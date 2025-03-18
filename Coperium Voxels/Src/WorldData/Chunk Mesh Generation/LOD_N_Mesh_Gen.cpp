#include "Chunk_Mesh.h"
#include "../../Compact Data/Cube Mesh/CCMS.h"
#include "../World Opertions/Wrap Operations/Wrap_Voxel_Operations.h"

glm::vec3 InterpolateColors(glm::vec3 color1, glm::vec3 color2, float t) {
    return glm::mix(color1, color2, t); // Linear interpolation between two colors
}

glm::vec3 CalculateAverageColorForVoxel(const glm::ivec3& voxelPos, Chunk& chunk, int l_o_d, int& num_air) {
    // In this case, we are linearly interpolating the surrounding voxel colors.
    glm::vec3 totalColor(0.0f);
    int count = 0;

    for (int i = 0; i < l_o_d; ++i) {
        for (int j = 0; j < l_o_d; ++j) {
            for (int k = 0; k < l_o_d; ++k) {
                Voxel* current_voxel = chunk.Get_Voxel(voxelPos + glm::ivec3(i, j, k), rel_loc_t::CHUNK_LOC);

                if (!current_voxel->IsAir()) {
                    totalColor += current_voxel->GetColour();
                    count++;
                }else {
                    num_air++;
                }
            }
        }
    }

    if (count > 0) {
        return totalColor / static_cast<float>(count);
    }

    return glm::vec3(0.5f);  // Default neutral color
}

void Generate_Chunk_Mesh(World& w, sector_pair_t sector_pair, chunk_pair_t chunk_pair, const Chunk& generic_chunk, int l_o_d) {
    const neighbouring_chunks_t c_neighbours = get_chunk_neighbours(w, chunk_pair, sector_pair, generic_chunk);

    std::vector<GLfloat> vertex_mesh;
    std::vector<GLuint> index_mesh;
    vertex_mesh.reserve(static_cast<size_t>(16) * 1024);
    index_mesh.reserve(static_cast<size_t>(4) * 1024);

    int vertex_offset = 0;
    int index_offset = 0;

    glm::vec3 color_accumulator(0.0f);

    for (int x = MIN_ID_V_X; x <= MAX_ID_V_X; x += l_o_d) {
        for (int y = MIN_ID_V_Y; y <= MAX_ID_V_Y; y += l_o_d) {
            for (int z = MIN_ID_V_Z; z <= MAX_ID_V_Z; z += l_o_d) {
                int num_air = 0;
                int solid_voxel_count = 0;

                // Calculate average color for the region
                glm::vec3 average_color = CalculateAverageColorForVoxel(glm::ivec3(x, y, z), chunk_pair.second, l_o_d, num_air);

                // Check if the chunk is mostly air and skip if necessary
                if (num_air >= l_o_d * l_o_d * l_o_d) continue;

                // Check neighboring faces for chunk boundaries
                cube_faces_t flags_air      = static_cast<cube_faces_t>(0);
                cube_faces_t flags_solid    = static_cast<cube_faces_t>(0);
                Chunk
                    * r_c = c_neighbours.Get_Right  (x + l_o_d - 1),
                    * t_c = c_neighbours.Get_Up     (y + l_o_d - 1),
                    * f_c = c_neighbours.Get_Front  (z + l_o_d - 1),
                    * l_c = c_neighbours.Get_Left   (x),
                    * d_c = c_neighbours.Get_Down   (y),
                    * b_c = c_neighbours.Get_Back   (z);

                cube_faces_t lod_flags = static_cast<cube_faces_t>(
                    ((r_c->Get_Chunk_Data().l_o_d >= l_o_d)) << RIGHT_SHIFT     |
                    ((l_c->Get_Chunk_Data().l_o_d >= l_o_d)) << LEFT_SHIFT      |
                    ((t_c->Get_Chunk_Data().l_o_d >= l_o_d)) << TOP_SHIFT       |
                    ((d_c->Get_Chunk_Data().l_o_d >= l_o_d)) << BOTTOM_SHIFT    |
                    ((f_c->Get_Chunk_Data().l_o_d >= l_o_d)) << FRONT_SHIFT     |
                    ((b_c->Get_Chunk_Data().l_o_d >= l_o_d)) << BACK_SHIFT
                );
                using u8 = std::underlying_type_t<cube_faces_t>;
                for (int i = 0; i < l_o_d; i++) {
                    for (int j = 0; j < l_o_d; j++) {
                        bool right_is_block     = r_c->Get_Voxel({ vox_inc_x(x, l_o_d), y + i, z + j })->IsAir();
                        bool left_is_block      = l_c->Get_Voxel({ vox_dec_x(x, l_o_d), y + i, z + j })->IsAir();
                        bool top_is_block       = t_c->Get_Voxel({ x + i, vox_inc_y(y, l_o_d), z + j })->IsAir();
                        bool bottom_is_block    = d_c->Get_Voxel({ x + i, vox_dec_y(y, l_o_d), z + j })->IsAir();
                        bool front_is_block     = f_c->Get_Voxel({ x + i, y + j, vox_inc_z(z, l_o_d) })->IsAir();
                        bool back_is_block      = b_c->Get_Voxel({ x + i, y + j, vox_dec_z(z, l_o_d) })->IsAir();

                        flags_air |= static_cast<cube_faces_t>(
                            (static_cast<u8>(right_is_block ) << RIGHT_SHIFT    ) |
                            (static_cast<u8>(left_is_block  ) << LEFT_SHIFT     ) |
                            (static_cast<u8>(top_is_block   ) << TOP_SHIFT      ) |
                            (static_cast<u8>(bottom_is_block) << BOTTOM_SHIFT   ) |
                            (static_cast<u8>(front_is_block ) << FRONT_SHIFT    ) |
                            (static_cast<u8>(back_is_block  ) << BACK_SHIFT     )
                        );

                        // Update block presence flag
                        flags_solid |= static_cast<cube_faces_t>(
                            (static_cast<u8>(!right_is_block ) << RIGHT_SHIFT    ) |
                            (static_cast<u8>(!left_is_block  ) << LEFT_SHIFT     ) |
                            (static_cast<u8>(!top_is_block   ) << TOP_SHIFT      ) |
                            (static_cast<u8>(!bottom_is_block) << BOTTOM_SHIFT   ) |
                            (static_cast<u8>(!front_is_block ) << FRONT_SHIFT    ) |
                            (static_cast<u8>(!back_is_block  ) << BACK_SHIFT     )
                        );
                    }
                }
                // --- Final Flag Register ---
                // For each face, if the neighbor's LOD is high (lod_flags set) and there is a block (flags_solid set)
                // then we cull (set final flag bit to 0); otherwise, we keep the air flag bit.
                cube_faces_t final_flags = static_cast<cube_faces_t>(
                    static_cast<u8>(flags_air) & ~(static_cast<u8>(lod_flags) & static_cast<u8>(flags_solid))
                );
                total_faces_generated += Count_Set_Bits(final_flags); // Track the total faces
                // Add the cube mesh with the smoothed average color
                Add_Cube_Mesh(glm::ivec3(x, y, z), average_color, vertex_mesh, index_mesh, vertex_offset, index_offset, final_flags, l_o_d);
            }
        }
    }

    // Final mesh configuration
    chunk_pair.second.Get_Mesh().Clear_Mesh();
    chunk_pair.second.Get_Mesh().Configure_Mesh(vertex_mesh.data(), sizeof(GLfloat), static_cast<GLsizei>(vertex_mesh.size()), GL_FLOAT, FACE_NUM_ELEMENTS);
    chunk_pair.second.Get_Mesh().Configure_Index_Buffer(index_mesh.data(), sizeof(GLuint), static_cast<GLsizei>(index_mesh.size()));

    chunk_pair.second.Get_Mesh().Add_Vertex_Set(0, 1, 0);
    chunk_pair.second.Get_Mesh().Add_Vertex_Set(1, 1, 1);
    chunk_pair.second.Get_Mesh().Add_Vertex_Set(2, 3, 2);
}
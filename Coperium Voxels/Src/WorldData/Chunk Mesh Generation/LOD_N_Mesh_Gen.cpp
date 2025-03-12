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
                bool 
                    right_face  = false, top_face = false, front_face   = false,
                    left_face   = false, bot_face = false, back_face    = false;

                Chunk
                    * r_c = c_neighbours.Get_Right  (x + l_o_d - 1),
                    * t_c = c_neighbours.Get_Up     (y + l_o_d - 1),
                    * f_c = c_neighbours.Get_Front  (z + l_o_d - 1),
                    * l_c = c_neighbours.Get_Left   (x),
                    * d_c = c_neighbours.Get_Down   (y),
                    * b_c = c_neighbours.Get_Back   (z);

                for (int i = 0; i < l_o_d; i++) {
                    for (int j = 0; j < l_o_d; j++) {
                        right_face  |= r_c->Get_Voxel(glm::ivec3(vox_inc_x(x, l_o_d), y + i, z + j))->IsAir();
                        left_face   |= l_c->Get_Voxel(glm::ivec3(vox_dec_x(x, l_o_d), y + i, z + j))->IsAir();
                        top_face    |= t_c->Get_Voxel(glm::ivec3(x + i, vox_inc_y(y, l_o_d), z + j))->IsAir();
                        bot_face    |= d_c->Get_Voxel(glm::ivec3(x + i, vox_dec_y(y, l_o_d), z + j))->IsAir();
                        front_face  |= f_c->Get_Voxel(glm::ivec3(x + i, y + j, vox_inc_z(z, l_o_d)))->IsAir();
                        back_face   |= b_c->Get_Voxel(glm::ivec3(x + i, y + j, vox_dec_z(z, l_o_d)))->IsAir();
                    }
                }

                cube_faces_t flags = static_cast<cube_faces_t>(
                    (right_face << 3) |
                    (left_face  << 2) |
                    (top_face   << 4) |
                    (bot_face   << 5) |
                    (front_face << 0) |
                    (back_face  << 1)
                );

                // Add the cube mesh with the smoothed average color
                Add_Cube_Mesh(glm::ivec3(x, y, z), average_color, vertex_mesh, index_mesh, vertex_offset, index_offset, flags, l_o_d);
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
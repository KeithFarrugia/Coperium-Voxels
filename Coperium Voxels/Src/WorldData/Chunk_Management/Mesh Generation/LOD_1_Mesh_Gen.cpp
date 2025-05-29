#include "Chunk_Mesh.h"
#include "../../../Compact Data/Cube Mesh/CCMS.h"
#include "../../World Opertions/Wrap Operations/Wrap_Voxel_Operations.h"
#include <bitset>



int Generate_Chunk_Mesh(World& w, sector_pair_t sector_pair, chunk_pair_t chunk_pair, const Chunk& generic_chunk) {
    const neighbouring_chunks_t c_neighbours =
        get_chunk_neighbours(w, chunk_pair, sector_pair, generic_chunk);

    std::vector<GLfloat>    vertex_mesh;
    std::vector<GLuint >    index_mesh;
    vertex_mesh.reserve(static_cast<size_t>(16) * 1024);
    index_mesh.reserve(static_cast<size_t>(4) * 1024);
    int vertex_offset = 0;
    int index_offset = 0;

    int total_faces_generated = 0;

    for (int x = MIN_ID_V_X; x <= MAX_ID_V_X; x++) {
        for (int y = MIN_ID_V_Y; y <= MAX_ID_V_Y; y++) {
            for (int z = MIN_ID_V_Z; z <= MAX_ID_V_Z; z++) {
                Voxel* voxel = chunk_pair.second.get()->Get_Voxel(glm::ivec3(x, y, z), rel_loc_t::CHUNK_LOC);
                if (!voxel->IsSolid()) continue;

                cube_faces_t flags = static_cast<cube_faces_t>(
                    ((c_neighbours.Get_Right(x)->Get_Voxel(glm::ivec3(vox_inc_x(x), y, z))->IsAir()) << 3) | // RIGHT_FACE
                    ((c_neighbours.Get_Left (x)->Get_Voxel(glm::ivec3(vox_dec_x(x), y, z))->IsAir()) << 2) | // LEFT_FACE
                    ((c_neighbours.Get_Up   (y)->Get_Voxel(glm::ivec3(x, vox_inc_y(y), z))->IsAir()) << 4) | // TOP_FACE
                    ((c_neighbours.Get_Down (y)->Get_Voxel(glm::ivec3(x, vox_dec_y(y), z))->IsAir()) << 5) | // BOTTOM_FACE
                    ((c_neighbours.Get_Front(z)->Get_Voxel(glm::ivec3(x, y, vox_inc_z(z)))->IsAir()) << 0) | // FRONT_FACE
                    ((c_neighbours.Get_Back (z)->Get_Voxel(glm::ivec3(x, y, vox_dec_z(z)))->IsAir()) << 1)   // BACK_FACE
                );

                total_faces_generated += Count_Set_Bits(flags); // Now local to this function

                Add_Cube_Mesh(
                    glm::ivec3(x, y, z),
                    voxel->GetColour(),
                    vertex_mesh, index_mesh,
                    vertex_offset, index_offset,
                    flags
                );
            }
        }
    }

    chunk_pair.second.get()->Get_Mesh().Clear_Mesh();
    chunk_pair.second.get()->Get_Mesh().Configure_Mesh(
        vertex_mesh.data(),
        sizeof(GLfloat),
        (GLsizei)vertex_mesh.size(),
        GL_FLOAT,
        FACE_NUM_ELEMENTS
    );
    chunk_pair.second.get()->Get_Mesh().Configure_Index_Buffer(
        index_mesh.data(),
        sizeof(GLuint),
        (GLsizei)index_mesh.size()
    );

    chunk_pair.second.get()->Get_Mesh().Add_Vertex_Set(0, 1, 0);
    chunk_pair.second.get()->Get_Mesh().Add_Vertex_Set(1, 1, 1);
    chunk_pair.second.get()->Get_Mesh().Add_Vertex_Set(2, 1, 2);

    return total_faces_generated;
}

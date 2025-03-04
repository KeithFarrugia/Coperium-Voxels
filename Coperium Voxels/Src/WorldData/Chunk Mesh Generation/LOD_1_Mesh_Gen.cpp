#include "Chunk Mesh.h"
#include "../../Compact Data/Cube Mesh/CCMS.h"

constexpr int NUM_VOXELS_X = MAX_ID_V_X - MIN_ID_V_X + 1; // 16
constexpr int NUM_VOXELS_Y = MAX_ID_V_Y - MIN_ID_V_Y + 1; // 64
constexpr int NUM_VOXELS_Z = MAX_ID_V_Z - MIN_ID_V_Z + 1; // 16

constexpr int MASK_VOXELS_X = NUM_VOXELS_X - 1; // 15 (0xF)
constexpr int MASK_VOXELS_Y = NUM_VOXELS_Y - 1; // 63 (0x3F)
constexpr int MASK_VOXELS_Z = NUM_VOXELS_Z - 1; // 15 (0xF)

constexpr inline int wrap_increment_x(int x) {
    return MIN_ID_V_X + (((x - MIN_ID_V_X) + 1) & MASK_VOXELS_X);
}
constexpr inline int wrap_decrement_x(int x) {
    return MIN_ID_V_X + (((x - MIN_ID_V_X) - 1) & MASK_VOXELS_X);
}
constexpr inline int wrap_increment_y(int y) {
    return MIN_ID_V_Y + (((y - MIN_ID_V_Y) + 1) & MASK_VOXELS_Y);
}
constexpr inline int wrap_decrement_y(int y) {
    return MIN_ID_V_Y + (((y - MIN_ID_V_Y) - 1) & MASK_VOXELS_Y);
}
constexpr inline int wrap_increment_z(int z) {
    return MIN_ID_V_Z + (((z - MIN_ID_V_Z) + 1) & MASK_VOXELS_Z);
}
constexpr inline int wrap_decrement_z(int z) {
    return MIN_ID_V_Z + (((z - MIN_ID_V_Z) - 1) & MASK_VOXELS_Z);
}

void Generate_Chunk_Mesh(World& w, chunk_pair_t chunk_pair, sector_pair_t sector_pair, const Chunk& generic_chunk) {
    const neighbouring_chunks_t c_neighbours = 
        get_chunk_neighbours(w, chunk_pair, sector_pair, generic_chunk);

    
    std::vector<GLfloat>    vertex_mesh;
    std::vector<GLuint >    index_mesh; 
    vertex_mesh.reserve     (static_cast<size_t>(16) * 1024);
    index_mesh .reserve     (static_cast<size_t>(4 ) * 1024);
    int vertex_offset       = 0;
    int index_offset        = 0;

    for (int x = MIN_ID_V_X; x <= MAX_ID_V_X; x++) {
        for (int y = MIN_ID_V_Y; y <= MAX_ID_V_Y; y++) {
            for (int z = MIN_ID_V_Z; z <= MAX_ID_V_Z; z++) {
                Voxel* voxel = chunk_pair.second.Get_Voxel(glm::ivec3(x, y, z), rel_loc_t::CHUNK_LOC);
                if (!voxel->IsSolid()) continue;
                cube_faces_t flags = static_cast<cube_faces_t>(
                    ((c_neighbours.Get_Right(x)->Get_Voxel(glm::ivec3(wrap_increment_x(x), y, z))->IsAir()) << 3) |  // RIGHT_FACE
                    ((c_neighbours.Get_Left (x)->Get_Voxel(glm::ivec3(wrap_decrement_x(x), y, z))->IsAir()) << 2) |   // LEFT_FACE
                    ((c_neighbours.Get_Up   (y)->Get_Voxel(glm::ivec3(x, wrap_increment_y(y), z))->IsAir()) << 4) |     // TOP_FACE
                    ((c_neighbours.Get_Down (y)->Get_Voxel(glm::ivec3(x, wrap_decrement_y(y), z))->IsAir()) << 5) |   // BOTTOM_FACE
                    ((c_neighbours.Get_Front(z)->Get_Voxel(glm::ivec3(x, y, wrap_increment_z(z)))->IsAir()) << 0) |  // FRONT_FACE
                    ((c_neighbours.Get_Back (z)->Get_Voxel(glm::ivec3(x, y, wrap_decrement_z(z)))->IsAir()) << 1)     // BACK_FACE
                    );

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


    chunk_pair.second.mesh.Clear_Mesh();
    chunk_pair.second.mesh.Configure_Mesh(
        vertex_mesh.data(),
        sizeof(GLfloat),
        (GLsizei)vertex_mesh.size(),
        GL_FLOAT,
        FACE_NUM_ELEMENTS
    );
    chunk_pair.second.mesh.Configure_Index_Buffer(
        index_mesh.data(),
        sizeof(GLuint),
        (GLsizei)index_mesh.size()
    );

    chunk_pair.second.mesh.Add_Vertex_Set(0, 1, 0);
    chunk_pair.second.mesh.Add_Vertex_Set(1, 1, 1);
    chunk_pair.second.mesh.Add_Vertex_Set(2, 3, 2);

}

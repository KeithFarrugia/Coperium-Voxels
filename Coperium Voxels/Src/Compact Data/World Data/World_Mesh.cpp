#include "World_Mesh.h"

void Generate_Single_Chunk_Mesh(World& w, Chunk* chunk, Sector* sector) {
    std::vector<GLfloat> vertex_mesh;
    std::vector<GLuint> index_mesh;
    int vertex_offset = 0;
    int index_offset = 0;
    if (chunk == nullptr || sector == nullptr) {
        return;
    }
    for (auto& voxel_entry : *chunk->Get_Voxels()) {
        glm::ivec3 relative_position = glm::vec3(
            voxel_entry.first.Get_X(),
            voxel_entry.first.Get_Y(),
            voxel_entry.first.Get_Z()
        );

        glm::ivec3 position = relative_position + glm::ivec3(
            chunk->Get_Offset_X() * CHUNK_X_MAX + sector->Get_Offset_X() * SECTOR_X_MAX,
            chunk->Get_Offset_Y() * CHUNK_Y_MAX,
            chunk->Get_Offset_Z() * CHUNK_Z_MAX + sector->Get_Offset_Z() * SECTOR_Z_MAX
        );

        glm::vec3 colour = glm::vec3(
            voxel_entry.second.Get_R(),
            voxel_entry.second.Get_G(),
            voxel_entry.second.Get_B()
        );

        cube_faces_t flags = static_cast<cube_faces_t>(0);

        // Check neighboring voxels to determine which faces to render
        if (w.Get_Voxel(position.x + 1, position.y, position.z).Get_Type() != voxel_type_t::NORMAL) {
            flags = (cube_faces_t)(flags | cube_faces_t::RIGHT_FACE);
        }
        if (w.Get_Voxel(position.x - 1, position.y, position.z).Get_Type() != voxel_type_t::NORMAL) {
            flags = (cube_faces_t)(flags | cube_faces_t::LEFT_FACE);
        }
        if (w.Get_Voxel(position.x, position.y + 1, position.z).Get_Type() != voxel_type_t::NORMAL) {
            flags = (cube_faces_t)(flags | cube_faces_t::TOP_FACE);
        }
        if (w.Get_Voxel(position.x, position.y - 1, position.z).Get_Type() != voxel_type_t::NORMAL) {
            flags = (cube_faces_t)(flags | cube_faces_t::BOTTOM_FACE);
        }
        if (w.Get_Voxel(position.x, position.y, position.z + 1).Get_Type() != voxel_type_t::NORMAL) {
            flags = (cube_faces_t)(flags | cube_faces_t::FRONT_FACE);
        }
        if (w.Get_Voxel(position.x, position.y, position.z - 1).Get_Type() != voxel_type_t::NORMAL) {
            flags = (cube_faces_t)(flags | cube_faces_t::BACK_FACE);
        }

        // Add the cube mesh for this voxel
        Add_Cube_Mesh(
            relative_position, colour,
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }

    // Generate the mesh for this chunk
    chunk->Generate_Mesh(vertex_mesh, index_mesh);
}


void Re_Generate_Chunk_Mesh(World& w, glm::ivec3 position) {
    Sector* sector = w.Get_Sector_W(position.x, position.y, position.z);
    Chunk* chunk = w.Get_Chunk(position);

    // Generate mesh for the current chunk
    Generate_Single_Chunk_Mesh(w, chunk, sector);

    // Check neighboring chunks
    std::vector<glm::ivec3> neighbors = {
        {CHUNK_X_MAX, 0, 0},   // Right
        {-CHUNK_X_MAX, 0, 0},  // Left
        {0, CHUNK_Y_MAX, 0},   // Up
        {0, -CHUNK_Y_MAX, 0},  // Down
        {0, 0, CHUNK_Z_MAX},    // Front
        {0, 0, -CHUNK_Z_MAX}    // Back
    };

    for (const auto& offset : neighbors) {
        Chunk* neighbor_chunk = w.Get_Chunk(position + glm::ivec3(offset)); // Adjust using offsets

        if (neighbor_chunk) {
            Generate_Single_Chunk_Mesh(w, neighbor_chunk, sector);
        }
    }
}

void Generate_All_Chunk_Meshes(World& w) {
    for (auto& sector_entry : *w.Get_Sectors()) {
        for (auto& chunk_entry : *sector_entry.second.Get_Chunks()) {
            Generate_Single_Chunk_Mesh(w, &chunk_entry.second, &sector_entry.second);
        }
    }
}

void Render_Chunk_Meshes(World& w, Coil::Shader& s){

    for (auto& sector_entry : *w.Get_Sectors()) {
        for (auto& chunk_entry : *sector_entry.second.Get_Chunks()) {
            glm::ivec3 offset = glm::vec3(
                chunk_entry.second.Get_Offset_X() * CHUNK_X_MAX + sector_entry.second.Get_Offset_X() * SECTOR_X_MAX,
                chunk_entry.second.Get_Offset_Y() * CHUNK_Y_MAX,
                chunk_entry.second.Get_Offset_Z() * CHUNK_Z_MAX + sector_entry.second.Get_Offset_Z() * SECTOR_Z_MAX
            );

            s.Set_Vec3("vertex_offset",offset);

            chunk_entry.second.Draw_Mesh();
        }
    }



}

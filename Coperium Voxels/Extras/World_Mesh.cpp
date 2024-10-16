#include "World_Mesh.h"

void Generate_Single_Chunk_Mesh(World* w, Chunk* chunk, Sector* sector) {
    std::vector<GLfloat> vertex_mesh;
    vertex_mesh.reserve(16 * 1024);
    std::vector<GLuint> index_mesh;
    index_mesh.reserve(4 * 1024);
    int vertex_offset = 0;
    int index_offset = 0;
    if (chunk == nullptr || sector == nullptr) {
        return;
    }
    for (int i = 0; i < VOX_LOC_MAX; i++) {
        Voxel_Loc v_loc(i);
        glm::ivec3 relative_position = glm::vec3(
            v_loc.Get_X(),
            v_loc.Get_Y(),
            v_loc.Get_Z()
        );

        glm::ivec3 position = relative_position + glm::ivec3(
            chunk->Get_Offset_X() * CHUNK_X_MAX + sector->Get_Offset_X() * SECTOR_X_MAX,
            chunk->Get_Offset_Y() * CHUNK_Y_MAX,
            chunk->Get_Offset_Z() * CHUNK_Z_MAX + sector->Get_Offset_Z() * SECTOR_Z_MAX
        );
        Voxel v = chunk->Get_Voxel(relative_position.x, relative_position.y, relative_position.z);
        glm::vec3 colour = glm::vec3(
            v.Get_R(),
            v.Get_G(),
            v.Get_B()
        );
        
        if (v.Get_Type() != voxel_type_t::NORMAL) {
            continue;
        }

        cube_faces_t flags = static_cast<cube_faces_t>(0);

        // Check neighboring voxels to determine which faces to render
        if (w->Get_Voxel(position.x + 1, position.y, position.z).Get_Type() != voxel_type_t::NORMAL) {
            flags = (cube_faces_t)(flags | cube_faces_t::RIGHT_FACE);
        }
        if (w->Get_Voxel(position.x - 1, position.y, position.z).Get_Type() != voxel_type_t::NORMAL) {
            flags = (cube_faces_t)(flags | cube_faces_t::LEFT_FACE);
        }
        if (w->Get_Voxel(position.x, position.y + 1, position.z).Get_Type() != voxel_type_t::NORMAL) {
            flags = (cube_faces_t)(flags | cube_faces_t::TOP_FACE);
        }
        if (w->Get_Voxel(position.x, position.y - 1, position.z).Get_Type() != voxel_type_t::NORMAL) {
            flags = (cube_faces_t)(flags | cube_faces_t::BOTTOM_FACE);
        }
        if (w->Get_Voxel(position.x, position.y, position.z + 1).Get_Type() != voxel_type_t::NORMAL) {
            flags = (cube_faces_t)(flags | cube_faces_t::FRONT_FACE);
        }
        if (w->Get_Voxel(position.x, position.y, position.z - 1).Get_Type() != voxel_type_t::NORMAL) {
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


void Re_Generate_Chunk_Mesh(World* w, glm::ivec3 position) {
    Sector* sector = w->Get_Sector_W(position.x, position.y, position.z);
    Chunk* chunk = w->Get_Chunk(position);

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

    printf("\n\nRegenerating....\n\n");
    for (const auto& offset : neighbors) {
        if (position.x % CHUNK_X_MAX != 0 || position.y % CHUNK_Y_MAX != 0 || position.z % CHUNK_Z_MAX != 0) { continue; }
        Chunk* neighbor_chunk = w->Get_Chunk(position + glm::ivec3(offset)); // Adjust using offse       ts

        if (neighbor_chunk) {
            Generate_Single_Chunk_Mesh(w, neighbor_chunk, sector);
            printf("Regenerating chunk: %d %d, %d\n", neighbor_chunk->Get_Offset_X(), neighbor_chunk->Get_Offset_Y(), neighbor_chunk->Get_Offset_Z());
        }
    }
}

void Generate_All_Chunk_Meshes(World* w) {

    for (uint32_t valid_sector : *w->Get_Valid_Sectors()) {
        for (uint16_t valid_chunk : *w->Get_Sector(valid_sector)->Get_Valid_Chunks()) {
            Generate_Single_Chunk_Mesh(
                w, 
                w->Get_Sector(valid_sector)->Get_Chunk(valid_chunk),
                w->Get_Sector(valid_sector)
            );
        }
    }
}

void Render_Chunk_Meshes(World* w, Coil::Shader& s){

    for (uint32_t valid_sector : *w->Get_Valid_Sectors()) {
        for (uint16_t valid_chunk : *w->Get_Sector(valid_sector)->Get_Valid_Chunks()) {

            Chunk* c = w->Get_Sector(valid_sector)->Get_Chunk(valid_chunk);
            glm::ivec3 offset = glm::vec3(
                c->Get_Offset_X() * CHUNK_X_MAX + w->Get_Sector(valid_sector)->Get_Offset_X() * SECTOR_X_MAX,
                c->Get_Offset_Y() * CHUNK_Y_MAX,
                c->Get_Offset_Z() * CHUNK_Z_MAX + w->Get_Sector(valid_sector)->Get_Offset_Z() * SECTOR_Z_MAX
            );

            s.Set_Vec3("vertex_offset",offset);

            c->Draw_Mesh();
        }
    }



}

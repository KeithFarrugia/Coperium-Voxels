#include "Manage_Chunks.h"
#include "../Create_Generic_Chunks.h"

void Update_Chunks(WorldManager& wm, Coil::Camera& camera) {
    // Compute camera position once and round.
    const glm::vec3 camera_pos = camera.Get_Position();
    const glm::ivec3 curr_position(
        glm::round(camera_pos.x),
        glm::round(camera_pos.y),
        glm::round(camera_pos.z)
    );
    glm::ivec3 current_chunk = Convert_Loc_2_ID(curr_position, rel_loc_t::WORLD_LOC, rel_loc_t::CHUNK_LOC);
    glm::ivec3 current_sector = Convert_Loc_2_ID(curr_position, rel_loc_t::WORLD_LOC, rel_loc_t::SECTOR_LOC);

    static glm::ivec3 last_chunk = glm::ivec3(INT_MIN, INT_MIN, INT_MIN);
    if (current_chunk == last_chunk) return;
    last_chunk = current_chunk;

    std::cout << "\nCurrent Sector : (" << current_sector.x << ", " << current_sector.y << ", " << current_sector.z << ") "
        << "Current Chunk    : (" << current_chunk.x << ", " << current_chunk.y << ", " << current_chunk.z << ")\n";

    // Unload far away chunks.
    Unload_Far_Chunks(wm, curr_position);

    // Load new chunks near the current chunk.
    Load_New_Chunks(wm, current_sector, current_chunk, Create_Solid_Chunk_Func);
}
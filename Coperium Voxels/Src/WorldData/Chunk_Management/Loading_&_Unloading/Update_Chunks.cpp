#include "../WorldManager.h"

void WorldManager::Dynamic_Update_Chunks(glm::vec3 player_position) {
    const glm::ivec3 curr_position(
        glm::round(player_position.x),
        glm::round(player_position.y),
        glm::round(player_position.z)
    );

    glm::ivec3 current_chunk    = Convert_Loc_2_ID(
        curr_position, rel_loc_t::WORLD_LOC, rel_loc_t::CHUNK_LOC
    );

    glm::ivec3 current_sector   = Convert_Loc_2_ID(
        curr_position, rel_loc_t::WORLD_LOC, rel_loc_t::SECTOR_LOC
    );

    last_chunk = glm::ivec3(INT_MIN, INT_MIN, INT_MIN);
    if (current_chunk == last_chunk) return;
    last_chunk = current_chunk;

    if (settings.debug) {
        std::cout 
            << "\nCurrent Sector : (" 
                << current_sector.x << ", " 
                << current_sector.y << ", "
                << current_sector.z << ") "
            << "Current Chunk    : (" 
                << current_chunk .x << ", " 
                << current_chunk .y << ", " 
                << current_chunk .z << ")\n";
    }
    
    if (settings.auto_unload) {
        if (load_callback) load_callback(*this);
        Unload_Far_Chunks(curr_position);
    }

    if (settings.auto_load) {
        if (unload_callback) unload_callback(*this);
        Load_New_Chunks(current_sector, current_chunk);
    }
}

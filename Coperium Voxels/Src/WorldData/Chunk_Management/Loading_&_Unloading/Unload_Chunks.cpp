#include "../WorldManager.h"
#include <GLM/gtx/norm.hpp>


/* ============================================================================
 * --------------------------- Unload_Chunk
 * Saves and removes a chunk from the world, then updates neighbouring chunks.
 *
 * ------ Parameters ------
 * world         : Reference to the world containing sectors and chunks.
 * world_name    : Name of the world (used when saving the chunk to disk).
 * sector_pair   : Pair containing sector location and its corresponding 
                   Sector pointer.
 * chunk_pair    : Pair containing chunk location and its corresponding 
                   Chunk object.
 * ============================================================================
 */

void WorldManager::Unload_Chunk(
    const sector_pair_t& sector_pair,
    const chunk_pair_t& chunk_pair
) {
    // Save chunk
    if (settings.allow_chunk_store) {
        Store_Chunk(sector_pair, chunk_pair);
    }

    // Remove chunk from sector
    Sector* sector = sector_pair.second.get();
    const glm::ivec3 chunk_loc(
        chunk_pair.first.X(),
        chunk_pair.first.Y(),
        chunk_pair.first.Z()
    );
    sector->Remove_Chunk(chunk_loc, rel_loc_t::CHUNK_LOC);

    // Update neighbouring chunks
    const glm::ivec3 sector_loc(
        sector_pair.first.X(),
        0,
        sector_pair.first.Z()
    );
    Set_Neighbours_to_Update(sector_loc, chunk_loc);

    if(settings.debug){
        std::cout << "Unloaded chunk at "
            << "Sector (" << sector_loc.x << "," << sector_loc.z << ") "
            << "Chunk  (" << chunk_loc .x << "," << chunk_loc .y << ","
                          << chunk_loc .z << ")\n";
    }
}


/* ============================================================================
 * --------------------------- Unload_Far_Chunks
 * Iterates over all chunks in the world and unloads any chunk whose center
 * is farther from the camera than the specified unload radius (in chunks).
 * Before unloading, each chunk is stored to disk.
 *
 * ------ Parameters ------
 * world_name:           The name of the world (used for saving chunk files).
 * world:                The world object managing sectors and chunks.
 * curr_position:        The current camera position (rounded to integers).
 *
 * ------ Operation ------
 * For each chunk, the world position is computed and its center is determined
 * by adding HALF_CHUNK. The squared distance from the camera to the chunk
 * center is computed and compared to a threshold derived from the unload
 * radius. If the distance is greater, the chunk is first stored to disk,
 * then unloaded.
 * ============================================================================
 */
void WorldManager::Unload_Far_Chunks(const glm::ivec3& curr_position) {
    const glm::vec2 cam_pos_xz(curr_position.x, curr_position.z);
    auto* sectors = world.Get_All_Sectrs();

    for (auto sector_pair : *sectors) {
        Sector* sector = sector_pair.second.get();
        glm::ivec3 sector_offset(
            sector_pair.first.X() * SECTR_SIZE_X,
            0,
            sector_pair.first.Z() * SECTR_SIZE_Z
        );

        auto* chunks = sector->Get_All_Chunks();
        std::vector<chunk_pair_t> chunks_to_unload;

        for (auto chunk_pair : *chunks) {
            glm::vec2 chunk_pos_xz(
                sector_offset.x + chunk_pair.first.X() * CHUNK_SIZE_X,
                sector_offset.z + chunk_pair.first.Z() * CHUNK_SIZE_Z
            );
            glm::vec2 chunk_center = chunk_pos_xz + glm::vec2(HALF_CHUNK.x, HALF_CHUNK.z);
            float dist_sq = glm::distance2(cam_pos_xz, chunk_center);

            if (dist_sq > unload_threshold) {
                chunks_to_unload.emplace_back(chunk_pair);
            }
        }

        for (const auto& chunk_pair : chunks_to_unload) {
            Unload_Chunk(sector_pair, chunk_pair);
        }
    }
}

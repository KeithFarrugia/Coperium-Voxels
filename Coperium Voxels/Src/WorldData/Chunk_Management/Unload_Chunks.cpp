#include "Manage_Chunks.h"
#include <GLM/gtx/norm.hpp>

constexpr glm::vec3 HALF_CHUNK = glm::vec3(
    CHUNK_SIZE_X * 0.5f,
    CHUNK_SIZE_Y * 0.5f,
    CHUNK_SIZE_Z * 0.5f
);

constexpr float chunk_unload_rad = 1;
float unload_treshold = chunk_unload_rad * CHUNK_SIZE_X * chunk_unload_rad * CHUNK_SIZE_Z;

/* ============================================================================
 * --------------------------- Unload_Chunk
 * Unloads a single chunk, given the sector offset and chunk coordinates.
 *
 * ------ Parameters ------
 * sector_pair  : Sector Pair.
 * chunk_pair   : Chunk Pair.
 * ============================================================================
 */
void Unload_Chunk(const sector_pair_t& sector_pair, const chunk_pair_t& chunk_pair) {
    // Your chunk-unloading logic (e.g., saving data and releasing resources)
    std::cout << "Unloading chunk at "
        << "Sector(" << sector_pair.first.X() << ", " << sector_pair.first.Z() << ")"
        << "Chunk(" << chunk_pair.first.X() << ", " << chunk_pair.first.Y() << ", " << chunk_pair.first.Z() << ")\n";
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
void Unload_Far_Chunks(WorldManager& wm, const glm::ivec3& curr_position) {
    World& world = wm.Get_World();
    const glm::vec2 camPosXZ = glm::vec2(curr_position.x, curr_position.z);  // Only XZ components

    sectors_t* sectors = world.Get_All_Sectrs();

    for (auto sector_pair : *sectors) {
        glm::ivec3 offset = glm::ivec3(
            sector_pair.first.X() * SECTR_SIZE_X,
            0,
            sector_pair.first.Z() * SECTR_SIZE_Z
        );

        auto* chunks = sector_pair.second.Get_All_Chunks();

        // Collect chunks to unload
        std::vector<chunk_loc_t> chunks_to_remove;

        for (auto chunk_pair : *chunks) {
            glm::vec2 chunk_posXZ(
                offset.x + chunk_pair.first.X() * CHUNK_SIZE_X,
                offset.z + chunk_pair.first.Z() * CHUNK_SIZE_Z
            );

            glm::vec2 chunk_centerXZ = chunk_posXZ + glm::vec2(HALF_CHUNK.x, HALF_CHUNK.z);
            float distSq = glm::distance2(camPosXZ, chunk_centerXZ);

            if (distSq > unload_treshold) {
                // Attempt to store the chunk before unloading it.
                Store_Chunk(wm.Get_World_Name(), sector_pair, chunk_pair);
                // Unload the chunk.
                Unload_Chunk(sector_pair, chunk_pair);
                chunks_to_remove.push_back(chunk_pair.first);
            }
        }

        // Remove chunks after iteration and update neighbours.
        for (const auto& chunk_loc : chunks_to_remove) {
            sector_pair.second.Remove_Chunk(glm::ivec3(chunk_loc.X(), chunk_loc.Y(), chunk_loc.Z()), rel_loc_t::CHUNK_LOC);
            Set_Neighbours_to_Update(
                world,
                glm::ivec3(sector_pair.first.X(), 0, sector_pair.first.Z()),
                glm::ivec3(chunk_loc.X(), chunk_loc.Y(), chunk_loc.Z())
            );
        }
    }
}

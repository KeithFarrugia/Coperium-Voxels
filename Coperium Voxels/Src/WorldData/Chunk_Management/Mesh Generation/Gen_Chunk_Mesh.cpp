#include "Chunk_Mesh.h"
#include "Calc_LOD.h"
#include "../WorldManager.h"
#include <chrono>

// Global state
int total_faces_generated = 0;


/* ============================================================================
 * --------------------------- Has_Moved
 * Returns true if the camera position has changed (in voxel space),
 * or if movement check is disabled.
 *
 * ------ Parameters ------
 * curr_position: Current camera voxel-space position.
 * check_mov:     Whether to skip processing if the camera hasn't moved.
 * ============================================================================ */
bool Has_Moved(glm::ivec3& last_position, glm::ivec3& curr_position, bool check_mov) {
    if (!check_mov) return true;
    if (curr_position == last_position) return false;
    last_position = curr_position;
    return true;
}

/* ============================================================================
 * --------------------------- Should_Update
 * Determines whether the update interval has elapsed since the last update.
 *
 * ------ Parameters ------
 * dt_ms              : Time delta in milliseconds.
 * update_interval_ms : Desired update interval.
 * ============================================================================ */
bool Should_Update(int dt_ms, int update_interval_ms, bool& first_call, int& time_acc_ms) {
    if (first_call) {
        time_acc_ms = update_interval_ms;
    }
    else {
        time_acc_ms += dt_ms;
    }

    if (time_acc_ms < update_interval_ms)
        return false;

    time_acc_ms -= update_interval_ms;
    return true;
}

/* ============================================================================
 * --------------------------- Update_Chunk_LODs
 * Sets the LOD level for each chunk based on the camera position and settings.
 *
 * Will reset chunks to NORMAL if LOD is disabled.
 *
 * ------ Parameters ------
 * world:      The game world containing all sectors and chunks.
 * camera_pos: The current camera position.
 * enable_LOD: Whether LOD is enabled (otherwise all chunks set to NORMAL).
 * ============================================================================ */
void Update_Chunk_LODs(
    World& world, const glm::vec3& camera_pos, bool enable_LOD,
    lod_dst_set_t lod_dst
) {
    sectors_t* sectors = world.Get_All_Sectrs();
    for (auto [sector_pos, sector_ptr] : *sectors) {
        chunks_t* chunks = sector_ptr->Get_All_Chunks();
        for (auto [chunk_pos, chunk_ptr] : *chunks) {
            chunk_data_t& data = chunk_ptr->Get_Chunk_Data();
            if (!enable_LOD) {
                if (data.l_o_d != lod_Level_t::NORMAL) {
                    data.l_o_d = lod_Level_t::NORMAL;
                    data.updated = true;
                }
                continue;
            }

            lod_Level_t new_lod = Compute_LOD(sector_pos, chunk_pos, camera_pos, lod_dst);
            if (new_lod != data.l_o_d) {
                data.l_o_d = new_lod;
                data.updated = true;
            }
        }
    }
}

/* ============================================================================
 * --------------------------- Regenerate_Update_Meshes
 * Re-generates the mesh for all chunks marked as updated, based on their LOD.
 *
 * ------ Parameters ------
 * world         : The game world containing all sectors and chunks.
 * generic_chunk : A shared/default chunk used during mesh generation.
 *
 * ------ Returns ------
 * true if any chunks were regenerated; false otherwise.
 * ============================================================================ */
bool Regenerate_Update_Meshes(World& world, Chunk& generic_chunk) {
    bool changed = false;
    sectors_t* sectors = world.Get_All_Sectrs();

    for (auto [sector_pos, sector_ptr] : *sectors) {
        chunks_t* chunks = sector_ptr->Get_All_Chunks();
        for (auto [chunk_pos, chunk_ptr] : *chunks) {
            chunk_data_t& data = chunk_ptr->Get_Chunk_Data();
            if (!data.updated) continue;

            if (data.l_o_d == lod_Level_t::NORMAL) {
                Generate_Chunk_Mesh(
                    world,
                    { sector_pos, sector_ptr },
                    { chunk_pos, chunk_ptr },
                    generic_chunk
                );
            }
            else {
                Generate_Chunk_Mesh(
                    world,
                    { sector_pos, sector_ptr },
                    { chunk_pos, chunk_ptr },
                    generic_chunk,
                    static_cast<int>(data.l_o_d)
                );
            }

            data.updated = false;
            changed = true;
        }
    }

    return changed;
}

/* ============================================================================
 * --------------------------- Generate_All_Chunk_Meshes
 * Main entry point for generating all chunk meshes with optional LOD support.
 *
 * Updates chunk LODs once unless `dynamic_lod` is enabled. Chunks are still
 * checked for mesh regeneration even if the player hasn't moved. Update
 * frequency is limited by `update_interval_ms`.
 *
 * ------ Parameters ------
 * player_position: The player's current position in world space.
 * ============================================================================ */
void WorldManager::Generate_All_Chunk_Meshes(glm::vec3 player_position) {
    auto now = std::chrono::steady_clock::now();
    auto dt_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - last_update_time
    ).count();

    last_update_time = now;

    glm::ivec3 curr_position(
        glm::round(player_position.x),
        glm::round(player_position.y),
        glm::round(player_position.z)
    );

    bool moved = Has_Moved(
        last_position, curr_position,
        settings.smart_update
    );

    if (!Should_Update(
        dt_ms, 
        settings.update_interval_ms, 
        initial_update, 
        time_acc_ms
    )) return;

    if (initial_update || (settings.dynamic_lod && moved)) {
        Update_Chunk_LODs(
            world           , player_position   , 
            settings.use_lod, settings.lod_set  );
    }

    if (Regenerate_Update_Meshes(world, settings.generic_chunk)) {
        printf("Number of faces: %d\n", total_faces_generated);
    }
}

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
    glm::ivec3 current_chunk = Convert_Loc_2_ID(
        curr_position, rel_loc_t::WORLD_LOC, rel_loc_t::CHUNK_LOC
    );

    if (current_chunk == last_position && check_mov) return false;
    last_position = current_chunk;
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
 * player_position: The current camera position.
 * ============================================================================ */
void WorldManager::Update_Chunk_LODs(
    const glm::vec3& player_position
) {
    sectors_t* sectors = world.Get_All_Sectrs();
    for (auto [sector_pos, sector_ptr] : *sectors) {
        chunks_t* chunks = sector_ptr->Get_All_Chunks();
        for (auto [chunk_pos, chunk_ptr] : *chunks) {
            chunk_data_t& data = chunk_ptr->Get_Chunk_Data();
            if (!settings.use_lod) {
                if (data.l_o_d != lod_Level_t::NORMAL) {
                    data.l_o_d = lod_Level_t::NORMAL;
                    data.updated = true;
                }
                continue;
            }else {

                lod_Level_t new_lod = Compute_LOD(sector_pos, chunk_pos, player_position, settings.lod_set);
                if (new_lod != data.l_o_d) {
                    data.l_o_d = new_lod;
                    data.updated = true;
                    Set_Neighbours_to_Update(
                        glm::ivec3(sector_pos.X(),        0     , sector_pos.Z()), 
                        glm::ivec3(chunk_pos. X(), chunk_pos.Y(), chunk_pos .Z())
                    );
                }
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
    int dt_ms = (int)std::chrono::duration_cast<std::chrono::milliseconds>(
        now - last_update_time
    ).count();

    last_update_time = now;

    glm::ivec3 curr_position(
        glm::round(player_position.x),
        glm::round(player_position.y),
        glm::round(player_position.z)
    );

    if (!Should_Update(
        dt_ms,
        settings.update_interval_ms,
        initial_update,
        time_acc_ms
    )) return;

    bool moved = Has_Moved(
        last_chunk_mesh, curr_position,
        settings.smart_update
    );

    if (initial_update || !settings.smart_update || moved) {
        Update_Chunk_LODs(player_position);
    }

    Regenerate_Update_Meshes(world, settings.generic_chunk);
}

/* ============================================================================
 * --------------------------- Clear Cache Thrasher
 * Performs a memory traversal over a large dummy buffer to evict existing
 * data from all cache levels. The buffer size should exceed the total
 * combined cache capacity.
 * ============================================================================ */
void Clear_Cache_Thrasher() {
    constexpr size_t cache_size_bytes = 32 * 1024 * 1024; // e.g., 32 MiB > typical L3
    constexpr size_t stride = 64;                       // cache line size
    static std::vector<char> buffer(cache_size_bytes);
    volatile char sink;
    for (size_t offset = 0; offset < cache_size_bytes; offset += stride) {
        sink = buffer[offset];
    }
    (void)sink; // prevent optimizing away
}

/* ============================================================================
 * --------------------------- Force Regenerate All Chunk Meshes Timed
 * Regenerates every chunk mesh ignoring `updated` flags, after clearing cache.
 * Prints CPU cycles taken to stdout.
 * ============================================================================ */
void WorldManager::Force_Generate_Meshes(glm::vec3 player_position) {
    // 1) Evict cache
    Clear_Cache_Thrasher();

    // 2) Record start time and cycles
    auto     wall_start = std::chrono::steady_clock::now();
    uint64_t rdtsc_start = __rdtsc();
    int      chunks_regenerated = 0;
    int64_t  total_faces_generated = 0;
    int      sector_count = 0;

    // 3) Optionally update LODs
    if (settings.use_lod) {
        Update_Chunk_LODs(player_position);
    }

    // 4) Regenerate all meshes
    sectors_t* sectors = world.Get_All_Sectrs();
    for (auto [sector_pos, sector_ptr] : *sectors) {
        ++sector_count;
        auto* chunks = sector_ptr->Get_All_Chunks();
        for (auto [chunk_pos, chunk_ptr] : *chunks) {
            chunk_data_t& data = chunk_ptr->Get_Chunk_Data();
            lod_Level_t lod = settings.use_lod
                ? data.l_o_d
                : lod_Level_t::NORMAL;

            int faces = (lod == lod_Level_t::NORMAL)
                ? Generate_Chunk_Mesh(
                    world,
                    { sector_pos, sector_ptr },
                    { chunk_pos, chunk_ptr },
                    settings.generic_chunk
                )
                : Generate_Chunk_Mesh(
                    world,
                    { sector_pos, sector_ptr },
                    { chunk_pos, chunk_ptr },
                    settings.generic_chunk,
                    static_cast<int>(data.l_o_d)
                );

            total_faces_generated += faces;
            data.updated = false;
            ++chunks_regenerated;
        }
    }

    // 5) Record end time and cycles
    uint64_t rdtsc_end = __rdtsc();
    auto     wall_end = std::chrono::steady_clock::now();

    // 6) Compute metrics
    uint64_t cycles = rdtsc_end - rdtsc_start;
    auto     elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        wall_end - wall_start
    );
    double   ms = static_cast<double>(elapsed_ms.count());
    double   seconds = ms / 1000.0;
    double   chunks_per_s = chunks_regenerated / seconds;
    double   faces_per_s = total_faces_generated / seconds;
    double   avg_faces_per_chunk = (chunks_regenerated > 0)
        ? static_cast<double>(total_faces_generated) / chunks_regenerated
        : 0.0;

    // 7) Output results
    std::cout
        << "===========================================================\n"
        << "Force regeneration cycles   = " << cycles << "\n"
        << "Wall time                   = " << ms << " ms\n"
        << "Sectors processed           = " << sector_count << "\n"
        << "Chunks regenerated          = " << chunks_regenerated
        << " (" << chunks_per_s << " chunks/s)\n"
        << "Faces generated             = " << total_faces_generated
        << " (" << faces_per_s << " faces/s)\n"
        << "Average faces per chunk     = " << avg_faces_per_chunk << "\n"
        << "===========================================================\n";
}

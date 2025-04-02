#include "Chunk_Mesh.h"
#include "Calc_LOD.h"
#include "../Create_Generic_Chunks.h"
#include <chrono>
int total_faces_generated = 0;
glm::ivec3 last_pos;
Chunk generic_c = Create_Air_Chunk();


/* ============================================================================
 * --------------------------- Generate_Single_Chunk
 * Generates or updates the mesh of a single chunk based on its LOD.
 *
 * ------ Parameters ------
 * world:       The game world containing all sectors and chunks.
 * sector_id:   The sector ID where the chunk is located.
 * chunk_id:    The chunk ID within the sector.
 * camera_pos:  The camera position for LOD calculation.
 * generic_chunk: A reference chunk used for mesh generation.
 * ============================================================================
 */
void Generate_Single_Chunk(
    World&              world      ,
    sector_pair_t       sector_pair,
    chunk_pair_t        chunk_pair ,
    const glm::vec3&    camera_pos
) {

    lod_Level_t new_lod = Compute_LOD(
        sector_pair.first, chunk_pair.first, camera_pos
    );
    if (
        chunk_pair.second.Get_Chunk_Data().l_o_d  != new_lod || 
        chunk_pair.second.Get_Chunk_Data().updated
    ){
        if (new_lod == lod_Level_t::NORMAL) {
            Generate_Chunk_Mesh(world, sector_pair, chunk_pair, generic_c);

        }else {
            Generate_Chunk_Mesh(world, sector_pair, chunk_pair, generic_c, static_cast<int>(new_lod));
        }
    }

    // Update chunk LOD
    chunk_pair.second.Get_Chunk_Data().l_o_d    = new_lod;
    chunk_pair.second.Get_Chunk_Data().updated  = false;
}




void Generate_All_Chunk_Meshes(World& world, Coil::Camera& camera) {
    const glm::vec3 camera_pos = camera.Get_Position();
    const glm::ivec3 curr_position(
        glm::round(camera_pos.x),
        glm::round(camera_pos.y),
        glm::round(camera_pos.z)
    );

    if (curr_position == last_pos) { return; }
    last_pos = curr_position;

    // Iterate over all sectors and chunks
    sectors_t* sectors = world.Get_All_Sectrs();
    for (sector_pair_t sector_pair : *sectors) {
        chunks_t* chunks = sector_pair.second.Get_All_Chunks();
        for (chunk_pair_t chunk_pair : *chunks) {
            Generate_Single_Chunk(
                world, 
                sector_pair, chunk_pair, 
                camera_pos
            );
        }
    }
    printf("Number of faces: %d\n", total_faces_generated);
}

void Generate_All_Chunk_Meshes_LOD_PASS(World& world, Coil::Camera& camera, bool check_mov, int update_interval_ms) {
    // Static variables to track time between calls.
    static auto last_frame_time = std::chrono::steady_clock::now();
    static float timeAccumulator = 0.0f;
    static bool firstCall = true;

    // Calculate elapsed time since the last call.
    auto now = std::chrono::steady_clock::now();
    float dt = std::chrono::duration_cast<std::chrono::duration<float>>(now - last_frame_time).count();
    last_frame_time = now;

    // On the first call, force an update by setting the accumulator high.
    if (firstCall) {
        timeAccumulator = update_interval_ms / 1000.0f;
        firstCall = false;
    }
    else {
        timeAccumulator += dt;
    }

    // Convert update interval to seconds.
    const float update_interval_sec = update_interval_ms / 1000.0f;

    // Only update when enough time has been accumulated.
    if (timeAccumulator < update_interval_sec)
        return;

    // Subtract the update interval from the accumulator (carry over any excess time).
    timeAccumulator -= update_interval_sec;

    // Get the current camera position.
    const glm::vec3 camera_pos = camera.Get_Position();
    const glm::ivec3 curr_position(
        glm::round(camera_pos.x),
        glm::round(camera_pos.y),
        glm::round(camera_pos.z)
    );

    // Check if movement is enabled and if the camera hasn't moved.
    // Assuming last_pos is a global or static variable of type glm::ivec3.
    static glm::ivec3 last_pos = curr_position;
    if (check_mov && curr_position == last_pos)
        return;
    last_pos = curr_position;

    bool changed = false;  // Flag to track if any changes occurred

    // Iterate over all sectors and chunks to update LOD values.
    sectors_t* sectors = world.Get_All_Sectrs();
    for (sector_pair_t sector_pair : *sectors) {
        chunks_t* chunks = sector_pair.second.Get_All_Chunks();
        for (chunk_pair_t chunk_pair : *chunks) {
            lod_Level_t new_lod = Compute_LOD(
                sector_pair.first, chunk_pair.first, camera_pos
            );
            if (new_lod != chunk_pair.second.Get_Chunk_Data().l_o_d) {
                chunk_pair.second.Get_Chunk_Data().l_o_d = new_lod;
                chunk_pair.second.Get_Chunk_Data().updated = true;
            }
        }
    }

    // Generate chunk meshes for updated chunks.
    for (sector_pair_t sector_pair : *sectors) {
        chunks_t* chunks = sector_pair.second.Get_All_Chunks();
        for (chunk_pair_t chunk_pair : *chunks) {
            if (chunk_pair.second.Get_Chunk_Data().updated) {
                if (chunk_pair.second.Get_Chunk_Data().l_o_d == lod_Level_t::NORMAL) {
                    Generate_Chunk_Mesh(world, sector_pair, chunk_pair, generic_c);
                }
                else {
                    Generate_Chunk_Mesh(world, sector_pair, chunk_pair, generic_c,
                        static_cast<int>(chunk_pair.second.Get_Chunk_Data().l_o_d));
                }
                chunk_pair.second.Get_Chunk_Data().updated = false;
                changed = true;
            }
        }
    }

    // Print information only if something changed.
    if (changed) {
        printf("Number of faces: %d\n", total_faces_generated);
    }
}

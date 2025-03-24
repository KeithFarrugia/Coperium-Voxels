
#include "Manage_Chunks.h"
#include "../World Opertions/Wrap Operations/Wrap_Chunk_Sector_Operations.h"
#include "../Create_Generic_Chunks.h"

constexpr int load_radius = 1;
/* ============================================================================
 * --------------------------- Load_Chunk
 * Attempts to load a chunk from a file. If unsuccessful, it creates a new chunk
 * using the provided chunk creation function and adds it to the sector.
 *
 * ------ Parameters ------
 * world: The world object where the chunk should be loaded.
 * sectorPos: The position of the sector containing the chunk.
 * chunkPos: The position of the chunk within the sector.
 * createChunkFunc: A callback function to create a chunk if loading from a file fails.
 *
 * ------ Operation ------
 * - Tries to load the chunk from a file.
 * - If the file is unavailable, a new chunk is created using createChunkFunc.
 * - The chunk is then added to the sector.
 * - Updates neighboring chunks.
 * ============================================================================
 */

void Load_Chunk(WorldManager& wm, const glm::ivec3& sector_pos, const glm::ivec3& chunk_pos, void (*create_chunk_func)(Chunk&, glm::ivec3 offset)) {
    // Retrieve or create the sector
    World& world = wm.Get_World();
    Sector* sector = world.Get_Sector(sector_pos, rel_loc_t::SECTOR_LOC);
    if (!sector) {
        world.Create_Sector(sector_pos, rel_loc_t::SECTOR_LOC);
        sector = world.Get_Sector(sector_pos, rel_loc_t::SECTOR_LOC);
    }

    // Attempt to load from file
    Chunk newChunk;
    bool loaded_from_file = Read_Chunk(wm.Get_World_Name(), sector_loc_t::Compact(sector_pos), chunk_loc_t::Compact(chunk_pos), newChunk);

    if (!loaded_from_file) {
        glm::ivec3 offset = glm::ivec3(
            chunk_pos.x * CHUNK_SIZE_X + sector_pos.x * SECTR_SIZE_X,
            chunk_pos.y * CHUNK_SIZE_Y,
            chunk_pos.z * CHUNK_SIZE_Z + sector_pos.z * SECTR_SIZE_Z
        );
        create_chunk_func(newChunk, offset);
    }

    // Add the chunk to the sector
    sector->Add_Chunk(chunk_pos, newChunk);

    Set_Neighbours_to_Update(world, sector_pos, chunk_pos);

    // Print whether it was loaded or generated
    if (loaded_from_file) {
        std::cout << "Loaded chunk from file at Sector(" << sector_pos.x << ", " << sector_pos.z
            << ") Chunk(" << chunk_pos.x << ", " << chunk_pos.y << ", " << chunk_pos.z << ")\n";
    }
    else {
        std::cout << "Generated new chunk at Sector(" << sector_pos.x << ", " << sector_pos.z
            << ") Chunk(" << chunk_pos.x << ", " << chunk_pos.y << ", " << chunk_pos.z << ")\n";
    }
}


/* ============================================================================
 * --------------------------- LoadNewChunks
 * Loads new chunks within a certain radius around the current chunk position.
 * If a chunk column does not exist, it attempts to load it from a file.
 * If unsuccessful, it creates a new chunk using the specified chunk creation function.
 *
 * ------ Parameters ------
 * world: The world object where the chunks should be loaded.
 * current_sector: The position of the sector containing the current chunk.
 * current_chunk: The position of the current chunk within the sector.
 * createChunkFunc: A callback function to create a chunk if loading from a file fails.
 *
 * ------ Operation ------
 * - Iterates through the chunk loading radius.
 * - Determines if a chunk column exists in the sector.
 * - If the chunk column does not exist, attempts to load from a file.
 * - If loading fails, creates a chunk using createChunkFunc.
 * ============================================================================
 */
void Load_New_Chunks(
    WorldManager& wm, 
    const glm::ivec3& current_sector, 
    const glm::ivec3& current_chunk, 
    void (*create_chunk_func)(Chunk&, glm::ivec3 offset)
) {
    glm::ivec3 sector_new = glm::ivec3(0), chunk_new = glm::ivec3(0);
    World& world = wm.Get_World();
    for (int dx = -load_radius; dx <= load_radius; ++dx) {
        for (int dz = -load_radius; dz <= load_radius; ++dz) {
            if (dx == 0 && dz == 0)
                continue;

            wrap_chunk_sec_x(current_sector.x, current_chunk.x, dx, sector_new.x, chunk_new.x);
            wrap_chunk_sec_z(current_sector.z, current_chunk.z, dz, sector_new.z, chunk_new.z);

            Sector* sector = world.Get_Sector(sector_new, rel_loc_t::SECTOR_LOC);
            bool columnExists = false;
            if (sector) {
                auto* chunks = sector->Get_All_Chunks();
                for (auto chunkPair : *chunks) {
                    if (
                        chunkPair.first.X() == chunk_new.x &&
                        chunkPair.first.Z() == chunk_new.z
                        ) {
                        columnExists = true;
                        break;
                    }
                }
            }

            if (!columnExists) {
                if (!sector) {
                    world.Create_Sector(sector_new, rel_loc_t::SECTOR_LOC);
                    sector = world.Get_Sector(sector_new, rel_loc_t::SECTOR_LOC);
                }
                Load_Chunk(wm, sector_new, chunk_new, create_chunk_func);
            }
        }
    }
}


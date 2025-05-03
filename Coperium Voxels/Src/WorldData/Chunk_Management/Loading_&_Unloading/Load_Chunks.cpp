
#include "../WorldManager.h"
#include "../../World Opertions/Wrap Operations/Wrap_Chunk_Sector_Operations.h"
#include "../../Create_Generic_Chunks.h"

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
void WorldManager::Load_New_Chunks(
    const glm::ivec3    & current_sector,
    const glm::ivec3    & current_chunk
) {
    glm::ivec3 sector_new, chunk_new;

    for (int dx = -settings.chunk_radius; dx <= settings.chunk_radius; ++dx) {
        for (int dz = -settings.chunk_radius; dz <= settings.chunk_radius; ++dz) {
            if (dx == 0 && dz == 0) continue;

            wrap_chunk_sec_x(current_sector.x, current_chunk.x, dx, sector_new.x, chunk_new.x);
            wrap_chunk_sec_z(current_sector.z, current_chunk.z, dz, sector_new.z, chunk_new.z);

            Sector* sector = world.Get_Sector(sector_new, rel_loc_t::SECTOR_LOC);
            bool column_exists = false;

            if (sector) {
                chunks_t* chunks = sector->Get_All_Chunks();
                for (chunk_pair_t chunk_pair : *chunks) {
                    if (chunk_pair.first.X() == chunk_new.x &&
                        chunk_pair.first.Z() == chunk_new.z) {
                        column_exists = true;
                        break;
                    }
                }
            }

            if (!column_exists) {
                Load_Chunk(sector_new, chunk_new);
            }
        }
    }
}



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

void WorldManager::Load_Chunk(
    const glm::ivec3& sector_pos,
    const glm::ivec3& chunk_pos
){
    Sector* sector = 
                 world.Get_Sector(sector_pos, rel_loc_t::SECTOR_LOC);
    if (!sector) {
                 world.Create_Sector(sector_pos, rel_loc_t::SECTOR_LOC);
        sector = world.Get_Sector   (sector_pos, rel_loc_t::SECTOR_LOC);
    }

    Chunk new_chunk;
    bool loaded = false;

    if (settings.allow_load_from_file) {
        loaded = Read_Chunk(
            sector_loc_t::Compact(sector_pos),
            chunk_loc_t ::Compact(chunk_pos),
            new_chunk
        );
    }

    if (!loaded && settings.allow_chunk_generation) {
        glm::ivec3 offset = {
            chunk_pos.x * CHUNK_SIZE_X + sector_pos.x * SECTR_SIZE_X,
            chunk_pos.y * CHUNK_SIZE_Y                              ,
            chunk_pos.z * CHUNK_SIZE_Z + sector_pos.z * SECTR_SIZE_Z
        };
        chunk_generation_callback(new_chunk, offset);
    }

    sector->Add_Chunk(chunk_pos, new_chunk);
    Set_Neighbours_to_Update(sector_pos, chunk_pos);

    if (settings.debug) {
        std::cout
            << (loaded ? "[Loaded] " : "[Generated] ")
            << "Sector (" << sector_pos.x << "," << sector_pos.z << ") "
            << "Chunk  (" << chunk_pos .x << "," << chunk_pos .y << "," 
                          << chunk_pos .z << ")\n";
    }
    
}
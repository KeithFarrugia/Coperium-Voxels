#include "Chunk_Mesh.h"

const Chunk* Get_Left_Chunk (World& w, chunk_pair_t chunk, sector_pair_t sector, const Chunk* generic_chunk);
const Chunk* Get_Right_Chunk(World& w, chunk_pair_t chunk, sector_pair_t sector, const Chunk* generic_chunk);
const Chunk* Get_Top_Chunk  (World& w, chunk_pair_t chunk, sector_pair_t sector, const Chunk* generic_chunk);
const Chunk* Get_Bot_Chunk  (World& w, chunk_pair_t chunk, sector_pair_t sector, const Chunk* generic_chunk);
const Chunk* Get_Front_Chunk(World& w, chunk_pair_t chunk, sector_pair_t sector, const Chunk* generic_chunk);
const Chunk* Get_Back_Chunk (World& w, chunk_pair_t chunk, sector_pair_t sector, const Chunk* generic_chunk);


const neighbouring_chunks_t get_chunk_neighbours(
    World&          w, 
    chunk_pair_t    chunk, 
    sector_pair_t   sector, 
    const Chunk&    generic_chunk
) {
    return neighbouring_chunks_t(
        Get_Left_Chunk  (w, chunk, sector, &generic_chunk), 
        Get_Right_Chunk (w, chunk, sector, &generic_chunk), 
        
        Get_Top_Chunk   (w, chunk, sector, &generic_chunk),
        Get_Bot_Chunk   (w, chunk, sector, &generic_chunk),

        Get_Front_Chunk (w, chunk, sector, &generic_chunk),
        Get_Back_Chunk  (w, chunk, sector, &generic_chunk),

        &chunk.second
    );
}



/* ============================================================================
 * --------------------------- Get_Right_Chunk
 * Determines the right (positive X) neighbouring chunk for a given chunk.
 *
 * ------ Parameters ------
 * w            : Reference the world object containing all sectors and chunks.
 * chunk        : Pair of the current chunk's location and the chunk itself.
 * sector       : Pair of the current sector's location and the sector itself.
 * generic_chunk: A default chunk pointer if the neighbouring chunk is null.
 *
 * ------ Returns ------
 * A pointer to the neighbouring chunk in the positive X direction,
 * or generic_chunk if not found.
 * ============================================================================ */
const Chunk* Get_Right_Chunk(
    World&          w           ,
    chunk_pair_t    chunk       ,
    sector_pair_t   sector      ,
    const Chunk*    generic_chunk
) {
    /* ---------------------------------------------
     * current chunk is not at the edge 
     * --------------------------------------------- */
    if (chunk.first.X() < MAX_ID_C_X) {
        const Chunk* candidate = sector.second.Get_Chunk(
            chunk_loc_t::Compact(glm::ivec3(
                chunk.first.X() + 1, chunk.first.Y(), chunk.first.Z()
            ))
        );
        return candidate ? candidate : generic_chunk;
    }

    /* ---------------------------------------------
     * current sector is not at the edge
     * --------------------------------------------- */
    if (sector.first.X() < MAX_ID_S_X) {
        Sector* next_sector = w.Get_Sector(
            sector_loc_t::Compact(glm::ivec2(
                sector.first.X() + 1, sector.first.Z()
            ))
        );
        if (next_sector) {
            const Chunk* candidate = next_sector->Get_Chunk(
                chunk_loc_t::Compact(glm::ivec3(
                    MIN_ID_C_X, chunk.first.Y(), chunk.first.Z()
                ))
            );
            return candidate ? candidate : generic_chunk;
        }
    }

    return generic_chunk;
}
/* ============================================================================
 * --------------------------- Get_Left_Chunk
 * Determines the left (negative X) neighbouring chunk for a given chunk.
 *
 * ------ Parameters ------
 * w           : Reference to the world object containing all sectors and chunks.
 * chunk       : Pair of the current chunk's location and the chunk itself.
 * sector      : Pair of the current sector's location and the sector itself.
 * generic_chunk: A default chunk pointer if the neighbouring chunk is null.
 *
 * ------ Returns ------
 * A pointer to the neighbouring chunk in the negative X direction,
 * or generic_chunk if not found.
 * ============================================================================ */
const Chunk* Get_Left_Chunk(
    World&          w           ,
    chunk_pair_t    chunk       ,
    sector_pair_t   sector      ,
    const Chunk*    generic_chunk
) {
    /* ---------------------------------------------
     * current chunk is not at the edge 
     * --------------------------------------------- */
    if (chunk.first.X() > MIN_ID_C_X) {
        const Chunk* candidate = sector.second.Get_Chunk(
            chunk_loc_t::Compact(glm::ivec3(
                chunk.first.X() - 1, chunk.first.Y(), chunk.first.Z()
            ))
        );
        return candidate ? candidate : generic_chunk;
    }

    /* ---------------------------------------------
     * current sector is not at the edge
     * --------------------------------------------- */
    if (sector.first.X() > MIN_ID_S_X) {
        Sector* next_sector = w.Get_Sector(
            sector_loc_t::Compact(glm::ivec2(
                sector.first.X() - 1, sector.first.Z()
            ))
        );
        if (next_sector) {
            const Chunk* candidate = next_sector->Get_Chunk(
                chunk_loc_t::Compact(glm::ivec3(
                    MAX_ID_C_X, chunk.first.Y(), chunk.first.Z()
                ))
            );
            return candidate ? candidate : generic_chunk;
        }
    }

    return generic_chunk;
}

/* ============================================================================
 * --------------------------- Get_Top_Chunk
 * Determines the top (positive Y) neighbouring chunk for a given chunk.
 *
 * ------ Parameters ------
 * w           : Reference to the world object containing all sectors and chunks.
 * chunk       : Pair of the current chunk's location and the chunk itself.
 * sector      : Pair of the current sector's location and the sector itself.
 * generic_chunk: A default chunk pointer if the neighbouring chunk is null.
 *
 * ------ Returns ------
 * A pointer to the neighbouring chunk in the positive Y direction,
 * or generic_chunk if not found.
 * ============================================================================ */
const Chunk* Get_Top_Chunk(
    World&          w           ,
    chunk_pair_t    chunk       ,
    sector_pair_t   sector      ,
    const Chunk*    generic_chunk
) {
    /* ---------------------------------------------
     * current chunk is not at the edge 
     * --------------------------------------------- */
    if (chunk.first.Y() < MAX_ID_C_Y) {
        const Chunk* candidate = sector.second.Get_Chunk(
            chunk_loc_t::Compact(glm::ivec3(
                chunk.first.X(), chunk.first.Y() + 1, chunk.first.Z()
            ))
        );
        return candidate ? candidate : generic_chunk;
    }

    return generic_chunk;
}

/* ============================================================================
 * --------------------------- Get_Bot_Chunk
 * Determines the bottom (negative Y) neighbouring chunk for a given chunk.
 *
 * ------ Parameters ------
 * w           : Reference to the world object containing all sectors and chunks.
 * chunk       : Pair of the current chunk's location and the chunk itself.
 * sector      : Pair of the current sector's location and the sector itself.
 * generic_chunk: A default chunk pointer if the neighbouring chunk is null.
 *
 * ------ Returns ------
 * A pointer to the neighbouring chunk in the negative Y direction,
 * or generic_chunk if not found.
 * ============================================================================ */
const Chunk* Get_Bot_Chunk(
    World&          w           ,
    chunk_pair_t    chunk       ,
    sector_pair_t   sector      ,
    const Chunk*    generic_chunk
) {
    /* ---------------------------------------------
     * current chunk is not at the edge
     * --------------------------------------------- */
    if (chunk.first.Y() > MIN_ID_C_Y) {
        const Chunk* candidate = sector.second.Get_Chunk(
            chunk_loc_t::Compact(glm::ivec3(
                chunk.first.X(), chunk.first.Y() - 1, chunk.first.Z()
            ))
        );
        return candidate ? candidate : generic_chunk;
    }

    return generic_chunk;
}

/* ============================================================================
 * --------------------------- Get_Front_Chunk
 * Determines the front (positive Z) neighbouring chunk for a given chunk.
 *
 * ------ Parameters ------
 * w           : Reference to the world object containing all sectors and chunks.
 * chunk       : Pair of the current chunk's location and the chunk itself.
 * sector      : Pair of the current sector's location and the sector itself.
 * generic_chunk: A default chunk pointer if the neighbouring chunk is null.
 *
 * ------ Returns ------
 * A pointer to the neighbouring chunk in the positive Z direction,
 * or generic_chunk if not found.
 * ============================================================================ */
const Chunk* Get_Front_Chunk(
    World&          w           ,
    chunk_pair_t    chunk       ,
    sector_pair_t   sector      ,
    const Chunk*    generic_chunk
) {
    /* ---------------------------------------------
     * current chunk is not at the edge
     * --------------------------------------------- */
    if (chunk.first.Z() < MAX_ID_C_Z) {
        const Chunk* candidate = sector.second.Get_Chunk(
            chunk_loc_t::Compact(glm::ivec3(
                chunk.first.X(), chunk.first.Y(), chunk.first.Z() + 1
            ))
        );
        return candidate ? candidate : generic_chunk;
    }

    /* ---------------------------------------------
     * current sector is not at the edge
     * --------------------------------------------- */
    if (sector.first.Z() < MAX_ID_S_Z) {
        Sector* next_sector = w.Get_Sector(
            sector_loc_t::Compact(glm::ivec2(
                sector.first.X(), sector.first.Z() + 1
            ))
        );
        if (next_sector) {
            const Chunk* candidate = next_sector->Get_Chunk(
                chunk_loc_t::Compact(glm::ivec3(
                    chunk.first.X(), chunk.first.Y(), MIN_ID_C_Z
                ))
            );
            return candidate ? candidate : generic_chunk;
        }
    }

    return generic_chunk;
}

/* ============================================================================
 * --------------------------- Get_Back_Chunk
 * Determines the back (negative Z) neighbouring chunk for a given chunk.
 *
 * ------ Parameters ------
 * w           : Reference to the world object containing all sectors and chunks.
 * chunk       : Pair of the current chunk's location and the chunk itself.
 * sector      : Pair of the current sector's location and the sector itself.
 * generic_chunk: A default chunk pointer if the neighbouring chunk is null.
 *
 * ------ Returns ------
 * A pointer to the neighbouring chunk in the negative Z direction,
 * or generic_chunk if not found.
 * ============================================================================ */
const Chunk* Get_Back_Chunk(
    World& w,
    chunk_pair_t    chunk,
    sector_pair_t   sector,
    const Chunk* generic_chunk
) {
    /* ---------------------------------------------
     * current chunk is not at the edge
     * --------------------------------------------- */
    if (chunk.first.Z() > MIN_ID_C_Z) {
        const Chunk* candidate = sector.second.Get_Chunk(
            chunk_loc_t::Compact(glm::ivec3(
                chunk.first.X(), chunk.first.Y(), chunk.first.Z() - 1
            ))
        );
        return candidate ? candidate : generic_chunk;
    }

    /* ---------------------------------------------
     * current sector is not at the edge
     * --------------------------------------------- */
    if (sector.first.Z() > MIN_ID_S_Z) {
        Sector* next_sector = w.Get_Sector(
            sector_loc_t::Compact(glm::ivec2(
                sector.first.X(), sector.first.Z() - 1
            ))
        );
        if (next_sector) {
            const Chunk* candidate = next_sector->Get_Chunk(
                chunk_loc_t::Compact(glm::ivec3(
                    chunk.first.X(), chunk.first.Y(), MAX_ID_C_Z
                ))
            );
            return candidate ? candidate : generic_chunk;
        }
    }

    return generic_chunk;
}
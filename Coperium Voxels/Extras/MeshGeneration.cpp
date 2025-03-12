#include "World.h"
#include "../Compact Data/Cube Mesh/CCMS.h"

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
    World& w,
    const chunk_pair_t    chunk,
    const sector_pair_t   sector,
    const Chunk* generic_chunk
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
    World& w,
    const chunk_pair_t    chunk,
    const sector_pair_t   sector,
    const Chunk* generic_chunk
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
    World& w,
    const chunk_pair_t    chunk,
    const sector_pair_t   sector,
    const Chunk* generic_chunk
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
    World& w,
    const chunk_pair_t    chunk,
    const sector_pair_t   sector,
    const Chunk* generic_chunk
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
    World& w,
    const chunk_pair_t    chunk,
    const sector_pair_t   sector,
    const Chunk* generic_chunk
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
    const chunk_pair_t    chunk,
    const sector_pair_t   sector,
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

void Chunk::Generate_Mesh(
    World& w, const chunk_pair_t chunk, const sector_pair_t sector, const Chunk& generic_chunk
) {

    std::vector<GLfloat>    vertex_mesh;
    std::vector<GLuint>     index_mesh; 
    vertex_mesh.reserve(static_cast<size_t>(16) * 1024);
    index_mesh.reserve(static_cast<size_t>(4) * 1024);
    int vertex_offset = 0;
    int index_offset = 0;

    Sector* curr_s = &sector.second;
    Chunk* curr_c = &chunk.second;

    // Get neighbouring chunks in X, Y, and Z directions
    const Chunk* r_chunk = Get_Right_Chunk  (w, chunk, sector, &generic_chunk);
    const Chunk* l_chunk = Get_Left_Chunk   (w, chunk, sector , &generic_chunk);

    const Chunk* u_chunk = Get_Top_Chunk    (w, chunk, sector, &generic_chunk);
    const Chunk* d_chunk = Get_Bot_Chunk    (w, chunk, sector, &generic_chunk);

    const Chunk* f_chunk = Get_Front_Chunk  (w, chunk, sector, &generic_chunk);
    const Chunk* b_chunk = Get_Back_Chunk   (w, chunk, sector, &generic_chunk);

    /* ======================================================================
     *                           CENTRAL
     * ======================================================================
     */
    // Internal cubes processing (same as before)
    for (int x = MIN_ID_V_X + 1; x < MAX_ID_V_X; x++) {
        for (int y = MIN_ID_V_Y + 1; y < MAX_ID_V_Y; y++) {
            for (int z = MIN_ID_V_Z + 1; z < MAX_ID_V_Z; z++) {
                Voxel* voxel = Get_Voxel(glm::ivec3(x, y, z), rel_loc_t::CHUNK_LOC);
                if (!voxel->IsSolid()) continue;

                cube_faces_t flags = static_cast<cube_faces_t>(
                    ((curr_c->Get_Voxel(glm::ivec3(x + 1, y     , z     ))->IsAir()) << 3) |  // RIGHT_FACE
                    ((curr_c->Get_Voxel(glm::ivec3(x - 1, y     , z     ))->IsAir()) << 2) |  // LEFT_FACE
                    ((curr_c->Get_Voxel(glm::ivec3(x    , y + 1 , z     ))->IsAir()) << 4) |  // TOP_FACE
                    ((curr_c->Get_Voxel(glm::ivec3(x    , y - 1 , z     ))->IsAir()) << 5) |  // BOTTOM_FACE
                    ((curr_c->Get_Voxel(glm::ivec3(x    , y     , z + 1 ))->IsAir()) << 0) |  // FRONT_FACE
                    ((curr_c->Get_Voxel(glm::ivec3(x    , y     , z - 1 ))->IsAir()) << 1)    // BACK_FACE
                );

                Add_Cube_Mesh(
                    glm::ivec3(x, y, z),
                    voxel->GetColour(),
                    vertex_mesh, index_mesh,
                    vertex_offset, index_offset,
                    flags
                );
            }
        }
    }


    /* ======================================================================
     *                           Faces
     * ======================================================================
     */
    // Top Set Faces
    for (int x = MIN_ID_V_X + 1; x < MAX_ID_V_X; x++) {
        for (int z = MIN_ID_V_Z + 1; z < MAX_ID_V_Z; z++) {
            Voxel* voxel = Get_Voxel(glm::ivec3(x, MAX_ID_V_Y, z), rel_loc_t::CHUNK_LOC);
            if (!voxel->IsSolid()) continue;

            cube_faces_t flags = static_cast<cube_faces_t>(
                ((curr_c->Get_Voxel (glm::ivec3(x + 1   , MAX_ID_V_Y    , z     ))->IsAir()) << 3) |  // RIGHT_FACE
                ((curr_c->Get_Voxel (glm::ivec3(x - 1   , MAX_ID_V_Y    , z     ))->IsAir()) << 2) |  // LEFT_FACE
                ((u_chunk->Get_Voxel(glm::ivec3(x       , MIN_ID_V_Y    , z     ))->IsAir()) << 4) |  // TOP_FACE
                ((curr_c->Get_Voxel (glm::ivec3(x       , MAX_ID_V_Y - 1, z     ))->IsAir()) << 5) |  // BOTTOM_FACE
                ((curr_c->Get_Voxel (glm::ivec3(x       , MAX_ID_V_Y    , z + 1 ))->IsAir()) << 0) |  // FRONT_FACE
                ((curr_c->Get_Voxel (glm::ivec3(x       , MAX_ID_V_Y    , z - 1 ))->IsAir()) << 1)    // BACK_FACE
            );

            Add_Cube_Mesh(
                glm::ivec3(x, MAX_ID_V_Y, z),
                voxel->GetColour(),
                vertex_mesh, index_mesh,
                vertex_offset, index_offset,
                flags
            );
        }
    }
    // Bottom Set Faces
    for (int x = MIN_ID_V_X + 1; x < MAX_ID_V_X; x++) {
        for (int z = MIN_ID_V_Z + 1; z < MAX_ID_V_Z; z++) {

            Voxel* voxel = Get_Voxel(glm::ivec3(x, MIN_ID_V_Y, z), rel_loc_t::CHUNK_LOC);
            if (!voxel->IsSolid()) continue;

            cube_faces_t flags = static_cast<cube_faces_t>(
                ((curr_c->Get_Voxel (glm::ivec3(x + 1   , MIN_ID_V_Y    , z     ))->IsAir()) << 3) |  // RIGHT_FACE
                ((curr_c->Get_Voxel (glm::ivec3(x - 1   , MIN_ID_V_Y    , z     ))->IsAir()) << 2) |  // LEFT_FACE
                ((curr_c->Get_Voxel (glm::ivec3(x       , MIN_ID_V_Y + 1, z     ))->IsAir()) << 4) |  // TOP_FACE
                ((d_chunk->Get_Voxel(glm::ivec3(x       , MAX_ID_V_Y    , z     ))->IsAir()) << 5) |  // BOTTOM_FACE
                ((curr_c->Get_Voxel (glm::ivec3(x       , MIN_ID_V_Y    , z + 1 ))->IsAir()) << 0) |  // FRONT_FACE
                ((curr_c->Get_Voxel (glm::ivec3(x       , MIN_ID_V_Y    , z - 1 ))->IsAir()) << 1)    // BACK_FACE
            );

            Add_Cube_Mesh(
                glm::ivec3(x, MIN_ID_V_Y, z),
                voxel->GetColour(),
                vertex_mesh, index_mesh,
                vertex_offset, index_offset,
                flags
            );
        }
    }

    // Front Set Faces
    for (int x = MIN_ID_V_X + 1; x < MAX_ID_V_X; x++) {
        for (int y = MIN_ID_V_Y + 1; y < MAX_ID_V_Y; y++) {

            Voxel* voxel = Get_Voxel(glm::ivec3(x, y, MAX_ID_V_Z), rel_loc_t::CHUNK_LOC);
            if (!voxel->IsSolid()) continue;

            cube_faces_t flags = static_cast<cube_faces_t>(
                ((curr_c->Get_Voxel (glm::ivec3(x + 1   , y     , MAX_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
                ((curr_c->Get_Voxel (glm::ivec3(x - 1   , y     , MAX_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
                ((curr_c->Get_Voxel (glm::ivec3(x       , y + 1 , MAX_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
                ((curr_c->Get_Voxel (glm::ivec3(x       , y - 1 , MAX_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
                ((f_chunk->Get_Voxel(glm::ivec3(x       , y     , MIN_ID_V_Z    ))->IsAir()) << 0) |  // FRONT_FACE
                ((curr_c->Get_Voxel (glm::ivec3(x       , y     , MAX_ID_V_Z - 1))->IsAir()) << 1)    // BACK_FACE
            );

            Add_Cube_Mesh(
                glm::ivec3(x, y, MAX_ID_V_Z),
                voxel->GetColour(),
                vertex_mesh, index_mesh,
                vertex_offset, index_offset,
                flags
            );
        }
    }

    // Back Set Faces
    for (int x = MIN_ID_V_X + 1; x < MAX_ID_V_X; x++) {
        for (int y = MIN_ID_V_Y + 1; y < MAX_ID_V_Y; y++) {

            Voxel* voxel = Get_Voxel(glm::ivec3(x, y, MIN_ID_V_Z), rel_loc_t::CHUNK_LOC);
            if (!voxel->IsSolid()) continue;

            cube_faces_t flags = static_cast<cube_faces_t>(
                ((curr_c->Get_Voxel (glm::ivec3(x + 1   , y     , MIN_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
                ((curr_c->Get_Voxel (glm::ivec3(x - 1   , y     , MIN_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
                ((curr_c->Get_Voxel (glm::ivec3(x       , y + 1 , MIN_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
                ((curr_c->Get_Voxel (glm::ivec3(x       , y - 1 , MIN_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
                ((curr_c->Get_Voxel (glm::ivec3(x       , y     , MIN_ID_V_Z + 1))->IsAir()) << 0) |  // FRONT_FACE
                ((b_chunk->Get_Voxel(glm::ivec3(x       , y     , MAX_ID_V_Z    ))->IsAir()) << 1)    // BACK_FACE
            );

            Add_Cube_Mesh(
                glm::ivec3(x, y, MIN_ID_V_Z),
                voxel->GetColour(),
                vertex_mesh, index_mesh,
                vertex_offset, index_offset,
                flags
            );
        }
    }


    // Right Set Faces
    for (int z = MIN_ID_V_Z + 1; z < MAX_ID_V_Z; z++) {
        for (int y = MIN_ID_V_Y + 1; y < MAX_ID_V_Y; y++) {
            Voxel* voxel = Get_Voxel(glm::ivec3(MAX_ID_V_X, y, z), rel_loc_t::CHUNK_LOC);
            if (!voxel->IsSolid()) continue;

            cube_faces_t flags = static_cast<cube_faces_t>(
                ((r_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , y     , z     ))->IsAir()) << 3) |  // RIGHT_FACE
                ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X - 1  , y     , z     ))->IsAir()) << 2) |  // LEFT_FACE
                ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , y + 1 , z     ))->IsAir()) << 4) |  // TOP_FACE
                ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , y - 1 , z     ))->IsAir()) << 5) |  // BOTTOM_FACE
                ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , y     , z + 1 ))->IsAir()) << 0) |  // FRONT_FACE
                ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , y     , z - 1 ))->IsAir()) << 1)    // BACK_FACE
            );

            Add_Cube_Mesh(
                glm::ivec3(MAX_ID_V_X, y, z),
                voxel->GetColour(),
                vertex_mesh, index_mesh,
                vertex_offset, index_offset,
                flags
            );
        }
    }

    // Left Set Faces
    for (int z = MIN_ID_V_Z + 1; z < MAX_ID_V_Z; z++) {
        for (int y = MIN_ID_V_Y + 1; y < MAX_ID_V_Y; y++) {
            Voxel* voxel = Get_Voxel(glm::ivec3(MIN_ID_V_X, y, z), rel_loc_t::CHUNK_LOC);
            if (!voxel->IsSolid()) continue;

            cube_faces_t flags = static_cast<cube_faces_t>(
                ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X + 1  , y     , z     ))->IsAir()) << 3) |  // RIGHT_FACE
                ((l_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , y     , z     ))->IsAir()) << 2) |  // LEFT_FACE
                ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , y + 1 , z     ))->IsAir()) << 4) |  // TOP_FACE
                ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , y - 1 , z     ))->IsAir()) << 5) |  // BOTTOM_FACE
                ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , y     , z + 1 ))->IsAir()) << 0) |  // FRONT_FACE
                ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , y     , z - 1 ))->IsAir()) << 1)    // BACK_FACE
            );

            Add_Cube_Mesh(
                glm::ivec3(MIN_ID_V_X, y, z),
                voxel->GetColour(),
                vertex_mesh, index_mesh,
                vertex_offset, index_offset,
                flags
            );
        }
    }


    /* ======================================================================
     *                           Columns
     * ======================================================================
     */
    // Front Right Collumn Faces
    for (int y = MIN_ID_V_Y + 1; y < MAX_ID_V_Y; y++) {
        Voxel* voxel = Get_Voxel(glm::ivec3(MAX_ID_V_X, y, MAX_ID_V_Z), rel_loc_t::CHUNK_LOC);
        if (!voxel->IsSolid()) continue;

        cube_faces_t flags = static_cast<cube_faces_t>(
            ((r_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , y     , MAX_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X - 1  , y     , MAX_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , y + 1 , MAX_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , y - 1 , MAX_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((f_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , y     , MIN_ID_V_Z    ))->IsAir()) << 0) |  // FRONT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , y     , MAX_ID_V_Z - 1))->IsAir()) << 1)    // BACK_FACE
        );

        Add_Cube_Mesh(
            glm::ivec3(MAX_ID_V_X, y, MAX_ID_V_Z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }

    // Front Left Collumn Faces
    for (int y = MIN_ID_V_Y + 1; y < MAX_ID_V_Y; y++) {
        Voxel* voxel = Get_Voxel(glm::ivec3(MIN_ID_V_X, y, MAX_ID_V_Z), rel_loc_t::CHUNK_LOC);
        if (!voxel->IsSolid()) continue;

        cube_faces_t flags = static_cast<cube_faces_t>(
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X + 1  , y     , MAX_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
            ((l_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , y     , MAX_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , y + 1 , MAX_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , y - 1 , MAX_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((f_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , y     , MIN_ID_V_Z    ))->IsAir()) << 0) |  // FRONT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , y     , MAX_ID_V_Z - 1))->IsAir()) << 1)    // BACK_FACE
        );

        Add_Cube_Mesh(
            glm::ivec3(MIN_ID_V_X, y, MAX_ID_V_Z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }
    // Back Right Collumn Faces
    for (int y = MIN_ID_V_Y + 1; y < MAX_ID_V_Y; y++) {
        Voxel* voxel = Get_Voxel(glm::ivec3(MAX_ID_V_X, y, MIN_ID_V_Z), rel_loc_t::CHUNK_LOC);
        if (!voxel->IsSolid()) continue;

        cube_faces_t flags = static_cast<cube_faces_t>(
            ((r_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , y     , MAX_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X - 1  , y     , MIN_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , y + 1 , MIN_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , y - 1 , MIN_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , y     , MIN_ID_V_Z + 1))->IsAir()) << 0) |  // FRONT_FACE
            ((b_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , y     , MAX_ID_V_Z    ))->IsAir()) << 1)    // BACK_FACE
        );

        Add_Cube_Mesh(
            glm::ivec3(MAX_ID_V_X, y, MIN_ID_V_Z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }

    // Back Left Collumn Faces
    for (int y = MIN_ID_V_Y + 1; y < MAX_ID_V_Y; y++) {
        Voxel* voxel = Get_Voxel(glm::ivec3(MIN_ID_V_X, y, MIN_ID_V_Z), rel_loc_t::CHUNK_LOC);
        if (!voxel->IsSolid()) continue;

        cube_faces_t flags = static_cast<cube_faces_t>(
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X + 1  , y     , MIN_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
            ((l_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , y     , MIN_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , y + 1 , MIN_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , y - 1 , MIN_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , y     , MIN_ID_V_Z + 1))->IsAir()) << 0) |  // FRONT_FACE
            ((b_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , y     , MAX_ID_V_Z    ))->IsAir()) << 1)    // BACK_FACE
        );

        Add_Cube_Mesh(
            glm::ivec3(MIN_ID_V_X, y, MIN_ID_V_Z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }
    /* ======================================================================
     *                           TOP ROWS
     * ======================================================================
     */
    // Top front row Faces
    for (int x = MIN_ID_V_X + 1; x < MAX_ID_V_X; x++) {
        Voxel* voxel = Get_Voxel(glm::ivec3(x, MAX_ID_V_Y, MAX_ID_V_Z), rel_loc_t::CHUNK_LOC);
        if (!voxel->IsSolid()) continue;

        cube_faces_t flags = static_cast<cube_faces_t>(
            ((curr_c->Get_Voxel (glm::ivec3(x + 1   , MAX_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(x - 1   , MAX_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
            ((u_chunk->Get_Voxel(glm::ivec3(x       , MIN_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
            ((curr_c->Get_Voxel (glm::ivec3(x       , MAX_ID_V_Y - 1, MAX_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((f_chunk->Get_Voxel(glm::ivec3(x       , MAX_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 0) |  // FRONT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(x       , MAX_ID_V_Y    , MAX_ID_V_Z - 1))->IsAir()) << 1)    // BACK_FACE
        );

        Add_Cube_Mesh(
            glm::ivec3(x, MAX_ID_V_Y, MAX_ID_V_Z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }

    // Top Back row Faces
    for (int x = MIN_ID_V_X + 1; x < MAX_ID_V_X; x++) {
        Voxel* voxel = Get_Voxel(glm::ivec3(x, MAX_ID_V_Y, MIN_ID_V_Z), rel_loc_t::CHUNK_LOC);
        if (!voxel->IsSolid()) continue;

        cube_faces_t flags = static_cast<cube_faces_t>(
            ((curr_c->Get_Voxel (glm::ivec3(x + 1   , MAX_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(x - 1   , MAX_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
            ((u_chunk->Get_Voxel(glm::ivec3(x       , MIN_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
            ((curr_c->Get_Voxel (glm::ivec3(x       , MAX_ID_V_Y - 1, MIN_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((curr_c->Get_Voxel (glm::ivec3(x       , MAX_ID_V_Y    , MIN_ID_V_Z + 1))->IsAir()) << 0) |  // FRONT_FACE
            ((b_chunk->Get_Voxel(glm::ivec3(x       , MAX_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 1)    // BACK_FACE
        );

        Add_Cube_Mesh(
            glm::ivec3(x, MAX_ID_V_Y, MIN_ID_V_Z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }


     // Top Right row Faces
    for (int z = MIN_ID_V_Z + 1; z < MAX_ID_V_Z; z++) {
        Voxel* voxel = Get_Voxel(glm::ivec3(MAX_ID_V_X, MAX_ID_V_Y, z), rel_loc_t::CHUNK_LOC);
        if (!voxel->IsSolid()) continue;

        cube_faces_t flags = static_cast<cube_faces_t>(
            ((r_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , MAX_ID_V_Y    , z     ))->IsAir()) << 3) |  // RIGHT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X - 1  , MAX_ID_V_Y    , z     ))->IsAir()) << 2) |  // LEFT_FACE
            ((u_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , MIN_ID_V_Y    , z     ))->IsAir()) << 4) |  // TOP_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , MAX_ID_V_Y - 1, z     ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , MAX_ID_V_Y    , z + 1 ))->IsAir()) << 0) |  // FRONT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , MAX_ID_V_Y    , z - 1 ))->IsAir()) << 1)    // BACK_FACE
        );

        Add_Cube_Mesh(
            glm::ivec3(MAX_ID_V_X, MAX_ID_V_Y, z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }

     // Top Left row Faces
    for (int z = MIN_ID_V_Z + 1; z < MAX_ID_V_Z; z++) {
        Voxel* voxel = Get_Voxel(glm::ivec3(MIN_ID_V_X, MAX_ID_V_Y, z), rel_loc_t::CHUNK_LOC);
        if (!voxel->IsSolid()) continue;

        cube_faces_t flags = static_cast<cube_faces_t>(
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , MAX_ID_V_Y    , z     ))->IsAir()) << 3) |  // RIGHT_FACE
            ((l_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , MAX_ID_V_Y    , z     ))->IsAir()) << 2) |  // LEFT_FACE
            ((u_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , MIN_ID_V_Y    , z     ))->IsAir()) << 4) |  // TOP_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , MAX_ID_V_Y - 1, z     ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , MAX_ID_V_Y    , z + 1 ))->IsAir()) << 0) |  // FRONT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , MAX_ID_V_Y    , z - 1 ))->IsAir()) << 1)    // BACK_FACE
        );

        Add_Cube_Mesh(
            glm::ivec3(MIN_ID_V_X, MAX_ID_V_Y, z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }


    /* ======================================================================
     *                           BOTTOM ROWS
     * ======================================================================
     */
    
    // Bottom front row Faces
    for (int x = MIN_ID_V_X + 1; x < MAX_ID_V_X; x++) {
        Voxel* voxel = Get_Voxel(glm::ivec3(x, MIN_ID_V_Y, MAX_ID_V_Z), rel_loc_t::CHUNK_LOC);
        if (!voxel->IsSolid()) continue;

        cube_faces_t flags = static_cast<cube_faces_t>(
            ((curr_c->Get_Voxel (glm::ivec3(x + 1   , MIN_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(x - 1   , MIN_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(x       , MIN_ID_V_Y + 1, MAX_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
            ((d_chunk->Get_Voxel(glm::ivec3(x       , MAX_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((f_chunk->Get_Voxel(glm::ivec3(x       , MIN_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 0) |  // FRONT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(x       , MIN_ID_V_Y    , MAX_ID_V_Z - 1))->IsAir()) << 1)    // BACK_FACE
        );

        Add_Cube_Mesh(
            glm::ivec3(x, MIN_ID_V_Y, MAX_ID_V_Z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }

    // Bottom Back row Faces
    for (int x = MIN_ID_V_X + 1; x < MAX_ID_V_X; x++) {
        Voxel* voxel = Get_Voxel(glm::ivec3(x, MIN_ID_V_Y, MIN_ID_V_Z), rel_loc_t::CHUNK_LOC);
        if (!voxel->IsSolid()) continue;

        cube_faces_t flags = static_cast<cube_faces_t>(
            ((curr_c->Get_Voxel (glm::ivec3(x + 1   , MIN_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(x - 1   , MIN_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(x       , MIN_ID_V_Y + 1, MIN_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
            ((d_chunk->Get_Voxel(glm::ivec3(x       , MAX_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((curr_c->Get_Voxel (glm::ivec3(x       , MIN_ID_V_Y    , MIN_ID_V_Z + 1))->IsAir()) << 0) |  // FRONT_FACE
            ((b_chunk->Get_Voxel(glm::ivec3(x       , MIN_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 1)    // BACK_FACE
        );

        Add_Cube_Mesh(
            glm::ivec3(x, MIN_ID_V_Y, MIN_ID_V_Z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }


     // Bottom Right row Faces
    for (int z = MIN_ID_V_Z + 1; z < MAX_ID_V_Z; z++) {
        Voxel* voxel = Get_Voxel(glm::ivec3(MAX_ID_V_X, MIN_ID_V_Y, z), rel_loc_t::CHUNK_LOC);
        if (!voxel->IsSolid()) continue;

        cube_faces_t flags = static_cast<cube_faces_t>(
            ((r_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , MIN_ID_V_Y    , z     ))->IsAir()) << 3) |  // RIGHT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X - 1  , MIN_ID_V_Y    , z     ))->IsAir()) << 2) |  // LEFT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , MIN_ID_V_Y + 1, z     ))->IsAir()) << 4) |  // TOP_FACE
            ((d_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , MAX_ID_V_Y    , z     ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , MIN_ID_V_Y    , z + 1 ))->IsAir()) << 0) |  // FRONT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , MIN_ID_V_Y    , z - 1 ))->IsAir()) << 1)    // BACK_FACE
        );

        Add_Cube_Mesh(
            glm::ivec3(MAX_ID_V_X, MIN_ID_V_Y, z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }

     // Bottom Left row Faces
    for (int z = MIN_ID_V_Z + 1; z < MAX_ID_V_Z; z++) {
        Voxel* voxel = Get_Voxel(glm::ivec3(MIN_ID_V_X, MIN_ID_V_Y, z), rel_loc_t::CHUNK_LOC);
        if (!voxel->IsSolid()) continue;

        cube_faces_t flags = static_cast<cube_faces_t>(
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , MIN_ID_V_Y    , z         ))->IsAir()) << 3) |  // RIGHT_FACE
            ((l_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , MIN_ID_V_Y    , z         ))->IsAir()) << 2) |  // LEFT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , MIN_ID_V_Y + 1, z         ))->IsAir()) << 4) |  // TOP_FACE
            ((d_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , MAX_ID_V_Y    , z         ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , MIN_ID_V_Y    , z + 1     ))->IsAir()) << 0) |  // FRONT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , MIN_ID_V_Y    , z - 1     ))->IsAir()) << 1)    // BACK_FACE
        );

        Add_Cube_Mesh(
            glm::ivec3(MIN_ID_V_X, MIN_ID_V_Y, z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }




    /* ======================================================================
     *                         TOP  CORNER CUBES
     * ======================================================================
     */

    // TOP RIGHT FRONT CORNER

    const Voxel* voxel = Get_Voxel(glm::ivec3(MAX_ID_V_X, MAX_ID_V_Y, MAX_ID_V_Z), rel_loc_t::CHUNK_LOC);
    if (voxel->IsSolid()){
        cube_faces_t flags = static_cast<cube_faces_t>(0);
        flags = static_cast<cube_faces_t>(
            ((r_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , MAX_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X - 1  , MAX_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
            ((u_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , MIN_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , MAX_ID_V_Y - 1, MAX_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((f_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , MAX_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 0) |  // FRONT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , MAX_ID_V_Y    , MAX_ID_V_Z - 1))->IsAir()) << 1)    // BACK_FACE
        );
        Add_Cube_Mesh(
            glm::ivec3(MAX_ID_V_X, MAX_ID_V_Y, MAX_ID_V_Z), 
            voxel->GetColour(), 
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }

    // TOP LEFT FRONT CORNER
    voxel = Get_Voxel(glm::ivec3(MIN_ID_V_X, MAX_ID_V_Y, MAX_ID_V_Z), rel_loc_t::CHUNK_LOC);
    if (voxel->IsSolid()) {
        cube_faces_t flags = static_cast<cube_faces_t>(0);
        flags = static_cast<cube_faces_t>(

            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X + 1  , MAX_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
            ((l_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , MAX_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
            ((u_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , MIN_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , MAX_ID_V_Y - 1, MAX_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((f_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , MAX_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 0) |  // FRONT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , MAX_ID_V_Y    , MAX_ID_V_Z - 1))->IsAir()) << 1)    // BACK_FACE
        );
        Add_Cube_Mesh(
            glm::ivec3(MIN_ID_V_X, MAX_ID_V_Y, MAX_ID_V_Z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }

    // TOP RIGHT BACK CORNER
    voxel = Get_Voxel(glm::ivec3(MAX_ID_V_X, MAX_ID_V_Y, MIN_ID_V_Z), rel_loc_t::CHUNK_LOC);
    if (voxel->IsSolid()) {
        cube_faces_t flags = static_cast<cube_faces_t>(0);
        flags = static_cast<cube_faces_t>(
            ((r_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , MAX_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X - 1  , MAX_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
            ((u_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , MIN_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , MAX_ID_V_Y - 1, MIN_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , MAX_ID_V_Y    , MIN_ID_V_Z + 1))->IsAir()) << 0) |  // FRONT_FACE
            ((b_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , MAX_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 1)    // BACK_FACE
        );
        Add_Cube_Mesh(
            glm::ivec3(MAX_ID_V_X, MAX_ID_V_Y, MIN_ID_V_Z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }

    // TOP LEFT BACK CORNER
    voxel = Get_Voxel(glm::ivec3(MIN_ID_V_X, MAX_ID_V_Y, MIN_ID_V_Z), rel_loc_t::CHUNK_LOC);
    if (voxel->IsSolid()) {
        cube_faces_t flags = static_cast<cube_faces_t>(0);
        flags = static_cast<cube_faces_t>(
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , MAX_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
            ((l_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , MAX_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
            ((u_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , MIN_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , MAX_ID_V_Y - 1, MIN_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , MAX_ID_V_Y    , MIN_ID_V_Z + 1))->IsAir()) << 0) |  // FRONT_FACE
            ((b_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , MAX_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 1)    // BACK_FACE
        );
        Add_Cube_Mesh(
            glm::ivec3(MIN_ID_V_X, MAX_ID_V_Y, MIN_ID_V_Z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }



    /* ======================================================================
     *                         BOTTOM  CORNER CUBES
     * ======================================================================
     */


    
    // BOTTOM RIGHT FRONT CORNER
    voxel = Get_Voxel(glm::ivec3(MAX_ID_V_X, MIN_ID_V_Y, MAX_ID_V_Z), rel_loc_t::CHUNK_LOC);
    if (voxel->IsSolid()) {
        cube_faces_t flags = static_cast<cube_faces_t>(0);
        flags = static_cast<cube_faces_t>(
            ((r_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , MIN_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X - 1  , MIN_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , MIN_ID_V_Y + 1, MAX_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
            ((d_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , MAX_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((f_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , MIN_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 0) |  // FRONT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , MIN_ID_V_Y    , MAX_ID_V_Z - 1))->IsAir()) << 1)    // BACK_FACE
        );
        Add_Cube_Mesh(
            glm::ivec3(MAX_ID_V_X, MIN_ID_V_Y, MAX_ID_V_Z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }

    // BOTTOM LEFT FRONT CORNER
    voxel = Get_Voxel(glm::ivec3(MIN_ID_V_X, MIN_ID_V_Y, MAX_ID_V_Z), rel_loc_t::CHUNK_LOC);
    if (voxel->IsSolid()) {
        cube_faces_t flags = static_cast<cube_faces_t>(0);
        flags = static_cast<cube_faces_t>(
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X + 1  , MIN_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
            ((l_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , MIN_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , MIN_ID_V_Y + 1, MAX_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
            ((d_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , MAX_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((f_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , MIN_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 0) |  // FRONT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , MIN_ID_V_Y    , MAX_ID_V_Z - 1))->IsAir()) << 1)    // BACK_FACE
        );
        Add_Cube_Mesh(
            glm::ivec3(MIN_ID_V_X, MIN_ID_V_Y, MAX_ID_V_Z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }
    // BOTTOM RIGHT BACK CORNER
    voxel = Get_Voxel(glm::ivec3(MAX_ID_V_X, MIN_ID_V_Y, MIN_ID_V_Z), rel_loc_t::CHUNK_LOC);
    if (voxel->IsSolid()) {
        cube_faces_t flags = static_cast<cube_faces_t>(0);
        flags = static_cast<cube_faces_t>(
            ((r_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , MIN_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X - 1  , MIN_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , MIN_ID_V_Y + 1, MIN_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
            ((d_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , MAX_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MAX_ID_V_X      , MIN_ID_V_Y    , MIN_ID_V_Z + 1))->IsAir()) << 0) |  // FRONT_FACE
            ((b_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , MIN_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 1)    // BACK_FACE
        );
        Add_Cube_Mesh(
            glm::ivec3(MAX_ID_V_X, MIN_ID_V_Y, MIN_ID_V_Z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }

    // BOTTOM LEFT BACK CORNER
    voxel = Get_Voxel(glm::ivec3(MIN_ID_V_X, MIN_ID_V_Y, MIN_ID_V_Z), rel_loc_t::CHUNK_LOC);
    if (voxel->IsSolid()) {
        cube_faces_t flags = static_cast<cube_faces_t>(0);
        flags = static_cast<cube_faces_t>(
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X  + 1 , MIN_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 3) |  // RIGHT_FACE
            ((l_chunk->Get_Voxel(glm::ivec3(MAX_ID_V_X      , MIN_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 2) |  // LEFT_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , MIN_ID_V_Y + 1, MIN_ID_V_Z    ))->IsAir()) << 4) |  // TOP_FACE
            ((d_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , MAX_ID_V_Y    , MIN_ID_V_Z    ))->IsAir()) << 5) |  // BOTTOM_FACE
            ((curr_c->Get_Voxel (glm::ivec3(MIN_ID_V_X      , MIN_ID_V_Y    , MIN_ID_V_Z + 1))->IsAir()) << 0) |  // FRONT_FACE
            ((b_chunk->Get_Voxel(glm::ivec3(MIN_ID_V_X      , MIN_ID_V_Y    , MAX_ID_V_Z    ))->IsAir()) << 1)    // BACK_FACE
        );
        Add_Cube_Mesh(
            glm::ivec3(MIN_ID_V_X, MIN_ID_V_Y, MIN_ID_V_Z),
            voxel->GetColour(),
            vertex_mesh, index_mesh,
            vertex_offset, index_offset,
            flags
        );
    }

    mesh.Clear_Mesh();
    mesh.Configure_Mesh(
        vertex_mesh.data(),
        sizeof(GLfloat),
        (GLsizei)vertex_mesh.size(),
        GL_FLOAT,
        FACE_NUM_ELEMENTS
    );
    mesh.Configure_Index_Buffer(
        index_mesh.data(),
        sizeof(GLuint),
        (GLsizei)index_mesh.size()
    );

    mesh.Add_Vertex_Set(0, 1, 0);
    mesh.Add_Vertex_Set(1, 1, 1);
    mesh.Add_Vertex_Set(2, 3, 2);

}


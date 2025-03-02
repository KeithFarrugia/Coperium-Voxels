#include "World.h"
#include "../Compact Data/Cube Mesh/CCMS.h"

/* ============================================================================
 * --------------------------- Get_X_Axis_Neighbours
 * Determines the left and right neighbouring chunks for a given chunk.
 *
 * ------ Parameters ------
 * w: Reference to the world object containing all sectors and chunks.
 * chunk_id: The location ID of the current chunk within its sector.
 * sector_id: The location ID of the sector that contains the current chunk.
 *
 * ------ Returns ------
 * A pointer to the left or right neighbouring chunk, or nullptr if not found.
 * ============================================================================
 */
Chunk* Get_X_Neighbour(World& w, const chunk_loc_t chunk_id, const sector_loc_t sector_id, bool is_right) {
    Sector* curr_s = w.Get_Sector(sector_id);

    // Check if the current sector is valid
    if (curr_s == nullptr) {
        return nullptr;  // Sector does not exist
    }

    if (is_right) {
        // If in the right-most sector
        if (sector_id.X() == MAX_ID_S_X) {
            return nullptr;  // No chunk on the right
        }

        // If chunk is in the right-most position in current sector
        if (chunk_id.X() == MAX_ID_C_X) {
            sector_loc_t r_sector_id = sector_loc_t::Compact(glm::ivec2(sector_id.X() + 1, sector_id.Z()));
            Sector* right_sector = w.Get_Sector(r_sector_id);
            if (right_sector == nullptr) {
                return nullptr;  // Right sector does not exist
            }
            return right_sector->Get_Chunk(chunk_loc_t::Compact(glm::ivec3(MIN_ID_C_X, chunk_id.Y(), chunk_id.Z())));
        }
        else {
            // Right chunk in the same sector
            Chunk* right_chunk = curr_s->Get_Chunk(chunk_loc_t::Compact(glm::ivec3(chunk_id.X() + 1, chunk_id.Y(), chunk_id.Z())));
            return right_chunk;  // This will be nullptr if chunk doesn't exist
        }
    }
    else {
        // If in the left-most sector
        if (sector_id.X() == MIN_ID_S_X) {
            return nullptr;  // No chunk on the left
        }

        // If chunk is in the left-most position in current sector
        if (chunk_id.X() == MIN_ID_C_X) {
            sector_loc_t l_sector_id = sector_loc_t::Compact(glm::ivec2(sector_id.X() - 1, sector_id.Z()));
            Sector* left_sector = w.Get_Sector(l_sector_id);
            if (left_sector == nullptr) {
                return nullptr;  // Left sector does not exist
            }
            return left_sector->Get_Chunk(chunk_loc_t::Compact(glm::ivec3(MAX_ID_C_X, chunk_id.Y(), chunk_id.Z())));
        }
        else {
            // Left chunk in the same sector
            Chunk* left_chunk = curr_s->Get_Chunk(chunk_loc_t::Compact(glm::ivec3(chunk_id.X() - 1, chunk_id.Y(), chunk_id.Z())));
            return left_chunk;  // This will be nullptr if chunk doesn't exist
        }
    }
}

/* ============================================================================
 * --------------------------- Get_Y_Axis_Neighbours
 * Determines the upper and lower neighbouring chunks for a given chunk.
 *
 * ------ Parameters ------
 * w: Reference to the world object containing all sectors and chunks.
 * chunk_id: The location ID of the current chunk within its sector.
 * sector_id: The location ID of the sector that contains the current chunk.
 *
 * ------ Returns ------
 * A pointer to the upper or lower neighbouring chunk, or nullptr if not found.
 * ============================================================================
 */
Chunk* Get_Y_Neighbour(Sector* curr_s, const chunk_loc_t chunk_id, bool is_up) {
    // Check if the current sector is valid
    if (curr_s == nullptr) {
        return nullptr;  // Sector does not exist
    }

    if (is_up) {
        // No chunks above the top
        if (chunk_id.Y() == MAX_ID_C_Y) {
            return nullptr;
        }
        else {
            // Up chunk in the same sector
            return curr_s->Get_Chunk(chunk_loc_t::Compact(glm::ivec3(chunk_id.X(), chunk_id.Y() + 1, chunk_id.Z())));
        }
    }
    else {
        // No chunks below the bottom
        if (chunk_id.Y() == MIN_ID_C_Y) {
            return nullptr;
        }
        else {
            // Down chunk in the same sector
            return curr_s->Get_Chunk(chunk_loc_t::Compact(glm::ivec3(chunk_id.X(), chunk_id.Y() - 1, chunk_id.Z())));
        }
    }
}

/* ============================================================================
 * --------------------------- Get_Z_Axis_Neighbours
 * Determines the front and back neighbouring chunks for a given chunk.
 *
 * ------ Parameters ------
 * w: Reference to the world object containing all sectors and chunks.
 * chunk_id: The location ID of the current chunk within its sector.
 * sector_id: The location ID of the sector that contains the current chunk.
 *
 * ------ Returns ------
 * A pointer to the front or back neighbouring chunk, or nullptr if not found.
 * ============================================================================
 */
Chunk* Get_Z_Neighbour(World& w, const chunk_loc_t chunk_id, const sector_loc_t sector_id, bool is_front) {
    Sector* curr_s = w.Get_Sector(sector_id);

    // Check if the current sector is valid
    if (curr_s == nullptr) {
        return nullptr;  // Sector does not exist
    }

    if (is_front) {
        // If in the front-most sector
        if (sector_id.Z() == MAX_ID_S_Z) {
            return nullptr;  // No chunk in front
        }

        // If chunk is in the front-most position in current sector
        if (chunk_id.Z() == MAX_ID_C_Z) {
            sector_loc_t f_sector_id = sector_loc_t::Compact(glm::ivec2(sector_id.X(), sector_id.Z() + 1));
            Sector* front_sector = w.Get_Sector(f_sector_id);
            if (front_sector == nullptr) {
                return nullptr;  // Front sector does not exist
            }
            return front_sector->Get_Chunk(chunk_loc_t::Compact(glm::ivec3(chunk_id.X(), chunk_id.Y(), MIN_ID_C_Z)));
        }
        else {
            // Front chunk in the same sector
            return curr_s->Get_Chunk(chunk_loc_t::Compact(glm::ivec3(chunk_id.X(), chunk_id.Y(), chunk_id.Z() + 1)));
        }
    }
    else {
        // If in the back-most sector
        if (sector_id.Z() == MIN_ID_S_Z) {
            return nullptr;  // No chunk in the back
        }

        // If chunk is in the back-most position in current sector
        if (chunk_id.Z() == MIN_ID_C_Z) {
            sector_loc_t b_sector_id = sector_loc_t::Compact(glm::ivec2(sector_id.X(), sector_id.Z() - 1));
            Sector* back_sector = w.Get_Sector(b_sector_id);
            if (back_sector == nullptr) {
                return nullptr;  // Back sector does not exist
            }
            return back_sector->Get_Chunk(chunk_loc_t::Compact(glm::ivec3(chunk_id.X(), chunk_id.Y(), MAX_ID_C_Z)));
        }
        else {
            // Back chunk in the same sector
            return curr_s->Get_Chunk(chunk_loc_t::Compact(glm::ivec3(chunk_id.X(), chunk_id.Y(), chunk_id.Z() - 1)));
        }
    }
}

void Chunk::Generate_Mesh(
    World& w, const chunk_loc_t chunk_id, const sector_loc_t sector_id, const Chunk& generic_chunk
) {

    std::vector<GLfloat>    vertex_mesh;
    std::vector<GLuint>     index_mesh; 
    vertex_mesh.reserve(static_cast<size_t>(16) * 1024);
    index_mesh.reserve(static_cast<size_t>(4) * 1024);
    int vertex_offset = 0;
    int index_offset = 0;

    Sector* curr_s = w.Get_Sector(sector_id);
    Chunk* curr_c = curr_s->Get_Chunk(chunk_id);

    // Get neighbouring chunks in X, Y, and Z directions
    Chunk* r_chunk = Get_X_Neighbour(w, chunk_id, sector_id, true);
    Chunk* l_chunk = Get_X_Neighbour(w, chunk_id, sector_id, false);

    Chunk* u_chunk = Get_Y_Neighbour(curr_s, chunk_id, true);
    Chunk* d_chunk = Get_Y_Neighbour(curr_s, chunk_id, false);

    Chunk* f_chunk = Get_Z_Neighbour(w, chunk_id, sector_id, true);
    Chunk* b_chunk = Get_Z_Neighbour(w, chunk_id, sector_id, false);

    if (r_chunk == nullptr) r_chunk = const_cast<Chunk*>(&generic_chunk);
    if (l_chunk == nullptr) l_chunk = const_cast<Chunk*>(&generic_chunk);
    if (u_chunk == nullptr) u_chunk = const_cast<Chunk*>(&generic_chunk);
    if (d_chunk == nullptr) d_chunk = const_cast<Chunk*>(&generic_chunk);
    if (f_chunk == nullptr) f_chunk = const_cast<Chunk*>(&generic_chunk);
    if (b_chunk == nullptr) b_chunk = const_cast<Chunk*>(&generic_chunk);

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

    Voxel* voxel = Get_Voxel(glm::ivec3(MAX_ID_V_X, MAX_ID_V_Y, MAX_ID_V_Z), rel_loc_t::CHUNK_LOC);
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


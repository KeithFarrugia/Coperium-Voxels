#include "World.h"

/* ============================================================================
 * --------------------------- ~World (Constructor)
 * Default Constructor
 * ============================================================================
 */
World::World() {}

/* ============================================================================
 * --------------------------- ~World (Destructor)
 * Destructor to clear the sectors upon destruction of the World object.
 * ============================================================================
 */
World::~World() {
    sectors.Clear();
}

/* ============================================================================
 * --------------------------- Get_Voxel
 * Retrieves a voxel at a specified position and relative location.
 *
 * ------ Parameters ------
 * pos:   The 3D position of the voxel in the world.
 * rel:   The relative location type (used to determine chunk/sector).
 *
 * ------ Returns ------
 * Pointer to the voxel at the specified location.
 * ============================================================================
 */
Voxel* World::Get_Voxel(glm::ivec3 pos, rel_loc_t rel) {
    Chunk* c = Get_Chunk(pos, rel);
    (c == nullptr) ? nullptr : c->Get_Voxel(pos, rel);
}

/* ============================================================================
 * --------------------------- Get_Chunk
 * Retrieves the chunk that contains the voxel at the specified position and
 * relative location.
 *
 * ------ Parameters ------
 * pos:   The 3D position of the voxel in the world.
 * rel:   The relative location type (used to determine chunk/sector).
 *
 * ------ Returns ------
 * Pointer to the chunk that contains the voxel at the specified location.
 * ============================================================================
 */
Chunk* World::Get_Chunk(glm::ivec3 pos, rel_loc_t rel) {
    Sector* s = Get_Sector(pos, rel);
    (s == nullptr) ? nullptr : s->Get_Chunk(pos, rel);
}

/* ============================================================================
 * --------------------------- Get_Sector
 * Retrieves the sector that contains the chunk at the specified position and
 * relative location.
 *
 * ------ Parameters ------
 * pos:   The 3D position of the voxel in the world.
 * rel:   The relative location type (used to determine chunk/sector).
 *
 * ------ Returns ------
 * Pointer to the sector that contains the chunk at the specified location.
 * ============================================================================
 */
Sector* World::Get_Sector(glm::ivec3 pos, rel_loc_t rel) {
    return sectors.Find(
        sector_loc_t::Compact(
            Convert_Loc_2_ID(
                pos,
                rel,
                rel_loc_t::SECTOR_LOC
            )
        )
    );
}

/* ============================================================================
 * --------------------------- Create_Voxel
 * Creates a voxel at the specified position within its sector, using the
 * provided voxel data.
 *
 * ------ Parameters ------
 * data:  The voxel data to be used when creating the voxel.
 * ============================================================================
 */
void World::Create_Voxel(vox_data_t data) {
    data.position = Convert_Loc_2_ID(
        data.position,
        data.rel,
        rel_loc_t::SECTOR_LOC
    );

    data.rel = SECTOR_LOC;

    Sector* s = sectors.Find(sector_loc_t::Compact(data.position));

    if (s != nullptr) { s->Create_Voxel(data); }
}

/* ============================================================================
 * --------------------------- Create_Chunk
 * Creates a chunk at the specified position and relative location within
 * its sector.
 *
 * ------ Parameters ------
 * pos:   The 3D position of the chunk in the world.
 * rel:   The relative location type (used to determine chunk/sector).
 * ============================================================================
 */
void World::Create_Chunk(glm::ivec3 pos, rel_loc_t rel) {
    pos = Convert_Loc_2_ID(pos, rel, rel_loc_t::SECTOR_LOC);
    rel = SECTOR_LOC;

    Sector* s = sectors.Find(sector_loc_t::Compact(pos));

    if (s != nullptr) { s->Create_Chunk(pos, rel); }
}

/* ============================================================================
 * --------------------------- Create_Sector
 * Creates a new sector at the specified position and relative location.
 *
 * ------ Parameters ------
 * pos:   The 3D position of the sector in the world.
 * rel:   The relative location type (used to determine chunk/sector).
 * ============================================================================
 */
void World::Create_Sector(glm::ivec3 pos, rel_loc_t rel) {
    sectors.Create_Node(sector_loc_t::Compact(
        Convert_Loc_2_ID(pos, rel, rel_loc_t::SECTOR_LOC))
    );
}

/* ============================================================================
 * --------------------------- Remove_Voxel
 * Removes the voxel at the specified position and relative location.
 *
 * ------ Parameters ------
 * pos:   The 3D position of the voxel in the world.
 * rel:   The relative location type (used to determine chunk/sector).
 * ============================================================================
 */
void World::Remove_Voxel(glm::ivec3 pos, rel_loc_t rel) {
    Chunk* c = Get_Chunk(pos, rel); 
    if (c != nullptr) { Get_Voxel(pos, rel); }
}

/* ============================================================================
 * --------------------------- Remove_Chunk
 * Removes the chunk at the specified position and relative location.
 *
 * ------ Parameters ------
 * pos:   The 3D position of the chunk in the world.
 * rel:   The relative location type (used to determine chunk/sector).
 * ============================================================================
 */
void World::Remove_Chunk(glm::ivec3 pos, rel_loc_t rel) {
    Sector* s = Get_Sector(pos, rel);
    if (s != nullptr) { Remove_Chunk(pos, rel); }
}

/* ============================================================================
 * --------------------------- Remove_Sector
 * Removes the sector at the specified position and relative location.
 *
 * ------ Parameters ------
 * pos:   The 3D position of the sector in the world.
 * rel:   The relative location type (used to determine chunk/sector).
 * ============================================================================
 */
void World::Remove_Sector(glm::ivec3 pos, rel_loc_t rel) {
    glm::ivec3 pos = Convert_Loc_2_ID(
        pos,
        rel,
        rel_loc_t::SECTOR_LOC
    );

    sectors.Remove(
        sector_loc_t::Compact(
            Convert_Loc_2_ID(
                pos, rel,
                rel_loc_t::SECTOR_LOC
            )
        )
    );
}

/* ============================================================================
 * --------------------------- Get_All_Sectors
 * Retrieves a pointer to all the sectors in the world.
 *
 * ------ Returns ------
 * Pointer to the collection of sectors.
 * ============================================================================
 */
sectors_t* World::Get_All_Sectrs() {
    return &sectors;
}
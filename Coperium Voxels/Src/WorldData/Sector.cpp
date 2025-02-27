#include "World.h"

/* ============================================================================
 * --------------------------- Sector
 * Constructor for the Sector class
 * ============================================================================
 */
Sector::Sector() {}

/* ============================================================================
 * --------------------------- Sector (Copy Constructor)
 * Copy Constructor
 * ============================================================================
 */
Sector::Sector(const Sector& other){
    chunks = other.chunks;
}
/* ============================================================================
 * --------------------------- ~Sector
 * Destructor for the Sector class, ensures the chunk tree is cleared.
 * ============================================================================
 */
Sector::~Sector() {
    chunks.Clear();
}

/* ============================================================================
 * --------------------------- Get_Voxel
 * Retrieves a voxel from the sector using a position and relative location.
 *
 * ------ Parameters ------
 * pos:   The 3D position to locate the voxel.
 * rel:   The relative location enum to specify the hierarchy 
 *        (sector, chunk, voxel).
 *
 * ------ Returns ------
 * Pointer to the Voxel found at the given position and relative location.
 * ============================================================================
 */
Voxel* Sector::Get_Voxel(glm::ivec3 pos, rel_loc_t rel) {
    Chunk* c = Get_Chunk(pos, rel);
    return (c == nullptr) ? nullptr : c->Get_Voxel(pos, rel);
}

/* ============================================================================
 * --------------------------- Get_Chunk
 * Retrieves a chunk from the sector using a position and relative location.
 *
 * ------ Parameters ------
 * pos:   The 3D position to locate the chunk.
 * rel:   The relative location enum to specify the hierarchy 
 *        (sector, chunk, voxel).
 *
 * ------ Returns ------
 * Pointer to the Chunk found at the given position and relative location.
 * ============================================================================
 */
Chunk* Sector::Get_Chunk(glm::ivec3 pos, rel_loc_t rel) {
    return chunks.Find(
        chunk_loc_t::Compact(
            Convert_Loc_2_ID(
                pos, rel, rel_loc_t::CHUNK_LOC
            )
        )
    );
}

/* ============================================================================
 * --------------------------- Get_Chunk
 * Retrieves a chunk from the sector using a position and relative location.
 *
 * ------ Parameters ------
 * pos:   The 3D position to locate the chunk.
 * rel:   The relative location enum to specify the hierarchy
 *        (sector, chunk, voxel).
 *
 * ------ Returns ------
 * Pointer to the Chunk found at the given position and relative location.
 * ============================================================================
 */
Chunk* Sector::Get_Chunk(chunk_loc_t id){
    return chunks.Find(id);
}

/* ============================================================================
 * --------------------------- Create_Voxel
 * Creates a new voxel within the sector at the specified position and 
 * hierarchy.
 *
 * ------ Parameters ------
 * data:   The voxel data structure containing position, relative 
 * location, and voxel data.
 *
 * ------ Operation ------
 * Retrieves the appropriate chunk using the voxel's 
 * data and creates the voxel inside it.
 * ============================================================================
 */
void Sector::Create_Voxel(vox_data_t data) {
    chunk_loc_t loc = chunk_loc_t::Compact(
        Convert_Loc_2_ID(data.position, data.rel, rel_loc_t::CHUNK_LOC)
    );
    
    Chunk* c = chunks.Find(loc);
    if (c != nullptr) {
        c->Create_Voxel(data); return;
    }
    c = chunks.Insert(loc, Chunk());

    if (c != nullptr) {
        c->Create_Voxel(data); return;
    }
}

/* ============================================================================
 * --------------------------- Create_Chunk
 * Creates a new chunk within the sector at the specified
 * position and hierarchy.
 *
 * ------ Parameters ------
 * pos:   The 3D position to create the chunk.
 * rel:   The relative location enum to specify the 
 *        hierarchy (sector, chunk, voxel).
 * ============================================================================
 */
void Sector::Create_Chunk(glm::ivec3 pos, rel_loc_t rel) {
    chunks.Insert(
        chunk_loc_t::Compact(
            Convert_Loc_2_ID(pos, rel, rel_loc_t::CHUNK_LOC)
        ),
        Chunk()
    );
}

/* ============================================================================
 * --------------------------- Remove_Voxel
 * Removes a voxel from the sector at the specified position and hierarchy.
 *
 * ------ Parameters ------
 * pos:   The 3D position to remove the voxel.
 * rel:   The relative location enum to specify the hierarchy 
 *        (sector, chunk, voxel).
 * ============================================================================
 */
void Sector::Remove_Voxel(glm::ivec3 pos, rel_loc_t rel) {
    Chunk* c = Get_Chunk(pos, rel);
    if (c != nullptr) { c->Remove_Voxel(pos, rel); }
}

/* ============================================================================
 * --------------------------- Remove_Chunk
 * Removes a chunk from the sector at the specified position and hierarchy.
 *
 * ------ Parameters ------
 * pos:   The 3D position to remove the chunk.
 * rel:   The relative location enum to specify the
 *        hierarchy (sector, chunk, voxel).
 * ============================================================================
 */
void Sector::Remove_Chunk(glm::ivec3 pos, rel_loc_t rel) {
    chunks.Remove(chunk_loc_t::Compact(
        Convert_Loc_2_ID(pos, rel, rel_loc_t::CHUNK_LOC))
    );
}

/* ============================================================================
 * --------------------------- Get_All_Chunks
 * Retrieves all chunks stored in the sector.
 *
 * ------ Returns ------
 * Pointer to the chunks_t structure, which stores all chunks in the sector.
 * Currently returns nullptr.
 * ============================================================================
 */
chunks_t* Sector::Get_All_Chunks() {
    return &chunks;
}

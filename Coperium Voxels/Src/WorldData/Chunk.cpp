#include "World.h"

/* ============================================================================
 * --------------------------- Chunk
 * Constructor for Chunk class, initializing a new chunk
 * ============================================================================
 */
Chunk::Chunk() {
    voxels.resize(MAX_VOX_LOC);
}

/* ============================================================================
 * --------------------------- Chunk (Copy Constructor)
 * Copy Constructor
 * ============================================================================
 */
Chunk::Chunk(const Chunk& other){
    voxels = other.voxels;
}

/* ============================================================================
 * --------------------------- ~Chunk
 * Destructor for Chunk class, responsible for cleanup
 * ============================================================================
 */
Chunk::~Chunk() {
    voxels.clear();
}

/* ============================================================================
 * --------------------------- Get_Voxel
 * Retrieves a voxel from the chunk based on the position and relative location
 *
 * ------ Parameters ------
 * pos:    The position (ivec3) of the voxel
 * rel:    The relative location type (rel_loc_t)
 *
 * ------ Returns ------
 * Voxel pointer if the voxel exists, nullptr otherwise
 * ============================================================================
 */
Voxel* Chunk::Get_Voxel(glm::ivec3 pos, rel_loc_t rel) {
    return &voxels[
        voxel_loc_t::Compact(
            Convert_Loc_2_Offset(pos, rel, rel_loc_t::CHUNK_LOC)
        ).location
    ];
}

/* ============================================================================
 * --------------------------- Create_Voxel
 * Creates a voxel in the chunk with the given voxel data
 *
 * ------ Parameters ------
 * data:    The data (vox_data_t) used to create the voxel
 * ============================================================================
 */
void Chunk::Create_Voxel(vox_data_t data) {
    Voxel vox(data);
    voxels[
        voxel_loc_t::Compact(
            Convert_Loc_2_Offset(data.position, data.rel, rel_loc_t::CHUNK_LOC)
        ).location
    ] = vox;
}

/* ============================================================================
 * --------------------------- Remove_Voxel
 * Removes a voxel from the chunk based on the position and relative location
 *
 * ------ Parameters ------
 * pos:    The position (ivec3) of the voxel to remove
 * rel:    The relative location type (rel_loc_t)
 * ============================================================================
 */
void Chunk::Remove_Voxel(glm::ivec3 pos, rel_loc_t rel) {
    voxels[
        voxel_loc_t::Compact(
            Convert_Loc_2_Offset(pos, rel, rel_loc_t::CHUNK_LOC)
        ).location
    ].SetType(voxel_type_t::AIR);
}

/* ============================================================================
 * --------------------------- Get_All_Voxels
 * Retrieves all the voxels contained within the chunk
 *
 * ------ Returns ------
 * A container (voxels_t) with all the voxels in the chunk
 * ============================================================================
 */
voxels_t* Chunk::Get_All_Voxels() {
    return &voxels;
}

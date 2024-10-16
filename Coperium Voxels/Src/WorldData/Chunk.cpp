#include "World.h"

/* ============================================================================
 * --------------------------- Chunk
 * Constructor for Chunk class, initializing a new chunk
 * ============================================================================
 */
Chunk::Chunk() {}

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
    voxels[1];
    return &voxels[
        voxel_t::Compress(
            Convert_Loc_2_Offset(pos, rel, rel_loc_t::CHUNK_LOC)
        )
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
}

/* ============================================================================
 * --------------------------- Get_All_Voxels
 * Retrieves all the voxels contained within the chunk
 *
 * ------ Returns ------
 * A container (voxels_t) with all the voxels in the chunk
 * ============================================================================
 */
voxels_t Chunk::Get_All_Voxels() {
    return voxels_t();
}

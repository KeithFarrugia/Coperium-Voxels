#ifndef WORLD_CONSTANTS_H
#define WORLD_CONSTANTS_H
#include <GLM/glm.hpp>

/* ---------------------------------
 * NUMBER OF VOXELS IN A SECTOR     */
inline constexpr int SECTR_SIZE_X = 512;    // 16 * 32
inline constexpr int SECTR_SIZE_Z = 512;    // 16 * 32

/* ---------------------------------
 * NUMBER OF VOXELS IN A SECTOR     */
inline constexpr int CHUNK_SIZE_X = 16;
inline constexpr int CHUNK_SIZE_Y = 64;
inline constexpr int CHUNK_SIZE_Z = 16;

inline constexpr int MAX_VOX_LOC = CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z;

/* ---------------------------------
 * MAX ID VALUE OF A SECTOR         */
inline constexpr int MIN_ID_S_X = -16384;
inline constexpr int MAX_ID_S_X = 16383;
inline constexpr int MIN_ID_S_Z = -16384;
inline constexpr int MAX_ID_S_Z = 16383;

/* ---------------------------------
 * MAX ID VALUE OF A CHUNK          */
inline constexpr int MIN_ID_C_X = 0;
inline constexpr int MAX_ID_C_X = 31;
inline constexpr int MIN_ID_C_Y = -31;
inline constexpr int MAX_ID_C_Y = 31;
inline constexpr int MIN_ID_C_Z = 0;
inline constexpr int MAX_ID_C_Z = 31;

/* ---------------------------------
 * MAX ID VALUE OF A VOXEL          */
inline constexpr int MIN_ID_V_X = 0;
inline constexpr int MAX_ID_V_X = 15;
inline constexpr int MIN_ID_V_Y = 0;
inline constexpr int MAX_ID_V_Y = 63;
inline constexpr int MIN_ID_V_Z = 0;
inline constexpr int MAX_ID_V_Z = 15;



/* ============================================================================
 * --------------------------- NUM_CHUNKS_X / NUM_CHUNKS_Z / NUM_CHUNKS_Y
 * Defines the number of valid chunk indices for x, z, and y coordinates.
 *
 * For chunk x and z:
 *    MIN_ID_C_X = 0, MAX_ID_C_X = 31 -> 32 values (a power-of-two)
 *
 * For chunk y:
 *    MIN_ID_C_Y = -31, MAX_ID_C_Y = 31 -> 63 values (not a power-of-two)
 * ============================================================================
 */
inline constexpr int NUM_CHUNKS_X = MAX_ID_C_X - MIN_ID_C_X + 1; // 32
inline constexpr int NUM_CHUNKS_Z = MAX_ID_C_Z - MIN_ID_C_Z + 1; // 32
inline constexpr int NUM_CHUNKS_Y = MAX_ID_C_Y - MIN_ID_C_Y + 1; // 63

/* ============================================================================
 * --------------------------- MASK_CHUNKS_X / MASK_CHUNKS_Z
 * Bitmask values used for branchless wrap-around on chunk x and z coordinates.
 *
 * Since there are 32 values (a power-of-two), the mask is NUM_CHUNKS - 1.
 * ============================================================================
 */
inline constexpr int MASK_CHUNKS_X = NUM_CHUNKS_X - 1; // 31 (0x1F)
inline constexpr int MASK_CHUNKS_Z = NUM_CHUNKS_Z - 1; // 31 (0x1F)
inline constexpr int MASK_CHUNKS = NUM_CHUNKS_X - 1; // 31 (0x1F)



inline constexpr int NUM_VOXELS_X = MAX_ID_V_X - MIN_ID_V_X + 1; // 16
inline constexpr int NUM_VOXELS_Y = MAX_ID_V_Y - MIN_ID_V_Y + 1; // 64
inline constexpr int NUM_VOXELS_Z = MAX_ID_V_Z - MIN_ID_V_Z + 1; // 16

inline constexpr int MASK_VOXELS_X = NUM_VOXELS_X - 1; // 15 (0xF)
inline constexpr int MASK_VOXELS_Y = NUM_VOXELS_Y - 1; // 63 (0x3F)
inline constexpr int MASK_VOXELS_Z = NUM_VOXELS_Z - 1; // 15 (0xF)


/* ============================================================================
 * --------------------------- Other Sizes
 * Other Generic Sizes used
 * ============================================================================
 */
inline const glm::vec3 HALF_CHUNK = glm::vec3(
    CHUNK_SIZE_X * 0.5f,
    CHUNK_SIZE_Y * 0.5f,
    CHUNK_SIZE_Z * 0.5f
);


#endif // !WORLD_CONSTANTS_H

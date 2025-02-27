#ifndef WORLD_CONSTANTS_H
#define WORLD_CONSTANTS_H


/* ---------------------------------
 * NUMBER OF VOXELS IN A SECTOR     */
constexpr int SECTR_SIZE_X = 512;    // 16 * 32
constexpr int SECTR_SIZE_Z = 512;    // 16 * 32

/* ---------------------------------
 * NUMBER OF VOXELS IN A SECTOR     */
constexpr int CHUNK_SIZE_X = 16;
constexpr int CHUNK_SIZE_Y = 64;
constexpr int CHUNK_SIZE_Z = 16;

constexpr int MAX_VOX_LOC = CHUNK_SIZE_X *
CHUNK_SIZE_Y *
CHUNK_SIZE_Z;

/* ---------------------------------
 * MAX ID VALUE OF A SECTOR         */
constexpr int MIN_ID_S_X = -16384;  constexpr int MAX_ID_S_X = 16383;
constexpr int MIN_ID_S_Z = -16384;  constexpr int MAX_ID_S_Z = 16383;

/* ---------------------------------
 * MAX ID VALUE OF A CHUNK          */
constexpr int MIN_ID_C_X =   0;     constexpr int MAX_ID_C_X = 31;
constexpr int MIN_ID_C_Y = -31;     constexpr int MAX_ID_C_Y = 31;
constexpr int MIN_ID_C_Z =   0;     constexpr int MAX_ID_C_Z = 31;

/* ---------------------------------
 * MAX ID VALUE OF A VOXEL          */
constexpr int MIN_ID_V_X = 0;       constexpr int MAX_ID_V_X = 15;
constexpr int MIN_ID_V_Y = 0;       constexpr int MAX_ID_V_Y = 63;
constexpr int MIN_ID_V_Z = 0;       constexpr int MAX_ID_V_Z = 15;



#endif // !WORLD_CONSTANTS_H


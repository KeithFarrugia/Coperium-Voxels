#pragma once
#ifndef CREATE_GENERIC_CHUNKS
#define CREATE_GENERIC_CHUNKS
#include "World.h"

/* ============================================================================
 * --------------------------- Create_Air_Chunk
 * Populates a Chunk with air voxels.
 *
 * Each voxel is set to type AIR, non-solid, and transparent.
 * ============================================================================
 */
inline void Create_Air_Chunk(Chunk& chunk) {
    for (int z = 0; z < CHUNK_SIZE_Z; ++z) {
        for (int y = 0; y < CHUNK_SIZE_Y; ++y) {
            for (int x = 0; x < CHUNK_SIZE_X; ++x) {
                vox_data_t data;
                data.position = glm::ivec3(x, y, z);
                data.colour = glm::ivec3(255, 255, 255); // Air voxels can have a default colour.
                data.type = voxel_type_t::AIR;
                data.solid = false;
                data.transparency = true;
                data.rel = rel_loc_t::WORLD_LOC; // Adjust if needed.
                chunk.Create_Voxel(data);
            }
        }
    }
}

/* ============================================================================
 * --------------------------- Create_Air_Chunk
 * Creates and returns a Chunk filled with air voxels.
 *
 * Each voxel is set to type AIR, non-solid, and transparent.
 * ============================================================================
 */
inline Chunk Create_Air_Chunk() {
    Chunk chunk;
    for (int z = 0; z < CHUNK_SIZE_Z; ++z) {
        for (int y = 0; y < CHUNK_SIZE_Y; ++y) {
            for (int x = 0; x < CHUNK_SIZE_X; ++x) {
                vox_data_t data;
                data.position = glm::ivec3(x, y, z);
                data.colour = glm::ivec3(255, 255, 255); // Default colour for air.
                data.type = voxel_type_t::AIR;
                data.solid = false;
                data.transparency = true;
                data.rel = rel_loc_t::WORLD_LOC; // Adjust if needed.
                chunk.Create_Voxel(data);
            }
        }
    }
    return chunk;
}

/* ============================================================================
 * --------------------------- Create_Solid_Chunk
 * Populates a Chunk with solid generic voxels.
 *
 * Each voxel is set to type NORMAL, solid, and opaque.
 * ============================================================================
 */
inline void Create_Solid_Chunk(Chunk& chunk) {
    for (int z = 0; z < CHUNK_SIZE_Z; ++z) {
        for (int y = 0; y < CHUNK_SIZE_Y; ++y) {
            for (int x = 0; x < CHUNK_SIZE_X; ++x) {
                vox_data_t data;
                data.position = glm::ivec3(x, y, z);
                data.colour = glm::ivec3(x, (int)(y / 4.0f), z); // Generic solid voxel colour.
                data.type = voxel_type_t::NORMAL;
                data.solid = true;
                data.transparency = false;
                data.rel = rel_loc_t::WORLD_LOC; // Adjust if needed.
                chunk.Create_Voxel(data);
            }
        }
    }
}
/* ============================================================================
 * --------------------------- Create_Solid_Chunk
 * Creates and returns a Chunk filled with solid generic voxels.
 *
 * Each voxel is set to type NORMAL, solid, and opaque.
 * ============================================================================
 */
inline Chunk Create_Solid_Chunk() {
    Chunk chunk;
    for (int z = 0; z < CHUNK_SIZE_Z; ++z) {
        for (int y = 0; y < CHUNK_SIZE_Y; ++y) {
            for (int x = 0; x < CHUNK_SIZE_X; ++x) {
                vox_data_t data;
                data.position = glm::ivec3(x, y, z);
                data.colour = glm::ivec3(x, (int)(y / 4.0f), z); // Generic solid voxel colour.
                data.type = voxel_type_t::NORMAL;
                data.solid = true;
                data.transparency = false;
                data.rel = rel_loc_t::WORLD_LOC; // Adjust if needed.
                chunk.Create_Voxel(data);
            }
        }
    }
    return chunk;
}

inline void Create_Solid_Chunk_Func(Chunk& chunk, glm::ivec3 offset) {
    for (int z = 0; z < CHUNK_SIZE_Z; ++z) {
        for (int y = 0; y < CHUNK_SIZE_Y; ++y) {
            for (int x = 0; x < CHUNK_SIZE_X; ++x) {
                vox_data_t data;
                data.position = glm::ivec3(x, y, z) + offset;
                data.colour = glm::ivec3(x, (int)(y / 4.0f), z);
                data.type = voxel_type_t::NORMAL;
                data.solid = true;
                data.transparency = false;
                data.rel = rel_loc_t::WORLD_LOC;
                chunk.Create_Voxel(data);
            }
        }
    }
}




#endif // !CREATE_GENERIC_CHUNKS
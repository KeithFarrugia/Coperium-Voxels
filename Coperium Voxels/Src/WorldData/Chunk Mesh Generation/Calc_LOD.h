#pragma once
#ifndef CALCULATE_LOD_H
#define CALCULATE_LOD_H

#include <GLM/gtx/norm.hpp>
#include "../World.h"

inline constexpr float THRESH_SQ0 = 50.0f * 50.0f;
inline constexpr float THRESH_SQ1 = 100.0f * 100.0f;
inline constexpr float THRESH_SQ2 = 300.0f * 300.0f;
inline constexpr float THRESH_SQ3 = 800.0f * 800.0f;



//inline constexpr float THRESH_SQ0 = 500.0f * 500.0f;
//inline constexpr float THRESH_SQ1 = 1000.0f * 1000.0f;
//inline constexpr float THRESH_SQ2 = 3000.0f * 3000.0f;
//inline constexpr float THRESH_SQ3 = 8000.0f * 8000.0f;

inline constexpr glm::vec3 HALF_CHUNK(
    CHUNK_SIZE_X * 0.5f, 
    CHUNK_SIZE_Y * 0.5f, 
    CHUNK_SIZE_Z * 0.5f
);

/* ============================================================================
 * --------------------------- Compute_LOD
 * Computes the appropriate level of detail (LOD) for a chunk based on the squared
 * distance from the camera to the chunk's center.
 *
 * ------ Parameters ------
 * camera_pos:  The position of the camera.
 * chunk_center: The center position of the chunk.
 *
 * ------ Returns ------
 * The appropriate lod_Level_t based on the thresholds.
 * ============================================================================
 */
inline lod_Level_t Compute_LOD(
    const sector_loc_t  sector_id   ,
    const chunk_loc_t   chunk_id    ,
    const glm::vec3&    camera_pos  
){
    glm::vec3 chunk_origin(
        sector_id.X() * SECTR_SIZE_X + chunk_id.X() * CHUNK_SIZE_X,
                                       chunk_id.Y() * CHUNK_SIZE_Y,
        sector_id.Z() * SECTR_SIZE_Z + chunk_id.Z() * CHUNK_SIZE_Z
    );


    float distSq = glm::distance2(camera_pos, chunk_origin + HALF_CHUNK);
    if (distSq < THRESH_SQ0) {
        return lod_Level_t::NORMAL;
    }
    else if (distSq < THRESH_SQ1) {
        return lod_Level_t::LOD_2;
    }
    else if (distSq < THRESH_SQ2) {
        return lod_Level_t::LOD_4;
    }
    else if (distSq < THRESH_SQ3) {
        return lod_Level_t::LOD_8;
    }
    else {
        return lod_Level_t::LOD_16;
    }
}


#endif // !CALCULATE_LOD_H
#pragma once
#ifndef CALCULATE_LOD_H
#define CALCULATE_LOD_H

#include <GLM/gtx/norm.hpp>
#include "../../World.h"

typedef struct lod_dst_set_t {
    enum class lod_Level_t : int {
        NORMAL = 0,
        LOD_2, LOD_4,
        LOD_8, LOD_16,
        COUNT // helper to determine array size
    };
    float thresholds[static_cast<int>(lod_Level_t::COUNT)];
    
    lod_dst_set_t() {
        thresholds[static_cast<int>(lod_Level_t::NORMAL )]  = 50.0f     * 50.0f;
        thresholds[static_cast<int>(lod_Level_t::LOD_2  )]  = 100.0f    * 100.0f;
        thresholds[static_cast<int>(lod_Level_t::LOD_4  )]  = 3000.0f   * 3000.0f;
        thresholds[static_cast<int>(lod_Level_t::LOD_8  )]  = 8000.0f   * 8000.0f;
        thresholds[static_cast<int>(lod_Level_t::LOD_16 )]  = std::numeric_limits<float>::max();
    }

    lod_dst_set_t(
        float normal_sq ,
        float lod2_sq   ,
        float lod4_sq   ,
        float lod8_sq   ,
        float lod16_sq = std::numeric_limits<float>::max()
    ) {
        thresholds[static_cast<int>(lod_Level_t::NORMAL)]   = normal_sq;
        thresholds[static_cast<int>(lod_Level_t::LOD_2)]    = lod2_sq;
        thresholds[static_cast<int>(lod_Level_t::LOD_4)]    = lod4_sq;
        thresholds[static_cast<int>(lod_Level_t::LOD_8)]    = lod8_sq;
        thresholds[static_cast<int>(lod_Level_t::LOD_16)]   = lod16_sq;
    }

    float Get_LOD_Threshold(lod_Level_t level) const {
        return thresholds[static_cast<int>(level)];
    }

    void Set_LOD_Threshold(lod_Level_t level, float distance_squared) {
        thresholds[static_cast<int>(level)] = distance_squared;
    }
}lod_dst_set_t;

/*inline constexpr float THRESH_SQ0 = 50.0f * 50.0f;
inline constexpr float THRESH_SQ1 = 100.0f * 100.0f;
inline constexpr float THRESH_SQ2 = 300.0f * 300.0f;
inline constexpr float THRESH_SQ3 = 800.0f * 800.0f*/;



inline constexpr float THRESH_SQ0 = 1000.0f * 1000.0f;
inline constexpr float THRESH_SQ1 = 1000.0f * 1000.0f;
inline constexpr float THRESH_SQ2 = 3000.0f * 3000.0f;
inline constexpr float THRESH_SQ3 = 8000.0f * 8000.0f;


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
    const sector_loc_t          &   sector_id   ,
    const chunk_loc_t           &   chunk_id    ,
    const glm::vec3             &   camera_pos  ,
    const lod_dst_set_t &   lod_settings
) {
    glm::vec3 chunk_origin{
        sector_id.X() * SECTR_SIZE_X + chunk_id.X() * CHUNK_SIZE_X,
                                       chunk_id.Y() * CHUNK_SIZE_Y,
        sector_id.Z() * SECTR_SIZE_Z + chunk_id.Z() * CHUNK_SIZE_Z
    };

    const float  dst        = glm::distance2(camera_pos, chunk_origin + HALF_CHUNK);
    const float* thresholds = lod_settings.thresholds;

    if (dst < thresholds[static_cast<int>(lod_Level_t::NORMAL)]) return lod_Level_t::NORMAL ;
    if (dst < thresholds[static_cast<int>(lod_Level_t::LOD_2 )]) return lod_Level_t::LOD_2  ;
    if (dst < thresholds[static_cast<int>(lod_Level_t::LOD_4 )]) return lod_Level_t::LOD_4  ;
    if (dst < thresholds[static_cast<int>(lod_Level_t::LOD_8 )]) return lod_Level_t::LOD_8  ;

    return lod_Level_t::LOD_16; // fallback
}


#endif // !CALCULATE_LOD_H
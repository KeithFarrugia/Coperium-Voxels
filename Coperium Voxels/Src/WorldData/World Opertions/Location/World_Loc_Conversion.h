#pragma once
#ifndef WORLD_LOCATION_CONVERSION_H
#define WORLD_LOCATION_CONVERSION_H


#include <glm/glm.hpp>
#include "../Safe_Operations.h"
#include "../World_Constants.h"


typedef enum rel_loc_t {
    WORLD_LOC,
    SECTOR_LOC,
    CHUNK_LOC,
    VOXEL_LOC,
}rel_loc_t;


/* ============================================================================
 * --------------------------- Convert_Loc_2_ID
 * Converts a location from one relative coordinate system to another.
 *
 * ------ Parameters ------
 * value: The position (ivec3) to convert.
 * from:  The current relative location type (rel_loc_t).
 * to:    The target relative location type (rel_loc_t).
 *
 * ------ Returns ------
 * Converted position in the target coordinate system.
 * ============================================================================
 */
inline static glm::ivec3 Convert_Loc_2_ID(
    glm::ivec3 value, rel_loc_t from, rel_loc_t to
){
    switch (from) {
    case rel_loc_t::WORLD_LOC:
        switch (to) {
        case rel_loc_t::SECTOR_LOC:
            return glm::ivec3(
                Safe_Div(value.x, SECTR_SIZE_X),
                value.y,
                Safe_Div(value.z, SECTR_SIZE_Z)
            );

        case rel_loc_t::CHUNK_LOC:
            return glm::ivec3(
                Safe_Div(Pos_Mod(value.x, SECTR_SIZE_X), CHUNK_SIZE_X),
                Safe_Div(        value.y,                CHUNK_SIZE_Y),
                Safe_Div(Pos_Mod(value.z, SECTR_SIZE_Z), CHUNK_SIZE_Z)
            );

        default:
            return value;
        }
    case rel_loc_t::SECTOR_LOC:
        switch (to) {
        case rel_loc_t::CHUNK_LOC:
            return glm::ivec3(
                Safe_Div(value.x, CHUNK_SIZE_X),
                Safe_Div(value.y, CHUNK_SIZE_Y),
                Safe_Div(value.z, CHUNK_SIZE_Z)
            );

        default:
            return value;
        }
    default:
        return value;
    }
    return glm::ivec3();
}

/* ============================================================================
 * --------------------------- Convert_Loc_2_Offset
 * Converts a world-relative location to an offset within its local region.
 *
 * ------ Parameters ------
 * value: The position (ivec3) to convert.
 * from:  The current relative location type (rel_loc_t).
 * to:    The target relative location type (rel_loc_t).
 *
 * ------ Returns ------
 * The offset position relative to the local coordinate system.
 * ============================================================================
 */
inline static glm::ivec3 Convert_Loc_2_Offset(
    glm::ivec3 value, rel_loc_t from, rel_loc_t to
) {
    switch (from) {
    case rel_loc_t::WORLD_LOC:
        switch (to) {
        case rel_loc_t::SECTOR_LOC:
            return glm::ivec3(
                Pos_Mod(value.x, SECTR_SIZE_X),
                value.y,
                Pos_Mod(value.z, SECTR_SIZE_Z)
            );

        case rel_loc_t::CHUNK_LOC:
            return glm::ivec3(
                Pos_Mod(Pos_Mod(value.x, SECTR_SIZE_X), CHUNK_SIZE_X),
                Pos_Mod(        value.y,                CHUNK_SIZE_Y),
                Pos_Mod(Pos_Mod(value.z, SECTR_SIZE_Z), CHUNK_SIZE_Z)
            );

        default:
            return value;
        }
    case rel_loc_t::SECTOR_LOC:
        switch (to) {
        case rel_loc_t::CHUNK_LOC:
            return glm::ivec3(
                Pos_Mod(value.x, CHUNK_SIZE_X),
                Pos_Mod(value.y, CHUNK_SIZE_Y),
                Pos_Mod(value.z, CHUNK_SIZE_Z)
            );

        default:
            return value;
        }
    default:
        return value;
    }
    return glm::ivec3();
}

#endif // !WORLD_LOCATION_CONVERSION_H
#pragma once
#ifndef COMMON_WORLD_DATA
#define COMMON_WORLD_DATA

#include <COIL/DataStructures/IndexedAvlTree/IndexedAvlTree.h>
#include <GLM/glm.hpp>
#include "Operations.h"
#include <vector>

/* ---------------------------------
 * NUMBER OF VOXELS IN A SECTOR     */
constexpr int SECTR_SIZE_X =    512;    // 16 * 32
constexpr int SECTR_SIZE_Z =    512;    // 16 * 32

/* ---------------------------------
 * NUMBER OF VOXELS IN A SECTOR     */
constexpr int CHUNK_SIZE_X =    16;
constexpr int CHUNK_SIZE_Y =    64;
constexpr int CHUNK_SIZE_Z =    16;

constexpr int MAX_VOX_LOC  =    CHUNK_SIZE_X * 
                                CHUNK_SIZE_Y * 
                                CHUNK_SIZE_Z ;




typedef enum {
    AIR,
    NORMAL
}voxel_type_t;

typedef enum {
    WORLD_LOC,
    SECTOR_LOC,
    CHUNK_LOC,
    VOXEL_LOC,
}rel_loc_t;

typedef struct vox_data_t {
    glm::ivec3  position;
    glm::ivec3  colour;
    int         type;
    bool        solid;
    bool        transparency;
    rel_loc_t   rel = rel_loc_t::WORLD_LOC;
}vox_data_t;


class World;
class Sector;
class Chunk;
class Voxel;


typedef struct sector_loc_t{
    uint32_t location;

    void Set(const glm::ivec2 vec) {
        int32_t x_sign  = (vec.x >> 31) & 0x1;
        int32_t z_sign  = (vec.y >> 31) & 0x1;
        int32_t abs_x   = (vec.x ^ (-x_sign)) + x_sign;
        int32_t abs_z   = (vec.y ^ (-z_sign)) + z_sign;

        location =  (x_sign << 31) | (abs_x << 16) |
                    (z_sign << 0 ) | (abs_z << 15);
    }
    int X() const {
        int32_t x       = (location >> 16) & 0x7FFF;
        int32_t sign    = (location >> 31) & 0x1;
        return (x ^ (-sign)) + sign;
    }
    int Z() const {
        int32_t z       = (location >> 0) & 0x7FFF;
        int32_t sign    = (location >> 15) & 0x1;
        return (z ^ (-sign)) + sign;
    }
    static sector_loc_t Compact(const glm::ivec2 vec) {
        sector_loc_t result;

        int32_t x_sign  = (vec.x >> 31) & 0x1;
        int32_t z_sign  = (vec.y >> 31) & 0x1;
        int32_t abs_x   = (vec.x ^ (-x_sign)) + x_sign;
        int32_t abs_z   = (vec.y ^ (-z_sign)) + z_sign;

        result.location = (x_sign << 31) | (abs_x << 16) |
                          (z_sign << 0 ) | (abs_z << 15);

        return result;
    }
    static sector_loc_t Compact(const glm::ivec3 vec) {
        sector_loc_t result;

        int32_t x_sign  = (vec.x >> 31) & 0x1;
        int32_t z_sign  = (vec.z >> 31) & 0x1;
        int32_t abs_x   = (vec.x ^ (-x_sign)) + x_sign;
        int32_t abs_z   = (vec.z ^ (-z_sign)) + z_sign;

        result.location = (x_sign << 31) | (abs_x << 16) |
                          (z_sign << 0 ) | (abs_z << 15);

        return result;
    }

    bool operator<(const sector_loc_t& other) const {
        return location < other.location;
    }
    bool operator>(const sector_loc_t& other) const {
        return location > other.location;
    }
    bool operator==(const sector_loc_t& other) const {
        return location == other.location;
    }
    bool operator!=(const sector_loc_t& other) const {
        return location != other.location;
    }
}sector_loc_t;




typedef struct chunk_loc_t{
    uint16_t location;

    void Set(const glm::ivec3 vec) {
        int y_sign = vec.y >> 31;
        int y_abs = (vec.y ^ y_sign) - y_sign;

        location =
            ((vec.x     & 0x1F) << 11) |
            ((vec.z     & 0x1F) << 0 ) |
            ((y_sign    & 0x1 ) << 10) |
            ((y_abs     & 0x1F) << 5 );
    }
    int X() const {
        return (location >> 11) & 0x1F;
    }
    int Y() const {
        int y_value = (location >> 5 ) & 0x1F;
        int y_sign  = (location >> 10) & 0x1;
        return (y_value ^ -y_sign) + y_sign;
    }
    int Z() const {
        return (location >> 0) & 0x1F;
    }
    static chunk_loc_t Compact(const glm::ivec3 vec) {
        chunk_loc_t result;

        int y_sign = vec.y >> 31;
        int y_abs = (vec.y ^ y_sign) - y_sign;

        result.location =
            ((vec.x     & 0x1F) << 11) |
            ((vec.z     & 0x1F) << 0 ) |
            ((y_sign    & 0x1 ) << 10) |
            ((y_abs     & 0x1F) << 5 );

        return result;
    }

    bool operator<(const chunk_loc_t& other) const {
        return location < other.location;
    }
    bool operator>(const chunk_loc_t& other) const {
        return location > other.location;
    }
    bool operator==(const chunk_loc_t& other) const {
        return location == other.location;
    }
    bool operator!=(const chunk_loc_t& other) const {
        return location != other.location;
    }
}chunk_loc_t;


typedef struct voxel_loc_t {
    uint32_t location;

    void Set(const glm::ivec3 vec) {
        location = 0;
        location =
            (vec.x << 10) |
            (vec.y << 4 ) |
            (vec.z << 0 ); 
    }
    int X() const {
        return (location >> 10) & 0xF;
    }
    int Y() const {
        return (location >> 4) & 0x3F;
    }
    int Z() const {
        return (location >> 0) & 0xF;
    }
    static voxel_loc_t Compact(const glm::ivec3 vec) {
        voxel_loc_t result;

        int y_sign = vec.y >> 31;
        int y_abs = (vec.y ^ y_sign) - y_sign;

        result.location =
            (vec.x << 10) |
            (vec.y << 4 ) |
            (vec.z << 0 );

        return result;
    }

    bool operator<(const voxel_loc_t& other) const {
        return location < other.location;
    }
    bool operator>(const voxel_loc_t& other) const {
        return location > other.location;
    }
    bool operator==(const voxel_loc_t& other) const {
        return location == other.location;
    }
    bool operator!=(const voxel_loc_t& other) const {
        return location != other.location;
    }

}voxel_loc_t;


typedef Coil::IndexedAvlTree<sector_loc_t, Sector>  sectors_t;
typedef Coil::IndexedAvlTree<chunk_loc_t,  Chunk>   chunks_t;
typedef std::vector<Voxel>                          voxels_t;





inline static glm::ivec3 Convert_Loc_2_ID(glm::ivec3 value, rel_loc_t from, rel_loc_t to) {
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
                Safe_Div(value.y, CHUNK_SIZE_Y),
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

inline static glm::ivec3 Convert_Loc_2_Offset(glm::ivec3 value, rel_loc_t from, rel_loc_t to) {
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
                Pos_Mod(value.y, CHUNK_SIZE_Y),
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






#endif // !COMMON_WORLD_DATA

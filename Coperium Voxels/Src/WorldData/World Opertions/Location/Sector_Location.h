#pragma once
#ifndef SECTOR_LOCATION_STUCT_H
#define SECTOR_LOCATION_STUCT_H
#include <cstdint>
#include <glm/glm.hpp>

struct sector_loc_t {

    uint32_t location;

    /* ============================================================================
     * --------------------------- Set
     * Sets the location value based on a 2D integer vector
     *
     * ------ Parameters ------
     * vec:    The 2D integer vector representing the sector position
     * ============================================================================
     */
    inline void Set(const glm::ivec2 vec) {
        int32_t x_sign = (vec.x >> 31) & 0x1;
        int32_t z_sign = (vec.y >> 31) & 0x1;
        int32_t abs_x = (vec.x ^ (-x_sign)) + x_sign;
        int32_t abs_z = (vec.y ^ (-z_sign)) + z_sign;

        location = (x_sign << 31) | (abs_x << 16) |
            (z_sign << 0) | (abs_z << 15);
    }

    /* ============================================================================
     * --------------------------- X
     * Retrieves the X coordinate from the encoded location
     *
     * ------ Returns ------
     * The X coordinate as an integer
     * ============================================================================
     */
    inline int X() const {
        int32_t x = (location >> 16) & 0x7FFF;
        int32_t sign = (location >> 31) & 0x1;
        return (x ^ (-sign)) + sign;
    }

    /* ============================================================================
     * --------------------------- Z
     * Retrieves the Z coordinate from the encoded location
     *
     * ------ Returns ------
     * The Z coordinate as an integer
     * ============================================================================
     */
    inline int Z() const {
        int32_t z = (location >> 0) & 0x7FFF;
        int32_t sign = (location >> 15) & 0x1;
        return (z ^ (-sign)) + sign;
    }

    /* ============================================================================
     * --------------------------- Compact (ivec2)
     * Compresses a 2D position into a compact sector location
     *
     * ------ Parameters ------
     * vec:    The 2D integer vector to compress
     *
     * ------ Returns ------
     * A compacted sector location structure
     * ============================================================================
     */
    static inline sector_loc_t Compact(const glm::ivec2 vec) {
        sector_loc_t result;
        result.Set(vec);
        return result;
    }

    /* ============================================================================
     * --------------------------- Compact (ivec3)
     * Compresses a 3D position into a compact sector location using only X and Z
     *
     * ------ Parameters ------
     * vec:    The 3D integer vector to compress
     *
     * ------ Returns ------
     * A compacted sector location structure
     * ============================================================================
     */
    static inline sector_loc_t Compact(const glm::ivec3 vec) {
        return Compact(glm::ivec2(vec.x, vec.z));
    }

    /* ============================================================================
     * --------------------------- Operator Overloads
     * Comparison and equality operators for sector_loc_t
     * ============================================================================
     */
    inline bool operator<(const sector_loc_t& other) const {
        return location < other.location;
    }

    inline bool operator>(const sector_loc_t& other) const {
        return location > other.location;
    }

    inline bool operator==(const sector_loc_t& other) const {
        return location == other.location;
    }

    inline bool operator!=(const sector_loc_t& other) const {
        return location != other.location;
    }
};

/* ============================================================================
 * --------------------------- std::hash Specialization for sector_loc_t
 * Specializes std::hash so that sector_loc_t can be used as a key in std::unordered_map.
 * ============================================================================ 
 */
namespace std {
    template <>
    struct hash<sector_loc_t> {
        std::size_t operator()(const sector_loc_t& key) const noexcept {
            return std::hash<uint32_t>()(key.location);
        }
    };
}

#endif // !SECTOR_LOCATION_STUCT_H
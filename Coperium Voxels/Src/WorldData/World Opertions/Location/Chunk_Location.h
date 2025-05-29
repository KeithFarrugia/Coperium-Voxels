#pragma once
#ifndef CHUNK_LOCATION_STUCT_H
#define CHUNK_LOCATION_STUCT_H

#include <cstdint>
#include <glm/glm.hpp>

struct chunk_loc_t {
    uint16_t location;

    /* ============================================================================
     * --------------------------- Set
     * Encodes a 3D position into the chunk location format
     *
     * ------ Parameters ------
     * vec:    The 3D integer vector representing the chunk position
     * ============================================================================
     */
    inline void Set(const glm::ivec3 vec) {
        int y_sign = vec.y >> 31;
        int y_abs = (vec.y ^ y_sign) - y_sign;

        location =
            ((vec.x & 0x1F) << 11) |
            ((vec.z & 0x1F) << 0) |
            ((y_sign & 0x1) << 10) |
            ((y_abs & 0x1F) << 5);
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
        return (location >> 11) & 0x1F;
    }

    /* ============================================================================
     * --------------------------- Y
     * Retrieves the Y coordinate from the encoded location
     *
     * ------ Returns ------
     * The Y coordinate as an integer
     * ============================================================================
     */
    inline int Y() const {
        int y_value = (location >> 5) & 0x1F;
        int y_sign = (location >> 10) & 0x1;
        return (y_value ^ -y_sign) + y_sign;
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
        return (location >> 0) & 0x1F;
    }

    /* ============================================================================
     * --------------------------- Compact
     * Compresses a 3D position into a compact chunk location
     *
     * ------ Parameters ------
     * vec:    The 3D integer vector to compress
     *
     * ------ Returns ------
     * A compacted chunk location structure
     * ============================================================================
     */
    static inline chunk_loc_t Compact(const glm::ivec3 vec) {
        chunk_loc_t result;
        result.Set(vec);
        return result;
    }

    /* ============================================================================
     * --------------------------- Operator Overloads
     * Comparison and equality operators for chunk_loc_t
     * ============================================================================
     */
    inline bool operator<(const chunk_loc_t& other) const {
        return location < other.location;
    }

    inline bool operator>(const chunk_loc_t& other) const {
        return location > other.location;
    }

    inline bool operator==(const chunk_loc_t& other) const {
        return location == other.location;
    }

    inline bool operator!=(const chunk_loc_t& other) const {
        return location != other.location;
    }

};
namespace std {
    template <>
    struct hash<chunk_loc_t> {
        size_t operator()(const chunk_loc_t& loc) const noexcept {
            return std::hash<uint16_t>{}(loc.location);
        }
    };
}
#endif // !CHUNK_LOCATION_STUCT_H
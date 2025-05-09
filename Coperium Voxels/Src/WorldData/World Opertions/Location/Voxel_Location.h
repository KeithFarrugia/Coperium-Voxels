#pragma once
#ifndef VOXEL_LOCATION_STUCT_H
#define VOXEL_LOCATION_STUCT_H

#include <cstdint>
#include <glm/glm.hpp>
struct voxel_loc_t {

    uint16_t  location;
    /* ============================================================================
     * --------------------------- Set
     * Encodes a 3D voxel position into a compact location format
     *
     * ------ Parameters ------
     * vec:    The 3D integer vector representing the voxel position
     * ============================================================================
     */
    inline void Set(const glm::ivec3 vec) {
        location =
            (vec.x << 10) |
            (vec.y << 4) |
            (vec.z << 0);
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
        return (location >> 10) & 0xF;
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
        return (location >> 4) & 0x3F;
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
        return (location >> 0) & 0xF;
    }

    /* ============================================================================
     * --------------------------- Compact
     * Compresses a 3D position into a compact voxel location
     *
     * ------ Parameters ------
     * vec:    The 3D integer vector to compress
     *
     * ------ Returns ------
     * A compacted voxel location structure
     * ============================================================================
     */
    static inline voxel_loc_t Compact(const glm::ivec3 vec) {
        voxel_loc_t result;
        result.Set(vec);
        return result;
    }

    /* ============================================================================
     * --------------------------- Operator Overloads
     * Comparison and equality operators for voxel_loc_t
     * ============================================================================
     */
    inline bool operator<(const voxel_loc_t& other) const {
        return location < other.location;
    }

    inline bool operator>(const voxel_loc_t& other) const {
        return location > other.location;
    }

    inline bool operator==(const voxel_loc_t& other) const {
        return location == other.location;
    }

    inline bool operator!=(const voxel_loc_t& other) const {
        return location != other.location;
    }
};
#endif // !VOXEL_LOCATION_STUCT_H
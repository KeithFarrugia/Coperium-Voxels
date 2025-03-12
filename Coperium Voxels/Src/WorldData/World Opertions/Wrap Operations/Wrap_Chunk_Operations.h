#pragma once
#ifndef WRAPAROUND_CHUNK_HELPERS_H
#define WRAPAROUND_CHUNK_HELPERS_H

#include "../World_Constants.h"


/* ============================================================================
 * --------------------------- wrap_chunk_x
 * Wraps a chunk x-coordinate by adding a delta (positive or negative) and
 * wrapping around using branchless bitwise operations.
 *
 * ------ Parameters ------
 * x:     The current chunk x-coordinate.
 * delta: The value to add (can be positive or negative).
 *
 * ------ Returns ------
 * The new chunk x-coordinate after wrapping.
 * ============================================================================
 */
constexpr inline int wrap_chunk_x(int x, int delta) {
    return MIN_ID_C_X + (((x - MIN_ID_C_X) + delta) & MASK_CHUNKS_X);
}

/* ============================================================================
 * --------------------------- wrap_chunk_z
 * Wraps a chunk z-coordinate by adding a delta (positive or negative) and
 * wrapping around using branchless bitwise operations.
 *
 * ------ Parameters ------
 * z:     The current chunk z-coordinate.
 * delta: The value to add (can be positive or negative).
 *
 * ------ Returns ------
 * The new chunk z-coordinate after wrapping.
 * ============================================================================
 */
constexpr inline int wrap_chunk_z(int z, int delta) {
    return MIN_ID_C_Z + (((z - MIN_ID_C_Z) + delta) & MASK_CHUNKS_Z);
}

/* ============================================================================
 * --------------------------- wrap_chunk_y
 * Wraps a chunk y-coordinate by adding a delta (positive or negative) and
 * wrapping around using branchless modulo arithmetic.
 *
 * Note: The chunk y range (from MIN_ID_C_Y to MAX_ID_C_Y) has 63 values which is not
 * a power-of-two, so a modulo operation is required. This function uses an arithmetic
 * right-shift to adjust for negative remainders without conditional branches.
 *
 * ------ Parameters ------
 * y:     The current chunk y-coordinate.
 * delta: The value to add (can be positive or negative).
 *
 * ------ Returns ------
 * The new chunk y-coordinate after wrapping.
 * ============================================================================
 */
inline int wrap_chunk_y(int y, int delta) {
    const int count = NUM_CHUNKS_Y; // 63
    int offset = (y - MIN_ID_C_Y) + delta; // This may be negative.
    int mod = offset % count;              // Standard modulo (may yield a negative result).
    // Branchless fix: (mod >> 31) yields all 1's (i.e. -1) if mod is negative.
    int add = (mod >> 31) & count;         // If mod is negative, add 'count'; otherwise, add 0.
    mod += add;
    return MIN_ID_C_Y + mod;
}

#endif // WRAPAROUND_CHUNK_HELPERS_H

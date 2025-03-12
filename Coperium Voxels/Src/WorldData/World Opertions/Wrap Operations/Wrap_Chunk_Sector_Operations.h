#pragma once
#pragma once
#ifndef CHUNK_SECTOR_ADJUSTMENT_H
#define CHUNK_SECTOR_ADJUSTMENT_H

#include "../World_Constants.h"

/* ============================================================================
 * --------------------------- wrap_chunk_sec_x
 * Computes new values for the chunk x-coordinate and sector x-coordinate 
 * given an initial sector x and chunk x along with a delta. If the resulting 
 * chunk x-coordinate exceeds the valid range [0, 31], it wraps around and 
 * the sector x-coordinate is adjusted.
 *
 * ------ Parameters ------
 * sector_x:        The current sector x-coordinate.
 * chunk_x:         The current chunk x-coordinate.
 * delta:           The value to add to the chunk x-coordinate.
 * new_sector_x:    (Output) The new sector x-coordinate after adjustment.
 * new_chunk_x:     (Output) The new chunk x-coordinate after wrapping.
 *
 * ------ Operation ------
 * Computes sum = chunk_x + delta. The quotient (carry) is computed using a 
 * right shift (division by 32) and the new chunk x-coordinate is obtained 
 * using a bitwise AND with MASK_CHUNKS. The new sector x-coordinate is then 
 * calculated by adding the carry to the original sector x-coordinate.
 * ============================================================================
 */
constexpr inline void wrap_chunk_sec_x(
    int     sector_x    , int   chunk_x     , int delta, 
    int&    new_sector_x, int&  new_chunk_x 
){
    int sum      = chunk_x  +   delta       ;
    int carry    = sum      >>  5           ;
    new_chunk_x  = sum      &   MASK_CHUNKS ;
    new_sector_x = sector_x +   carry       ;
}

/* ============================================================================
 * --------------------------- wrap_chunk_sec_z
 * Computes new values for the chunk z-coordinate and sector z-coordinate 
 * given an initial sector z and chunk z along with a delta. If the resulting
 * chunk z-coordinate exceeds the valid range [0, 31], it wraps around and the 
 * sector z-coordinate is adjusted.
 *
 * ------ Parameters ------
 * sector_z:        The current sector z-coordinate.
 * chunk_z:         The current chunk z-coordinate.
 * delta:           The value to add to the chunk z-coordinate.
 * new_sector_z:    (Output) The new sector z-coordinate after adjustment.
 * new_chunk_z:     (Output) The new chunk z-coordinate after wrapping.
 *
 * ------ Operation ------
 * Computes sum = chunk_z + delta. The quotient (carry) is computed using
 * a right shift, and the new chunk z-coordinate is obtained using a bitwise
 * AND with MASK_CHUNKS. The new sector z-coordinate is calculated by adding 
 * the carry to the original sector z-coordinate.
 * ============================================================================
 */
constexpr inline void wrap_chunk_sec_z(
    int     sector_z    , int   chunk_z     , int delta, 
    int&    new_sector_z, int&  new_chunk_z
){
    int sum         = chunk_z   + delta         ;
    int carry       = sum       >> 5            ;
    new_chunk_z     = sum       & MASK_CHUNKS   ;
    new_sector_z    = sector_z  + carry         ;
}

/* ============================================================================
 * --------------------------- wrap_chunk_sec_y
 * Computes a new chunk y-coordinate given an initial chunk y-coordinate and
 * a delta, wrapping around the valid range [MIN_ID_C_Y, MAX_ID_C_Y] without 
 * adjusting any sector coordinate.
 *
 * ------ Parameters ------
 * chunk_y: The current chunk y-coordinate.
 * delta:  The value to add to the chunk y-coordinate.
 *
 * ------ Returns ------
 * The new chunk y-coordinate after wrapping.
 *
 * ------ Operation ------
 * Normalizes the y-coordinate by subtracting MIN_ID_C_Y, adds the
 * delta, and computes the remainder modulo NUM_CHUNKS_Y. A branchless
 * adjustment corrects for a negative remainder, and MIN_ID_C_Y is then added 
 * back to yield the new y-coordinate.
 * ============================================================================
 */
constexpr inline void wrap_chunk_sec_y(
    int     sector_y    , int   chunk_y     , int delta,
    int&    new_sector_y, int&  new_chunk_y
){
    const int   count   =  NUM_CHUNKS_Y                      ;
    int         offset  = (chunk_y      - MIN_ID_C_Y) + delta;
    int         mod     =  offset       % count              ;
    int         add     = (mod          >> 31       ) & count;
                mod    +=  add                               ;

    new_chunk_y         =  MIN_ID_C_Y + mod;
    new_sector_y        = sector_y;
}

#endif // CHUNK_SECTOR_ADJUSTMENT_H

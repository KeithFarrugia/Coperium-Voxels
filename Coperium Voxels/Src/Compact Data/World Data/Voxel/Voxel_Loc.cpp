#include "Voxel_Loc.h"

/* ============================================================================
 * --------------------------- Voxel_Loc
 * Default constructor initializing data to default X, Y, Z (0, 0, 0).
 * ============================================================================
 */
Voxel_Loc::Voxel_Loc() : data(0) {}

/* ============================================================================
 * --------------------------- Voxel_Loc
 * Constructor initializing data to a given value.
 * ============================================================================
 */
Voxel_Loc::Voxel_Loc(const uint16_t data) : data(data) {}

/* ============================================================================
 * --------------------------- Set_X
 * Sets the X component using an integer.
 *
 * ------ Parameters ------
 * x: The integer value to set for X (0-15).
 * ============================================================================
 */
void Voxel_Loc::Set_X(const int x) {
    data &= ~(X_MASK);  // Clear X bits
    data |= (x & 0xF) << X_SHIFT;  // Set new X bits
}

/* ============================================================================
 * --------------------------- Set_Y
 * Sets the Y component using an integer.
 *
 * ------ Parameters ------
 * y: The integer value to set for Y (0-63).
 * ============================================================================
 */
void Voxel_Loc::Set_Y(const int y) {
    data &= ~(Y_MASK);  // Clear Y bits
    data |= (y & 0x3F) << Y_SHIFT;  // Set new Y bits
}

/* ============================================================================
 * --------------------------- Set_Z
 * Sets the Z component using an integer.
 *
 * ------ Parameters ------
 * z: The integer value to set for Z (0-15).
 * ============================================================================
 */
void Voxel_Loc::Set_Z(const int z) {
    data &= ~(Z_MASK);  // Clear Z bits
    data |= (z & 0xF) << Z_SHIFT;  // Set new Z bits
}

/* ============================================================================
 * --------------------------- Get_X
 * Gets the X component as an integer.
 *
 * Returns the integer value of X (0-15).
 * ============================================================================
 */
int Voxel_Loc::Get_X() const {
    return (data >> X_SHIFT) & 0xF;
}

/* ============================================================================
 * --------------------------- Get_Y
 * Gets the Y component as an integer.
 *
 * Returns the integer value of Y (0-63).
 * ============================================================================
 */
int Voxel_Loc::Get_Y() const {
    return (data >> Y_SHIFT) & 0x3F;
}

/* ============================================================================
 * --------------------------- Get_Z
 * Gets the Z component as an integer.
 *
 * Returns the integer value of Z (0-15).
 * ============================================================================
 */
int Voxel_Loc::Get_Z() const {
    return (data >> Z_SHIFT) & 0xF;
}

/* ============================================================================
 * --------------------------- Compact
 * Compacts X, Y, and Z into a single 16-bit unsigned integer.
 *
 * ------ Parameters ------
 * x: The X component as an integer (0-15).
 * y: The Y component as an integer (0-63).
 * z: The Z component as an integer (0-15).
 *
 * Returns a compacted 16-bit value encoding X, Y, and Z.
 * ============================================================================
 */
uint16_t Voxel_Loc::Compact(const int x, const int y, const int z){
    return (x << X_SHIFT) | (y << Y_SHIFT) | (z << Z_SHIFT);
}

/* ============================================================================
 * --------------------------- From_Compact
 * Decompacts a 16-bit unsigned integer into X, Y, and Z components.
 *
 * ------ Parameters ------
 * data: The 16-bit packed data to decompact.
 * ============================================================================
 */
void Voxel_Loc::From_Compact(const uint16_t packed_data) {
    data = packed_data;
}


/* ============================================================================
 * --------------------------- ==
 * Comparison Operator.
 * ============================================================================
 */
bool Voxel_Loc::operator==(const Voxel_Loc& other) const {
    return data == other.data;
}
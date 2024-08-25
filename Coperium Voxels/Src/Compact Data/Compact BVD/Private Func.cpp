#include "Block Vertex Data.h"

/* ============================================================================
 * --------------------------- getBits
 * Retrieves the underlying 32-bit representation of the stored GLfloat value.
 *
 * ------ Returns ------
 * uint32_t: The 32-bit integer representation of the stored GLfloat value.
 * ============================================================================
 */
uint32_t Block_VD::Get_Bits() const {
    uint32_t bits;
    std::memcpy(&bits, &value, sizeof(GLfloat));
    return bits;
}

// Helper to set the bits
/* ============================================================================
 * --------------------------- setBits
 * Sets the underlying 32-bit representation of the stored GLfloat value.
 *
 * ------ Parameters ------
 * bits: The 32-bit integer representation to set the stored GLfloat value.
 * ============================================================================
 */
void Block_VD::Set_Bits(const uint32_t bits) {
    std::memcpy(&value, &bits, sizeof(GLfloat));
}

/* ============================================================================
 * --------------------------- X_Sign
 * Retrieves the sign bit of the X component.
 *
 * ------ Returns ------
 * int: 1 if the sign bit is set (negative), 0 if not (positive).
 * ============================================================================
 */
int Block_VD::X_Sign() const {
    return (Get_Bits() >> 31) & 0x1;
}

/* ============================================================================
 * --------------------------- X_Mantissa
 * Retrieves the 4-bit mantissa of the X component.
 *
 * ------ Returns ------
 * uint8_t: The 4-bit mantissa value of the X component.
 * ============================================================================
 */
uint8_t Block_VD::X_Mantissa() const {
    return (Get_Bits() >> 26) & 0xF;
}

/* ============================================================================
 * --------------------------- X_Fraction
 * Retrieves the 5-bit fraction of the X component.
 *
 * ------ Returns ------
 * uint8_t: The 5-bit fraction value of the X component.
 * ============================================================================
 */
uint8_t Block_VD::X_Fraction() const {
    return (Get_Bits() >> 21) & 0x1F;
}






/* ============================================================================
 * --------------------------- Y_Sign
 * Retrieves the sign bit of the Y component.
 *
 * ------ Returns ------
 * int: 1 if the sign bit is set (negative), 0 if not (positive).
 * ============================================================================
 */
int Block_VD::Y_Sign() const {
    return (Get_Bits() >> 21) & 0x1;
}

/* ============================================================================
 * --------------------------- Y_Mantissa
 * Retrieves the 6-bit mantissa of the Y component.
 *
 * ------ Returns ------
 * uint8_t: The 6-bit mantissa value of the Y component.
 * ============================================================================
 */
uint8_t Block_VD::Y_Mantissa() const {
    return (Get_Bits() >> 15) & 0x3F;
}

/* ============================================================================
 * --------------------------- Y_Fraction
 * Retrieves the 5-bit fraction of the Y component.
 *
 * ------ Returns ------
 * uint8_t: The 5-bit fraction value of the Y component.
 * ============================================================================
 */
uint8_t Block_VD::Y_Fraction() const {
    return (Get_Bits() >> 10) & 0x1F;
}






/* ============================================================================
 * --------------------------- Z_Sign
 * Retrieves the sign bit of the Z component.
 *
 * ------ Returns ------
 * int: 1 if the sign bit is set (negative), 0 if not (positive).
 * ============================================================================
 */
int Block_VD::Z_Sign() const {
    return (Get_Bits() >> 9) & 0x1;
}

/* ============================================================================
 * --------------------------- Z_Mantissa
 * Retrieves the 4-bit mantissa of the Z component.
 *
 * ------ Returns ------
 * uint8_t: The 4-bit mantissa value of the Z component.
 * ============================================================================
 */
uint8_t Block_VD::Z_Mantissa() const {
    return (Get_Bits() >> 5) & 0xF;
}

/* ============================================================================
 * --------------------------- Z_Fraction
 * Retrieves the 5-bit fraction of the Z component.
 *
 * ------ Returns ------
 * uint8_t: The 5-bit fraction value of the Z component.
 * ============================================================================
 */
uint8_t Block_VD::Z_Fraction() const {
    return Get_Bits() & 0x1F;
}
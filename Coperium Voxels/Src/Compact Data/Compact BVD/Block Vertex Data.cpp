#include "Block Vertex Data.h"

// Constructor
/* ============================================================================
 * --------------------------- Block_VD
 * Constructor for the Block_VD class. Initializes the value to 0.0f.
 * ============================================================================
 */
Block_VD::Block_VD() : value(0.0f) {}






/* ============================================================================
 * --------------------------- Set_X
 * Converts a floating-point value to the custom type and stores it in the X component.
 *
 * ------ Parameters ------
 * f: The floating-point value to be converted and stored in the X component.
 * ============================================================================
 */
void Block_VD::Set_X(float f) {
    int sign = (f < 0) ? 1 : 0;
    f = std::fabs(f);
    uint8_t mantissa = static_cast<uint8_t>(f);
    uint8_t fraction = static_cast<uint8_t>((f - mantissa) * 32.0f);
    Set_X(sign, mantissa, fraction);
}

/* ============================================================================
 * --------------------------- Set_X
 * Sets the X component using a sign bit, mantissa, and fraction.
 *
 * ------ Parameters ------
 * sign: The sign bit (1 for negative, 0 for positive).
 * mantissa: The 4-bit mantissa value.
 * fraction: The 5-bit fraction value.
 * ============================================================================
 */
void Block_VD::Set_X(
    const int sign, const uint8_t mantissa, const uint8_t fraction
){
    uint32_t bits = Get_Bits();
    bits = 
        (bits & 0xFFFFF000)         | // Clear bits 0-9 for X
        ((sign & 0x1)       << 31)  | 
        ((mantissa & 0xF)   << 26)  | 
        ((fraction & 0x1F)  << 21);
    Set_Bits(bits);
}

/* ============================================================================
 * --------------------------- Get_X
 * Converts the X component of the custom type to a float.
 *
 * ------ Returns ------
 * float: The floating-point value representing the X component.
 * ============================================================================
 */
float Block_VD::Get_X() const {
    return 
        (X_Sign() ? -1.0f : 1.0f)   *
        (X_Mantissa()               +
        static_cast<float>(X_Fraction()) / 32.0f);
}






/* ============================================================================
 * --------------------------- Set_Y
 * Converts a floating-point value to the custom type and stores it in the 
 * Y component.
 *
 * ------ Parameters ------
 * f: The floating-point value to be converted and stored in the Y component.
 * ============================================================================
 */
void Block_VD::Set_Y(float f) {
    int sign = (f < 0) ? 1 : 0;
    f = std::fabs(f);
    uint8_t mantissa = static_cast<uint8_t>(f);
    uint8_t fraction = static_cast<uint8_t>((f - mantissa) * 32.0f);
    Set_Y(sign, mantissa, fraction);
}

/* ============================================================================
 * --------------------------- Set_Y
 * Sets the Y component using a sign bit, mantissa, and fraction.
 *
 * ------ Parameters ------
 * sign: The sign bit (1 for negative, 0 for positive).
 * mantissa: The 6-bit mantissa value.
 * fraction: The 5-bit fraction value.
 * ============================================================================
 */
void Block_VD::Set_Y(
    const int sign, const uint8_t mantissa, const uint8_t fraction
){
    uint32_t bits = Get_Bits();
    bits = 
        (bits & 0xC03FFFFF)         | // Clear bits 10-21 for Y
        ((sign & 0x1)       << 21)  | // Y sign bit at bit position 21
        ((mantissa & 0x3F)  << 15)  | // 6-bit mantissa at bits 15-20
        ((fraction & 0x1F)  << 10);    // 5-bit fraction at bits 10-14
    Set_Bits(bits);
}

/* ============================================================================
 * --------------------------- Get_Y
 * Converts the Y component of the custom type to a float.
 *
 * ------ Returns ------
 * float: The floating-point value representing the Y component.
 * ============================================================================
 */
float Block_VD::Get_Y() const {
    return 
        (Y_Sign() ? -1.0f : 1.0f)   *
        (Y_Mantissa()               +
        static_cast<float>(Y_Fraction()) / 32.0f);
}






/* ============================================================================
 * --------------------------- Set_Z
 * Converts a floating-point value to the custom type and stores it in the Z component.
 *
 * ------ Parameters ------
 * f: The floating-point value to be converted and stored in the Z component.
 * ============================================================================
 */
void Block_VD::Set_Z(float f) {
    int sign = (f < 0) ? 1 : 0;
    f = std::fabs(f);
    uint8_t mantissa = static_cast<uint8_t>(f);
    uint8_t fraction = static_cast<uint8_t>((f - mantissa) * 32.0f);
    Set_Z(sign, mantissa, fraction);
}

/* ============================================================================
 * --------------------------- Set_Z
 * Sets the Z component using a sign bit, mantissa, and fraction.
 *
 * ------ Parameters ------
 * sign: The sign bit (1 for negative, 0 for positive).
 * mantissa: The 4-bit mantissa value.
 * fraction: The 5-bit fraction value.
 * ============================================================================
 */
void Block_VD::Set_Z(
    const int sign, const uint8_t mantissa, const uint8_t fraction
){
    uint32_t bits = Get_Bits();
    bits =
        (bits & 0x003FFFFF)         | // Clear bits 22-31 for Z
        ((sign & 0x1)       << 9)   |
        ((mantissa & 0xF)   << 5)   |
        (fraction & 0x1F);
    Set_Bits(bits);
}



/* ============================================================================
 * --------------------------- Get_Z
 * Converts the Z component of the custom type to a float.
 *
 * ------ Returns ------
 * float: The floating-point value representing the Z component.
 * ============================================================================
 */
float Block_VD::Get_Z() const {
    return
        (Z_Sign() ? -1.0f : 1.0f) *
        (Z_Mantissa() +
            static_cast<float>(Z_Fraction()) / 32.0f);
}





/* ============================================================================
 * --------------------------- Convert
 * Combines the x, y, and z components into a single 32-bit GLfloat value.
 *
 * ------ Parameters ------
 * x: The floating-point value representing the x component.
 * y: The floating-point value representing the y component.
 * z: The floating-point value representing the z component.
 *
 * ------ Returns ------
 * GLfloat: A 32-bit floating-point value containing the compacted x, y,
 *          and z components.
 * ============================================================================
 */
GLfloat Block_VD::Convert(const float x, const float y, const float z) {
    Block_VD co_ordinates;
    co_ordinates.Set_X(x);
    co_ordinates.Set_Y(y);
    co_ordinates.Set_Z(z);
    return co_ordinates.value;
}

/* ============================================================================
 * --------------------------- Convert
 * Combines the x, y, and z components into a single 32-bit GLfloat value.
 *
 * ------ Parameters ------
 * x: The floating-point value representing the x component.
 * y: The floating-point value representing the y component.
 * z: The floating-point value representing the z component.
 *
 * ------ Returns ------
 * GLfloat: A 32-bit floating-point value containing the compacted x, y,
 *          and z components.
 * ============================================================================
 */
void Block_VD::Shift(
    Block_VD& co_ordinates, const float x, const float y, const float z
){
    co_ordinates.Set_X(co_ordinates.Get_X() + x);
    co_ordinates.Set_Y(co_ordinates.Get_Y() + y);
    co_ordinates.Set_Z(co_ordinates.Get_Z() + z);
}
#include "CLD.h"

/* ============================================================================
 * --------------------------- CLD
 * Default constructor initializing data to zero.
 * ============================================================================
 */
CLD::CLD() : data(0) {}

/* ============================================================================
 * --------------------------- CLD
 * Constructor that takes a floating point number to then
 * convert/decode
 * ============================================================================
 */
CLD::CLD(float val){
    From_Float(val);
}
/* ============================================================================
 * --------------------------- Set_X
 * Sets the X component from a float by decomposing it into sign, mantissa,
 * and fraction.
 *
 * ------ Parameters ------
 * f: The float value to set for X.
 * ============================================================================
 */
void CLD::Set_X(const float f) {
    bool    sign;
    uint8_t mantissa, 
            fraction;
    Decompose_From_Float(f, sign, mantissa, fraction);
    Set_X               (   sign, mantissa, fraction);
}

/* ============================================================================
 * --------------------------- Set_X
 * Sets the X component with specific sign, mantissa, and fraction values.
 *
 * ------ Parameters ------
 * sign: The sign bit.
 * mantissa: The mantissa part.
 * fraction: The fractional part.
 * ============================================================================
 */
void CLD::Set_X(
    const bool sign, const uint8_t mantissa, const uint8_t fraction
){
    data &= ~X_MASK;

    data |= (sign       & MASK_1_BIT) << X_S_SHIFT;
    data |= (mantissa   & MASK_4_BIT) << X_M_SHIFT;
    data |= (fraction   & MASK_5_BIT) << X_F_SHIFT;
}

/* ============================================================================
 * --------------------------- Get_X
 * Gets the float value of the X component by combining sign, mantissa,
 * and fraction.
 *
 * Returns the decoded float value of X.
 * ============================================================================
 */
float CLD::Get_X() const {
    bool    sign     = (data >> X_S_SHIFT) & MASK_1_BIT;
    uint8_t mantissa = (data >> X_M_SHIFT) & MASK_4_BIT;
    uint8_t fraction = (data >> X_F_SHIFT) & MASK_5_BIT;

    return Combine_To_Float(sign, mantissa, fraction);
}

/* ============================================================================
 * --------------------------- Set_Y
 * Sets the Y component from a float by decomposing it into sign, mantissa,
 * and fraction.
 *
 * ------ Parameters ------
 * f: The float value to set for Y.
 * ============================================================================
 */
void CLD::Set_Y(const float f) {
    bool    sign;
    uint8_t mantissa, 
            fraction;

    Decompose_From_Float(f, sign, mantissa, fraction);
    Set_Y               (   sign, mantissa, fraction);
}

/* ============================================================================
 * --------------------------- Set_Y
 * Sets the Y component with specific sign, mantissa, and fraction values.
 *
 * ------ Parameters ------
 * sign     : The sign bit.
 * mantissa : The mantissa part.
 * fraction : The fractional part.
 * ============================================================================
 */
void CLD::Set_Y(
    const bool sign, const uint8_t mantissa, const uint8_t fraction
){
    data &= ~(Y_MASK);

    data |=  (sign      & MASK_1_BIT) << Y_S_SHIFT;
    data |=  (mantissa  & MASK_6_BIT) << Y_M_SHIFT;
    data |=  (fraction  & MASK_5_BIT) << Y_F_SHIFT;
}

/* ============================================================================
 * --------------------------- Get_Y
 * Gets the float value of the Y component by combining sign, mantissa,
 * and fraction.
 *
 * Returns the decoded float value of Y.
 * ============================================================================
 */
float CLD::Get_Y() const {
    bool sign        = (data >> Y_S_SHIFT) & MASK_1_BIT;
    uint8_t mantissa = (data >> Y_M_SHIFT) & MASK_6_BIT;
    uint8_t fraction = (data >> Y_F_SHIFT) & MASK_5_BIT;

    return Combine_To_Float(sign, mantissa, fraction);
}

/* ============================================================================
 * --------------------------- Set_Z
 * Sets the Z component from a float by decomposing it into sign, mantissa,
 * and fraction.
 *
 * ------ Parameters ------
 * f: The float value to set for Z.
 * ============================================================================
 */
void CLD::Set_Z(const float f) {
    bool    sign;
    uint8_t mantissa, 
            fraction;

    Decompose_From_Float(f, sign, mantissa, fraction);
    Set_Z               (   sign, mantissa, fraction);
}

/* ============================================================================
 * --------------------------- Set_Z
 * Sets the Z component with specific sign, mantissa, and fraction values.
 *
 * ------ Parameters ------
 * sign: The sign bit.
 * mantissa: The mantissa part.
 * fraction: The fractional part.
 * ============================================================================
 */
void CLD::Set_Z(
    const bool sign, const uint8_t mantissa, const uint8_t fraction
) {
    data &= ~(Z_MASK);
    data |=  (sign      & MASK_1_BIT) << Z_S_SHIFT;
    data |=  (mantissa  & MASK_4_BIT) << Z_M_SHIFT;
    data |=  (fraction  & MASK_5_BIT) << Z_F_SHIFT;
}

/* ============================================================================
 * --------------------------- Get_Z
 * Gets the float value of the Z component by combining sign, mantissa,
 * and fraction.
 *
 * Returns the decoded float value of Z.
 * ============================================================================
 */
float CLD::Get_Z() const {
    bool sign           = (data >> Z_S_SHIFT) & MASK_1_BIT;
    uint8_t mantissa    = (data >> Z_M_SHIFT) & MASK_4_BIT;
    uint8_t fraction    = (data >> Z_F_SHIFT) & MASK_5_BIT;
    return Combine_To_Float(sign, mantissa, fraction);
}

/* ============================================================================
 * --------------------------- To_Float
 * Converts the internal 32-bit integer representation to a float.
 *
 * Returns the float representation of the encoded data.
 * ============================================================================
 */
float CLD::To_Float() const {
    float result;

    std::memcpy(&result, &data, sizeof(data));

    return result;
}

/* ============================================================================
 * --------------------------- From_Float
 * Sets the internal 32-bit integer representation from a float.
 *
 * ------ Parameters ------
 * f: The float to decode into internal representation.
 * ============================================================================
 */
void CLD::From_Float(const float f) {
    std::memcpy(&data, &f, sizeof(data));
}

/* ============================================================================
 * --------------------------- Shift
 * Shifts the X, Y, and Z components by the given amounts.
 *
 * ------ Parameters ------
 * x: The amount to shift the X component.
 * y: The amount to shift the Y component.
 * z: The amount to shift the Z component.
 * ============================================================================
 */
void CLD::Shift(const float x, const float y, const float z){
    Set_X(Get_X() + x);
    Set_Y(Get_Y() + y);
    Set_Z(Get_Z() + z);
}
/* ============================================================================
 * --------------------------- Scale
 * Scales the X, Y, and Z components by a given factor.
 *
 * ------ Parameters ------
 * factor: The multiplier to scale each component.
 *
 * This function multiplies the current X, Y, and Z values by the factor,
 * and updates the internal data accordingly.
 * ============================================================================
 */
void CLD::Scale(const float f) {
    Set_X(Get_X() * f);
    Set_Y(Get_Y() * f);
    Set_Z(Get_Z() * f);
}
/* ============================================================================
 * --------------------------- Compact
 * Static method to create a compacted float from three float components.
 *
 * ------ Parameters ------
 * x: The X component as a float.
 * y: The Y component as a float.
 * z: The Z component as a float.
 *
 * Returns a compacted float encoding all three components.
 * ============================================================================
 */
float CLD::Compact(float x, float y, float z) {
    CLD block_vertex;

    block_vertex.Set_X(x);
    block_vertex.Set_Y(y);
    block_vertex.Set_Z(z);

    return block_vertex.To_Float();
}

/* ============================================================================
 * --------------------------- Combine_To_Float
 * Combines the sign, mantissa, and fraction to create a float representation.
 *
 * ------ Parameters ------
 * sign: The sign bit.
 * mantissa: The mantissa part.
 * fraction: The fractional part.
 *
 * Returns the combined float value.
 * ============================================================================
 */
float CLD::Combine_To_Float(
    const bool sign, const uint8_t mantissa, const uint8_t fraction
)const{
    float value = mantissa + 
                 (fraction / 
                  DIVISOR   );

    return sign ? -value : value;
}

/* ============================================================================
 * --------------------------- Decompose_From_Float
 * Decomposes a float value into sign, mantissa, and fraction components.
 *
 * ------ Parameters ------
 * f: The float value to decompose.
 * sign: The sign bit (output).
 * mantissa: The mantissa part (output).
 * fraction: The fractional part (output).
 * ============================================================================
 */
void CLD::Decompose_From_Float(
    const float f,          bool&       sign, 
    uint8_t&    mantissa,   uint8_t&    fraction
)const{
    sign        = f < 0;
    float abs_f = std::abs(f);
    mantissa    = static_cast<uint8_t>( abs_f);
    fraction    = static_cast<uint8_t>((abs_f - mantissa) * DIVISOR);
}

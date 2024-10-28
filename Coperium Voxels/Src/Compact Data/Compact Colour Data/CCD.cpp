#include "CCD.h"

/* ============================================================================
 * --------------------------- CCD
 * Default constructor initializing data to default RGBA (0, 0, 0, 255).
 * ============================================================================
 */
CCD::CCD() : data(255 << A_SHIFT) {}

/* ============================================================================
 * --------------------------- CCD
 * Default constructor initializing data to a given value
 * ============================================================================
 */
CCD::CCD(float data) {
    From_Float(data);
}

/* ============================================================================
 * --------------------------- Set_R
 * Sets the Red component using an integer.
 *
 * ------ Parameters ------
 * r: The integer value to set for Red (0-255).
 * ============================================================================
 */
void CCD::Set_R(int r) {
    data &= ~(R_MASK);
    data |= (r & MASK_8_BIT) << R_SHIFT;
}

/* ============================================================================
 * --------------------------- Set_G
 * Sets the Green component using an integer.
 *
 * ------ Parameters ------
 * g: The integer value to set for Green (0-255).
 * ============================================================================
 */
void CCD::Set_G(int g) {
    data &= ~(G_MASK);
    data |= (g & MASK_8_BIT) << G_SHIFT;
}

/* ============================================================================
 * --------------------------- Set_B
 * Sets the Blue component using an integer.
 *
 * ------ Parameters ------
 * b: The integer value to set for Blue (0-255).
 * ============================================================================
 */
void CCD::Set_B(int b) {
    data &= ~(B_MASK);
    data |= (b & MASK_8_BIT) << B_SHIFT;
}

/* ============================================================================
 * --------------------------- Set_A
 * Sets the Alpha component using an integer.
 *
 * ------ Parameters ------
 * a: The integer value to set for Alpha (0-255). Defaults to 255.
 * ============================================================================
 */
void CCD::Set_A(int a) {
    data &= ~(A_MASK);
    data |= (a & MASK_8_BIT) << A_SHIFT;
}

/* ============================================================================
 * --------------------------- Set_R
 * Sets the Red component using a float.
 *
 * ------ Parameters ------
 * r: The float value to set for Red (0.0-1.0).
 * ============================================================================
 */
void CCD::Set_R(float r) {
    Set_R(static_cast<int>(r * 255));
}

/* ============================================================================
 * --------------------------- Set_G
 * Sets the Green component using a float.
 *
 * ------ Parameters ------
 * g: The float value to set for Green (0.0-1.0).
 * ============================================================================
 */
void CCD::Set_G(float g) {
    Set_G(static_cast<int>(g * 255));
}

/* ============================================================================
 * --------------------------- Set_B
 * Sets the Blue component using a float.
 *
 * ------ Parameters ------
 * b: The float value to set for Blue (0.0-1.0).
 * ============================================================================
 */
void CCD::Set_B(float b) {
    Set_B(static_cast<int>(b * 255));
}

/* ============================================================================
 * --------------------------- Set_A
 * Sets the Alpha component using a float.
 *
 * ------ Parameters ------
 * a: The float value to set for Alpha (0.0-1.0). Defaults to 1.0.
 * ============================================================================
 */
void CCD::Set_A(float a) {
    Set_A(static_cast<int>(a * 255));
}

/* ============================================================================
 * --------------------------- Get_R
 * Gets the Red component as an integer.
 *
 * Returns the integer value of Red (0-255).
 * ============================================================================
 */
int CCD::Get_R() const {
    return (data >> R_SHIFT) & MASK_8_BIT;
}

/* ============================================================================
 * --------------------------- Get_G
 * Gets the Green component as an integer.
 *
 * Returns the integer value of Green (0-255).
 * ============================================================================
 */
int CCD::Get_G() const {
    return (data >> G_SHIFT) & MASK_8_BIT;
}

/* ============================================================================
 * --------------------------- Get_B
 * Gets the Blue component as an integer.
 *
 * Returns the integer value of Blue (0-255).
 * ============================================================================
 */
int CCD::Get_B() const {
    return (data >> B_SHIFT) & MASK_8_BIT;
}

/* ============================================================================
 * --------------------------- Get_A
 * Gets the Alpha component as an integer.
 *
 * Returns the integer value of Alpha (0-255).
 * ============================================================================
 */
int CCD::Get_A() const {
    return (data >> A_SHIFT) & MASK_8_BIT;
}

/* ============================================================================
 * --------------------------- Get_Rf
 * Gets the Red component as a float.
 *
 * Returns the float value of Red (0.0-1.0).
 * ============================================================================
 */
float CCD::Get_Rf() const {
    return Get_R() / 255.0f;
}

/* ============================================================================
 * --------------------------- Get_Gf
 * Gets the Green component as a float.
 *
 * Returns the float value of Green (0.0-1.0).
 * ============================================================================
 */
float CCD::Get_Gf() const {
    return Get_G() / 255.0f;
}

/* ============================================================================
 * --------------------------- Get_Bf
 * Gets the Blue component as a float.
 *
 * Returns the float value of Blue (0.0-1.0).
 * ============================================================================
 */
float CCD::Get_Bf() const {
    return Get_B() / 255.0f;
}

/* ============================================================================
 * --------------------------- Get_Af
 * Gets the Alpha component as a float.
 *
 * Returns the float value of Alpha (0.0-1.0).
 * ============================================================================
 */
float CCD::Get_Af() const {
    return Get_A() / 255.0f;
}

/* ============================================================================
 * --------------------------- To_Float
 * Converts the internal 32-bit integer representation to a float.
 *
 * Returns the float representation of the encoded RGBA data.
 * ============================================================================
 */
float CCD::To_Float() const {
    float result;
    std::memcpy(&result, &data, sizeof(data));
    return result;
}

/* ============================================================================
 * --------------------------- From_Float
 * Sets the internal 32-bit integer representation from a float.
 *
 * ------ Parameters ------
 * value: The float to decode into internal representation.
 * ============================================================================
 */
void CCD::From_Float(float value) {
    std::memcpy(&data, &value, sizeof(data));
}

/* ============================================================================
 * --------------------------- Compact
 * Static method to create a compacted float from four integer components.
 *
 * ------ Parameters ------
 * r: The Red component as an integer (0-255).
 * g: The Green component as an integer (0-255).
 * b: The Blue component as an integer (0-255).
 * a: The Alpha component as an integer (0-255). Defaults to 255.
 *
 * Returns a compacted float encoding all four components.
 * ============================================================================
 */
float CCD::Compact(int r, int g, int b, int a) {
    CCD color;
    color.Set_R(r);
    color.Set_G(g);
    color.Set_B(b);
    color.Set_A(a);
    return color.To_Float();
}

/* ============================================================================
 * --------------------------- Compact (Overload)
 * Static method to create a compacted float from four float components.
 *
 * ------ Parameters ------
 * r: The Red component as a float (0.0-1.0).
 * g: The Green component as a float (0.0-1.0).
 * b: The Blue component as a float (0.0-1.0).
 * a: The Alpha component as a float (0.0-1.0). Defaults to 1.0.
 *
 * Returns a compacted float encoding all four components.
 * ============================================================================
 */
float CCD::Compact(float r, float g, float b, float a) {
    return Compact(static_cast<int>(r * 255),
        static_cast<int>(g * 255),
        static_cast<int>(b * 255),
        static_cast<int>(a * 255));
}

/* ============================================================================
 * --------------------------- Scale
 * Scales the Red, Green, and Blue components by given float values in
 * range (0.0-1.0).
 *
 * ------ Parameters ------
 * rScale: Scaling factor for Red (0.0-1.0).
 * gScale: Scaling factor for Green (0.0-1.0).
 * bScale: Scaling factor for Blue (0.0-1.0).
 * aScale: Scaling factor for Alpha (0.0-1.0). Defaults to 1.0.
 * ============================================================================
 */
void CCD::Scale(float rScale, float gScale, float bScale, float aScale) {
    Set_R(Get_Rf() * rScale);
    Set_G(Get_Gf() * gScale);
    Set_B(Get_Bf() * bScale);
    Set_A(Get_Af() * aScale);
}

/* ============================================================================
 * --------------------------- Scale
 * Scales the Red, Green, and Blue components by given integer values in
 * range (0-255).
 *
 * ------ Parameters ------
 * rScale: Scaling factor for Red (0-255).
 * gScale: Scaling factor for Green (0-255).
 * bScale: Scaling factor for Blue (0-255).
 * aScale: Scaling factor for Alpha (0-255). Defaults to 255.
 * ============================================================================
 */
void CCD::Scale(int rScale, int gScale, int bScale, int aScale) {
    Scale(  (float)(rScale / 255), 
            (float)(gScale / 255),
            (float)(bScale / 255),
            (float)(aScale / 255));
}

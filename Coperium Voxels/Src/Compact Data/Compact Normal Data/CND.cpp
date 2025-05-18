#include "CND.h"
#include <glm/gtc/constants.hpp>
#include <cmath>

/* ============================================================================
 * --------------------------- CND::CND
 * Default constructor initializes data to zero (0,0,0).
 * ============================================================================
 */
CND::CND()
    : data(0)
{}

/* ============================================================================
 * --------------------------- CND::CND
 * Constructs a CND from a packed float representation.
 *
 * ------ Parameters ------
 * packed: The 32-bit float containing packed normals.
 * ============================================================================
 */
CND::CND(float packed)
{
    From_Float(packed);
}

/* ============================================================================
 * --------------------------- CND::To_Float
 * Converts the internal 32-bit data to a float for storage (e.g., VBO).
 *
 * Returns the float representation of packed normals.
 * ============================================================================
 */
float CND::To_Float() const
{
    float f;
    std::memcpy(&f, &data, sizeof(data));
    return f;
}

/* ============================================================================
 * --------------------------- CND::From_Float
 * Sets internal data from a packed float.
 *
 * ------ Parameters ------
 * f: The float containing packed normals.
 * ============================================================================
 */
void CND::From_Float(float f)
{
    std::memcpy(&data, &f, sizeof(data));
}

/* ============================================================================
 * --------------------------- CND::Set_X
 * Packs the X component into internal data.
 *
 * ------ Parameters ------
 * vx: The X component in [-1,1].
 * ============================================================================
 */
void CND::Set_X(float vx)
{
    bool s = vx < 0.0f;
    uint32_t m = static_cast<uint32_t>(std::round(std::abs(vx) * MAG_SCALE)) & MASK_9;
    data &= ~((MASK_1 << X_S_SHIFT) | (MASK_9 << X_M_SHIFT));
    data |= (uint32_t(s) << X_S_SHIFT) | (m << X_M_SHIFT);
}

/* ============================================================================
 * --------------------------- CND::Set_Y
 * Packs the Y component into internal data.
 *
 * ------ Parameters ------
 * vy: The Y component in [-1,1].
 * ============================================================================
 */
void CND::Set_Y(float vy)
{
    bool s = vy < 0.0f;
    uint32_t m = static_cast<uint32_t>(std::round(std::abs(vy) * MAG_SCALE)) & MASK_9;
    data &= ~((MASK_1 << Y_S_SHIFT) | (MASK_9 << Y_M_SHIFT));
    data |= (uint32_t(s) << Y_S_SHIFT) | (m << Y_M_SHIFT);
}

/* ============================================================================
 * --------------------------- CND::Set_Z
 * Packs the Z component into internal data.
 *
 * ------ Parameters ------
 * vz: The Z component in [-1,1].
 * ============================================================================
 */
void CND::Set_Z(float vz)
{
    bool s = vz < 0.0f;
    uint32_t m = static_cast<uint32_t>(std::round(std::abs(vz) * MAG_SCALE)) & MASK_9;
    data &= ~((MASK_1 << Z_S_SHIFT) | (MASK_9 << Z_M_SHIFT));
    data |= (uint32_t(s) << Z_S_SHIFT) | (m << Z_M_SHIFT);
}

/* ============================================================================
 * --------------------------- CND::Get_X
 * Unpacks and returns the X component.
 *
 * Returns the X component as float in [-1,1].
 * ============================================================================
 */
float CND::Get_X() const
{
    bool s = (data >> X_S_SHIFT) & MASK_1;
    uint32_t m = (data >> X_M_SHIFT) & MASK_9;
    float v = float(m) / MAG_SCALE;
    return s ? -v : v;
}

/* ============================================================================
 * --------------------------- CND::Get_Y
 * Unpacks and returns the Y component.
 *
 * Returns the Y component as float in [-1,1].
 * ============================================================================
 */
float CND::Get_Y() const
{
    bool s = (data >> Y_S_SHIFT) & MASK_1;
    uint32_t m = (data >> Y_M_SHIFT) & MASK_9;
    float v = float(m) / MAG_SCALE;
    return s ? -v : v;
}

/* ============================================================================
 * --------------------------- CND::Get_Z
 * Unpacks and returns the Z component.
 *
 * Returns the Z component as float in [-1,1].
 * ============================================================================
 */
float CND::Get_Z() const
{
    bool s = (data >> Z_S_SHIFT) & MASK_1;
    uint32_t m = (data >> Z_M_SHIFT) & MASK_9;
    float v = float(m) / MAG_SCALE;
    return s ? -v : v;
}

/* ============================================================================
 * --------------------------- CND::Unpack
 * Returns all three components as a glm::vec3.
 *
 * Returns vec3(X, Y, Z).
 * ============================================================================
 */
glm::vec3 CND::Unpack() const
{
    return glm::vec3(Get_X(), Get_Y(), Get_Z());
}

/* ============================================================================
 * --------------------------- CND::Compact
 * Static helper to pack X,Y,Z into a float in one call.
 *
 * ------ Parameters ------
 * x, y, z: Components in [-1,1].
 *
 * Returns the packed float.
 * ============================================================================
 */
float CND::Compact(float x, float y, float z)
{
    CND c;
    c.Set_X(x);
    c.Set_Y(y);
    c.Set_Z(z);
    return c.To_Float();
}

/* ============================================================================
 * --------------------------- CND::Scale
 * Scales unpacked normal by factor, then renormalizes.
 *
 * ------ Parameters ------
 * factor: Scale multiplier.
 * ============================================================================
 */
void CND::Scale(float factor)
{
    glm::vec3 v = Unpack() * factor;
    Normalize(v);
}

/* ============================================================================
 * --------------------------- CND::Normalize
 * Renormalizes current packed data to unit length.
 * ============================================================================
 */
void CND::Normalize()
{
    glm::vec3 v = Unpack();
    Normalize(v);
}

/* ============================================================================
 * --------------------------- CND::Normalize
 * Helper that takes a glm::vec3, normalizes it, and packs back.
 *
 * ------ Parameters ------
 * v: The vector to normalize and pack.
 * ============================================================================
 */
void CND::Normalize(const glm::vec3& v)
{
    float len = std::sqrt(glm::dot(v, v));
    if (len > 0.0f) {
        Set_X(v.x / len);
        Set_Y(v.y / len);
        Set_Z(v.z / len);
    }
    else {
        data = 0;
    }
}

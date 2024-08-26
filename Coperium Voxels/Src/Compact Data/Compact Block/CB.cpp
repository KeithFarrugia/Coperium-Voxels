#include "CB.h"

/* ============================================================================
 * --------------------------- CB
 * Default constructor initializing data to 0.
 * ============================================================================
 */
CB::CB() : data(0) {}

/* ============================================================================
 * --------------------------- CB
 * Constructor initializing data with given values.
 * ============================================================================
 */
CB::CB(
    const int x, const int y, const int z, 
    const int r, const int g, const int b
) {
    Set_X(x);
    Set_Y(y);
    Set_Z(z);
    Set_R(r);
    Set_G(g);
    Set_B(b);
}

/* ============================================================================
 * --------------------------- Set_X
 * Sets the X value (4 bits).
 *
 * ------ Parameters ------
 * x: The X value (0-15).
 * ============================================================================
 */
void CB::Set_X(int x) {
    data &= ~(X_MASK);

    data |= ((x & MASK_4_BIT) << X_SHIFT);
}

/* ============================================================================
 * --------------------------- Set_Y
 * Sets the Y value (6 bits).
 *
 * ------ Parameters ------
 * y: The Y value (0-63).
 * ============================================================================
 */
void CB::Set_Y(int y) {
    data &= ~(Y_MASK);

    data |= ((y & MASK_6_BIT) << Y_SHIFT);
}

/* ============================================================================
 * --------------------------- Set_Z
 * Sets the Z value (4 bits).
 *
 * ------ Parameters ------
 * z: The Z value (0-15).
 * ============================================================================
 */
void CB::Set_Z(int z) {
    data &= ~(Z_MASK);

    data |= ((z & MASK_4_BIT) << Z_SHIFT);
}

/* ============================================================================
 * --------------------------- Set_R
 * Sets the Red component (4 bits).
 *
 * ------ Parameters ------
 * r: The Red value (0-15).
 * ============================================================================
 */
void CB::Set_R(int r) {
    data &= ~(R_MASK);

    data |= ((r & MASK_4_BIT) << R_SHIFT);
}

/* ============================================================================
 * --------------------------- Set_G
 * Sets the Green component (4 bits).
 *
 * ------ Parameters ------
 * g: The Green value (0-15).
 * ============================================================================
 */
void CB::Set_G(int g) {
    data &= ~(G_MASK);

    data |= ((g & MASK_4_BIT) << G_SHIFT);
}

/* ============================================================================
 * --------------------------- Set_B
 * Sets the Blue component (4 bits).
 *
 * ------ Parameters ------
 * b: The Blue value (0-15).
 * ============================================================================
 */
void CB::Set_B(int b) {
    data &= ~(B_MASK);

    data |= ((b & MASK_4_BIT) << B_SHIFT);
}

/* ============================================================================
 * --------------------------- Set_All
 * Sets the the values to the given values
 * ============================================================================
 */
void CB::Set_All(
    const int x, const int y, const int z, 
    const int r, const int g, const int b
){
    Set_X(x);   Set_R(r);
    Set_Y(y);   Set_G(g);
    Set_Z(z);   Set_B(b);
}

/* ============================================================================
 * --------------------------- Get_X
 * Gets the X value (4 bits).
 *
 * Returns the X value (0-15).
 * ============================================================================
 */
int CB::Get_X() const {
    return (data >> X_SHIFT) & MASK_4_BIT;
}

/* ============================================================================
 * --------------------------- Get_Y
 * Gets the Y value (6 bits).
 *
 * Returns the Y value (0-63).
 * ============================================================================
 */
int CB::Get_Y() const {
    return (data >> Y_SHIFT) & MASK_6_BIT;
}

/* ============================================================================
 * --------------------------- Get_Z
 * Gets the Z value (4 bits).
 *
 * Returns the Z value (0-15).
 * ============================================================================
 */
int CB::Get_Z() const {
    return (data >> Z_SHIFT) & MASK_4_BIT;
}

/* ============================================================================
 * --------------------------- Get_R
 * Gets the Red component (4 bits).
 *
 * Returns the Red value (0-15).
 * ============================================================================
 */
int CB::Get_R() const {
    return (data >> R_SHIFT) & MASK_4_BIT;
}

/* ============================================================================
 * --------------------------- Get_G
 * Gets the Green component (4 bits).
 *
 * Returns the Green value (0-15).
 * ============================================================================
 */
int CB::Get_G() const {
    return (data >> G_SHIFT) & MASK_4_BIT;
}

/* ============================================================================
 * --------------------------- Get_B
 * Gets the Blue component (4 bits).
 *
 * Returns the Blue value (0-15).
 * ============================================================================
 */
int CB::Get_B() const {
    return (data >> B_SHIFT) & MASK_4_BIT;
}

/* ============================================================================
 * --------------------------- Generate_Mesh
 * Generates a mesh
 * ============================================================================
 */
std::unique_ptr<GLfloat[]> CB::Generate_Mesh() const{
    float x = (float) Get_X();
    float y = (float) Get_Y();
    float z = (float) Get_Z();

    float r = ((float)Get_R()) / 16.0f;
    float g = ((float)Get_G()) / 16.0f;
    float b = ((float)Get_B()) / 16.0f;

    auto cube_mesh = std::make_unique<GLfloat[]>(COMPACT_CUBE_SIZE);

    std::copy(  COMPACT_CUBE, 
                COMPACT_CUBE + COMPACT_CUBE_SIZE,
                cube_mesh.get());

    for (size_t i = 0; i < COMPACT_CUBE_SIZE; i += COMPACT_CUBE_ELEMENTS) {
        CLD loc(cube_mesh[i]);
        CCD col(cube_mesh[i + 1]);

        loc.Shift(x, y, z);
        col.Scale(r, g, b);

        cube_mesh[i]     = loc.To_Float();
        cube_mesh[i + 1] = col.To_Float();
    }

    return cube_mesh;
}

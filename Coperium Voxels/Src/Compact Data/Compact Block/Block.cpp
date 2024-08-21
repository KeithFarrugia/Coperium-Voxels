#include "Block.h"

/* ============================================================================
 * --------------------------- Block::Block
 * Constructor that initializes a Block object with the given x, y, z coordinates
 * and r, g, b color values. It uses the Set_All method to assign these values.
 *
 * ------ Parameters ------
 * x: The x-coordinate of the Block (0-15).
 * y: The y-coordinate of the Block (0-15).
 * z: The z-coordinate of the Block (0-15).
 * r: The red color component of the Block (0-15).
 * g: The green color component of the Block (0-15).
 * b: The blue color component of the Block (0-15).
 * ============================================================================
 */
Block::Block(uint8_t x, uint8_t y, uint8_t z, uint8_t r, uint8_t g, uint8_t b) {
    Set_All(x, y, z, r, g, b);
}

/* ============================================================================
 * --------------------------- Block::Get_X
 * Retrieves the x-coordinate from the Block's data.
 *
 * ------ Returns ------
 * uint8_t: The x-coordinate (4-bit value).
 * ============================================================================
 */
uint8_t Block::Get_X() const {
    return (data >> 28) & MASK_4_BITS;
}

/* ============================================================================
 * --------------------------- Block::Get_Y
 * Retrieves the y-coordinate from the Block's data.
 *
 * ------ Returns ------
 * uint8_t: The y-coordinate (4-bit value).
 * ============================================================================
 */
uint8_t Block::Get_Y() const {
    return (data >> 24) & MASK_4_BITS;
}

/* ============================================================================
 * --------------------------- Block::Get_Z
 * Retrieves the z-coordinate from the Block's data.
 *
 * ------ Returns ------
 * uint8_t: The z-coordinate (4-bit value).
 * ============================================================================
 */
uint8_t Block::Get_Z() const {
    return (data >> 20) & MASK_4_BITS;
}

/* ============================================================================
 * --------------------------- Block::Get_R
 * Retrieves the red color component from the Block's data.
 *
 * ------ Returns ------
 * uint8_t: The red color component (4-bit value).
 * ============================================================================
 */
uint8_t Block::Get_R() const {
    return (data >> 16) & MASK_4_BITS;
}

/* ============================================================================
 * --------------------------- Block::Get_G
 * Retrieves the green color component from the Block's data.
 *
 * ------ Returns ------
 * uint8_t: The green color component (4-bit value).
 * ============================================================================
 */
uint8_t Block::Get_G() const {
    return (data >> 12) & MASK_4_BITS;
}

/* ============================================================================
 * --------------------------- Block::Get_B
 * Retrieves the blue color component from the Block's data.
 *
 * ------ Returns ------
 * uint8_t: The blue color component (4-bit value).
 * ============================================================================
 */
uint8_t Block::Get_B() const {
    return (data >> 8) & MASK_4_BITS;
}

/* ============================================================================
 * --------------------------- Block::Set_X
 * Sets the x-coordinate in the Block's data. The x value is masked to ensure
 * it is within 4 bits and then positioned correctly in the data variable.
 *
 * ------ Parameters ------
 * x: The x-coordinate (4-bit value).
 * ============================================================================
 */
void Block::Set_X(const uint8_t x) {
    data =
        (data & ~(MASK_4_BITS << 28))
        | ((x & MASK_4_BITS) << 28);
}

/* ============================================================================
 * --------------------------- Block::Set_Y
 * Sets the y-coordinate in the Block's data. The y value is masked to ensure
 * it is within 4 bits and then positioned correctly in the data variable.
 *
 * ------ Parameters ------
 * y: The y-coordinate (4-bit value).
 * ============================================================================
 */
void Block::Set_Y(const uint8_t y) {
    data = (data & ~(MASK_4_BITS << 24)) | ((y & MASK_4_BITS) << 24);
}

/* ============================================================================
 * --------------------------- Block::Set_Z
 * Sets the z-coordinate in the Block's data. The z value is masked to ensure
 * it is within 4 bits and then positioned correctly in the data variable.
 *
 * ------ Parameters ------
 * z: The z-coordinate (4-bit value).
 * ============================================================================
 */
void Block::Set_Z(const uint8_t z) {
    data = (data & ~(MASK_4_BITS << 20)) | ((z & MASK_4_BITS) << 20);
}

/* ============================================================================
 * --------------------------- Block::Set_R
 * Sets the red color component in the Block's data. The r value is masked
 * to ensure it is within 4 bits and then positioned correctly in the data
 * variable.
 *
 * ------ Parameters ------
 * r: The red color component (4-bit value).
 * ============================================================================
 */
void Block::Set_R(const uint8_t r) {
    data = (data & ~(MASK_4_BITS << 16)) | ((r & MASK_4_BITS) << 16);
}

/* ============================================================================
 * --------------------------- Block::Set_G
 * Sets the green color component in the Block's data. The g value is masked t
 * o ensure it is within 4 bits and then positioned correctly in the data
 * variable.
 *
 * ------ Parameters ------
 * g: The green color component (4-bit value).
 * ============================================================================
 */
void Block::Set_G(const uint8_t g) {
    data = (data & ~(MASK_4_BITS << 12)) | ((g & MASK_4_BITS) << 12);
}

/* ============================================================================
 * --------------------------- Block::Set_B
 * Sets the blue color component in the Block's data. The b value is
 * masked to ensure it is within 4 bits and then positioned correctly
 * in the data variable.
 *
 * ------ Parameters ------
 * b: The blue color component (4-bit value).
 * ============================================================================
 */
void Block::Set_B(const uint8_t b) {
    data = (data & ~(MASK_4_BITS << 8)) | ((b & MASK_4_BITS) << 8);
}

/* ============================================================================
 * --------------------------- Block::Set_All
 * Sets all the x, y, z coordinates and r, g, b color components in the
 * Block's data at once. Each value is masked to ensure it is within 4 bits
 * and then positioned correctly in the data variable.
 *
 * ------ Parameters ------
 * x: The x-coordinate (4-bit value).
 * y: The y-coordinate (4-bit value).
 * z: The z-coordinate (4-bit value).
 * r: The red color component (4-bit value).
 * g: The green color component (4-bit value).
 * b: The blue color component (4-bit value).
 * ============================================================================
 */
void Block::Set_All(
    const uint8_t x, const uint8_t y, const uint8_t z,
    const uint8_t r, const uint8_t g, const uint8_t b
) {
    data =
        ((x & MASK_4_BITS) << 28) |
        ((y & MASK_4_BITS) << 24) |
        ((z & MASK_4_BITS) << 20) |
        ((r & MASK_4_BITS) << 16) |
        ((g & MASK_4_BITS) << 12) |
        ((b & MASK_4_BITS) << 8);
}

/* ============================================================================
 * --------------------------- Block::Generate_Cube_Vertices
 * Generates the vertices of a cube based on the Block's position (x, y, z) and
 * color (r, g, b). The color components are normalized to the range [0, 1].
 *
 * ------ Returns ------
 * std::unique_ptr<GLfloat[]>: A unique pointer to an array of 216 GLfloat values
 * representing the vertices and color of the cube.
 * ============================================================================
 */
std::unique_ptr<GLfloat[]> Block::Generate_Cube_Vertices() const {
    float x = get_x();
    float y = get_y();
    float z = get_z();

    float r = static_cast<float>(get_r()) / 16.0f;
    float g = static_cast<float>(get_g()) / 16.0f;
    float b = static_cast<float>(get_b()) / 16.0f;

    auto cube_mesh = std::make_unique<GLfloat[]>(216);
    std::copy(block_vertices, block_vertices + 216, cube_mesh.get());

    for (int i = 0; i < 216; i += 6) {
        cube_mesh[i + 0] += x;
        cube_mesh[i + 1] += y;
        cube_mesh[i + 2] += z;

        cube_mesh[i + 3] *= r;
        cube_mesh[i + 4] *= g;
        cube_mesh[i + 5] *= b;
    }

    return cube_mesh;
}

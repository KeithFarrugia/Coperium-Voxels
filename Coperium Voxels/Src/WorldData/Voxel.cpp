#include "World.h"

/* ============================================================================
 * --------------------------- Voxel Constructor
 * Initializes a Voxel object and sets the data to 0 by default.
 * ============================================================================
 */
Voxel::Voxel() {
    data = 0;
}
/* ============================================================================
 * --------------------------- Voxel (Copy Constructor)
 * Copy Constructor
 * ============================================================================
 */

Voxel::Voxel(const Voxel& other) : data(other.data) {}

/* ============================================================================
 * --------------------------- Voxel Parameterized Constructor
 * Initializes a Voxel object using the provided voxelData structure.
 * The data is compacted into the `data` field using the Compact method.
 *
 * ------ Parameters ------
 * voxelData: Struct containing voxel information like color, transparency, etc.
 * ============================================================================
 */
Voxel::Voxel(const vox_data_t voxelData) : data(0) {
    data = Compact(voxelData).data;
}

/* ============================================================================
 * --------------------------- Voxel Destructor
 * Destroys the Voxel object.
 * ============================================================================
 */
Voxel::~Voxel() {}

/* ============================================================================
 * --------------------------- SetSolid
 * Sets the solid flag for the voxel in the most significant bit.
 *
 * ------ Parameters ------
 * solid: Boolean flag to set whether the voxel is solid or not.
 * ============================================================================
 */
void Voxel::SetSolid(bool solid) {
    data = (data & ~(1 << 31)) | (solid << 31);
}

/* ============================================================================
 * --------------------------- SetTransparency
 * Sets the transparency flag for the voxel in the 2nd most significant bit.
 *
 * ------ Parameters ------
 * transparency: Boolean flag to set whether the voxel is transparent or not.
 * ============================================================================
 */
void Voxel::SetTransparency(bool transparency) {
    data = (data & ~(1 << 30)) | (transparency << 30);
}

/* ============================================================================
 * --------------------------- SetR
 * Sets the red color value in the voxel data (4 bits at positions 26 to 29).
 *
 * ------ Parameters ------
 * r: Red color value (4 bits).
 * ============================================================================
 */
void Voxel::SetR(uint8_t r) {
    data &= ~(0xF << 26); // Clear the 4 bits for red (bits 26 to 29)
    data |= ((r & 0xF) << 26); // Set red bits (bits 26 to 29)
}

/* ============================================================================
 * --------------------------- SetG
 * Sets the green color value in the voxel data (4 bits at positions 22 to 25).
 *
 * ------ Parameters ------
 * g: Green color value (4 bits).
 * ============================================================================
 */
void Voxel::SetG(uint8_t g) {
    data &= ~(0xF << 22); // Clear the 4 bits for green (bits 22 to 25)
    data |= ((g & 0xF) << 22); // Set green bits (bits 22 to 25)
}

/* ============================================================================
 * --------------------------- SetB
 * Sets the blue color value in the voxel data (4 bits at positions 18 to 21).
 *
 * ------ Parameters ------
 * b: Blue color value (4 bits).
 * ============================================================================
 */
void Voxel::SetB(uint8_t b) {
    data &= ~(0xF << 18); // Clear the 4 bits for blue (bits 18 to 21)
    data |= ((b & 0xF) << 18); // Set blue bits (bits 18 to 21)
}

/* ============================================================================
 * --------------------------- SetType
 * Sets the type of the voxel (occupying the least significant 17 bits).
 *
 * ------ Parameters ------
 * type: Integer value representing the voxel type (17 bits).
 * ============================================================================
 */
void Voxel::SetType(uint32_t type) {
    data &= ~(0x1FFFF); // Clear the last 17 bits for type
    data |= (type & 0x1FFFF); // Set type (17 bits)
}

/* ============================================================================
 * --------------------------- IsSolid
 * Returns whether the voxel is solid or not by checking the most significant bit.
 *
 * ------ Returns ------
 * true if the voxel is solid, false otherwise.
 * ============================================================================
 */
bool Voxel::IsSolid() const {
    return (data >> 31) & 0x1; // Get the 1st bit
}

/* ============================================================================
 * --------------------------- IsTransparent
 * Returns whether the voxel is transparent or not by checking the 2nd most significant bit.
 *
 * ------ Returns ------
 * true if the voxel is transparent, false otherwise.
 * ============================================================================
 */
bool Voxel::IsTransparent() const {
    return (data >> 30) & 0x1; // Get the 2nd bit
}

/* ============================================================================
 * --------------------------- GetR
 * Retrieves the red color component from the voxel data (4 bits at positions 26 to 29).
 *
 * ------ Returns ------
 * Red color component (4 bits).
 * ============================================================================
 */
uint8_t Voxel::GetR() const {
    return (data >> 26) & 0xF; // Get the red component (4 bits)
}

/* ============================================================================
 * --------------------------- GetG
 * Retrieves the green color component from the voxel data (4 bits at positions 22 to 25).
 *
 * ------ Returns ------
 * Green color component (4 bits).
 * ============================================================================
 */
uint8_t Voxel::GetG() const {
    return (data >> 22) & 0xF; // Get the green component (4 bits)
}

/* ============================================================================
 * --------------------------- GetB
 * Retrieves the blue color component from the voxel data (4 bits at positions 18 to 21).
 *
 * ------ Returns ------
 * Blue color component (4 bits).
 * ============================================================================
 */
uint8_t Voxel::GetB() const {
    return (data >> 18) & 0xF; // Get the blue component (4 bits)
}

/* ============================================================================
 * --------------------------- GetType
 * Retrieves the voxel type stored in the least significant 17 bits.
 *
 * ------ Returns ------
 * Integer value representing the voxel type (17 bits).
 * ============================================================================
 */
uint32_t Voxel::GetType() const {
    return data & 0x1FFFF; // Get the type (17 bits)
}

/* ============================================================================
 * --------------------------- Compact
 * Compacts the provided voxel data (vox_data_t struct) into a Voxel object.
 *
 * ------ Parameters ------
 * voxelData: Struct containing the data to be packed into a Voxel object.
 *
 * ------ Returns ------
 * A Voxel object with the provided data compacted.
 * ============================================================================
 */
Voxel Voxel::Compact(const vox_data_t voxelData) {
    Voxel voxel;

    voxel.SetSolid(voxelData.solid);
    voxel.SetTransparency(voxelData.transparency);
    voxel.SetR(voxelData.colour.r);
    voxel.SetG(voxelData.colour.g);
    voxel.SetB(voxelData.colour.b);
    voxel.SetType(voxelData.type);

    return voxel;
}

/* ============================================================================
 * --------------------------- Display
 * Utility function to display the voxel's data values.
 * Displays the voxel's solid state, transparency, color, and type.
 * ============================================================================
 */
void Voxel::Display() const {
    std::cout << "Solid: " << IsSolid() << "\n";
    std::cout << "Transparency: " << IsTransparent() << "\n";
    std::cout << "R: " << static_cast<int>(GetR()) << "\n";
    std::cout << "G: " << static_cast<int>(GetG()) << "\n";
    std::cout << "B: " << static_cast<int>(GetB()) << "\n";
    std::cout << "Type: " << GetType() << "\n";
}

#include "Voxel.h"

/* ============================================================================
 * --------------------------- Voxel
 * Default constructor initializing data to default LRGB (0, 0, 0, 0) and type 0.
 * ============================================================================
 */
Voxel::Voxel() : data(0) {}

/* ============================================================================
 * --------------------------- Voxel
 * Constructor initializing data to a given value.
 * ============================================================================
 */
Voxel::Voxel(const uint32_t data) : data(data) {}

/* ============================================================================
 * --------------------------- Set_L
 * Sets the Light component using an integer.
 *
 * ------ Parameters ------
 * l: The integer value to set for Light (0-15).
 * ============================================================================
 */
void Voxel::Set_L(const int l) {
    data &= ~(L_MASK);
    data |= (l & MASK_4_BIT) << L_SHIFT;
}

/* ============================================================================
 * --------------------------- Set_R
 * Sets the Red component using an integer.
 *
 * ------ Parameters ------
 * r: The integer value to set for Red (0-15).
 * ============================================================================
 */
void Voxel::Set_R(const int r) {
    data &= ~(R_MASK);
    data |= (r & MASK_4_BIT) << R_SHIFT;
}

/* ============================================================================
 * --------------------------- Set_G
 * Sets the Green component using an integer.
 *
 * ------ Parameters ------
 * g: The integer value to set for Green (0-15).
 * ============================================================================
 */
void Voxel::Set_G(const int g) {
    data &= ~(G_MASK);
    data |= (g & MASK_4_BIT) << G_SHIFT;
}

/* ============================================================================
 * --------------------------- Set_B
 * Sets the Blue component using an integer.
 *
 * ------ Parameters ------
 * b: The integer value to set for Blue (0-15).
 * ============================================================================
 */
void Voxel::Set_B(const int b) {
    data &= ~(B_MASK);
    data |= (b & MASK_4_BIT) << B_SHIFT;
}

/* ============================================================================
 * --------------------------- Set_Type
 * Sets the Type field using an integer.
 *
 * ------ Parameters ------
 * type: The integer value to set for Type (0-65535).
 * ============================================================================
 */
void Voxel::Set_Type(const int type) {
    data &= ~(TYPE_MASK);
    data |= (type & TYPE_MASK) << TYPE_SHIFT;
}

/* ============================================================================
 * --------------------------- Get_L
 * Gets the Light component as an integer.
 *
 * Returns the integer value of Light (0-15).
 * ============================================================================
 */
int Voxel::Get_L() const {
    return (data >> L_SHIFT) & MASK_4_BIT;
}

/* ============================================================================
 * --------------------------- Get_R
 * Gets the Red component as an integer.
 *
 * Returns the integer value of Red (0-15).
 * ============================================================================
 */
int Voxel::Get_R() const {
    return (data >> R_SHIFT) & MASK_4_BIT;
}

/* ============================================================================
 * --------------------------- Get_G
 * Gets the Green component as an integer.
 *
 * Returns the integer value of Green (0-15).
 * ============================================================================
 */
int Voxel::Get_G() const {
    return (data >> G_SHIFT) & MASK_4_BIT;
}

/* ============================================================================
 * --------------------------- Get_B
 * Gets the Blue component as an integer.
 *
 * Returns the integer value of Blue (0-15).
 * ============================================================================
 */
int Voxel::Get_B() const {
    return (data >> B_SHIFT) & MASK_4_BIT;
}

/* ============================================================================
 * --------------------------- Get_Type
 * Gets the Type field as an integer.
 *
 * Returns the integer value of Type (0-65535).
 * ============================================================================
 */
int Voxel::Get_Type() const {
    return (data >> TYPE_SHIFT) & TYPE_MASK;
}

/* ============================================================================
 * --------------------------- Compact
 * Compacts LRGB and Type into a single 32-bit unsigned integer.
 *
 * ------ Parameters ------
 * l: The Light component as an integer (0-15).
 * r: The Red component as an integer (0-15).
 * g: The Green component as an integer (0-15).
 * b: The Blue component as an integer (0-15).
 * type: The Type component as an integer (0-65535).
 *
 * Returns a compacted 32-bit value encoding LRGB and Type.
 * ============================================================================
 */
uint32_t Voxel::Compact(
    const int l, const int r, const int g, const int b, const int type
)const{
    uint32_t packed = 0;
    packed |= (l & MASK_4_BIT) << L_SHIFT;
    packed |= (r & MASK_4_BIT) << R_SHIFT;
    packed |= (g & MASK_4_BIT) << G_SHIFT;
    packed |= (b & MASK_4_BIT) << B_SHIFT;
    packed |= (type & TYPE_MASK) << TYPE_SHIFT;
    return packed;
}

/* ============================================================================
 * --------------------------- From_Compact
 * Decompacts a 32-bit unsigned integer into LRGB and Type components.
 *
 * ------ Parameters ------
 * data: The 32-bit packed data to decompact.
 * ============================================================================
 */
void Voxel::From_Compact(const uint32_t packed_data) {
    data = packed_data;
}

/* ============================================================================
 * --------------------------- To_String
 * Creates a readable string based on the voxel
 *
 * ------ Returns ------
 * String
 * ============================================================================
 */
std::string Voxel::To_String(){
    return 
        "R: " + std::to_string(Get_R()) + "\n" +
        "G: " + std::to_string(Get_G()) + "\n" +
        "B: " + std::to_string(Get_B()) + "\n" +
        "L: " + std::to_string(Get_L()) + "\n" +
        "T: " + Voxel_Type_To_String(Get_Type());
}

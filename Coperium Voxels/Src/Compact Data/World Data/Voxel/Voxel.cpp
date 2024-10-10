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

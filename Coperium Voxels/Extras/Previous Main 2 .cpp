#include <iostream>
#include <iomanip> // for std::setprecision
#include <GLFW/glfw3.h>// For GLfloat definition
#include "Test.h"
int main() {
    Block_VD block;

    // Test Set_X, Set_Y, Set_Z with GLfloat input
    block.Set_X(static_cast<GLfloat>(3.5f));  // Expected: sign = 0, mantissa = 3, fraction = 5
    block.Set_Y(static_cast<GLfloat>(-7.5f));  // Expected: sign = 1, mantissa = 7, fraction = 10
    block.Set_Z(static_cast<GLfloat>(0.5f));  // Expected: sign = 0, mantissa = 0, fraction = 31

    std::cout << "Testing GLfloat inputs:\n";
    std::cout << "X = " << block.Get_X() << "\n";
    std::cout << "Y = " << block.Get_Y() << "\n";
    std::cout << "Z = " << block.Get_Z() << "\n";

    // Test Set_X, Set_Y, Set_Z with individual bit components
    block.Set_X(false, 15, 31);  // Maximum positive X
    block.Set_Y(true, 63, 31);   // Maximum negative Y
    block.Set_Z(false, 8, 0);    // Specific value for Z

    std::cout << "\nTesting bitwise inputs:\n";
    std::cout << "X = " << block.Get_X() << " (Expected: 15.96875)\n";
    std::cout << "Y = " << block.Get_Y() << " (Expected: -63.96875)\n";
    std::cout << "Z = " << block.Get_Z() << " (Expected: 8.0)\n";

    // Test conversion to and from GLfloat
    GLfloat glfloat = block.To_GLfloat();
    Block_VD blockFromGL;
    blockFromGL.From_GLfloat(glfloat);

    std::cout << "\nTesting conversion to/from GLfloat:\n";
    std::cout << "GLfloat representation: " << glfloat << "\n";
    std::cout << "X = " << blockFromGL.Get_X() << " (Expected: 15.96875)\n";
    std::cout << "Y = " << blockFromGL.Get_Y() << " (Expected: -63.96875)\n";
    std::cout << "Z = " << blockFromGL.Get_Z() << " (Expected: 8.0)\n";

    // Edge Case Tests
    block.Set_X(true, 0, 0);    // Smallest negative value
    block.Set_Y(false, 0, 31);  // Smallest positive with max fraction
    block.Set_Z(true, 15, 0);   // Maximum negative whole number for Z

    std::cout << "\nTesting edge cases:\n";
    std::cout << "X = " << block.Get_X() << " (Expected: -0.0)\n";
    std::cout << "Y = " << block.Get_Y() << " (Expected: 0.96875)\n";
    std::cout << "Z = " << block.Get_Z() << " (Expected: -15.0)\n";


    block.From_GLfloat(Block_VD::Compact(-0.5f, 0.5f, 0.5f));
    std::cout << "\nTesting Compaction:\n";
    std::cout << "X = " << block.Get_X() << " (Expected: -0.5)\n";
    std::cout << "Y = " << block.Get_Y() << " (Expected:  0.5)\n";
    std::cout << "Z = " << block.Get_Z() << " (Expected:  0.5)\n";
    return 0;
}

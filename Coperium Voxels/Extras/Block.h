#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <GLFW/glfw3.h>
#include <cstdint>
#include <memory>
#include "../Block Mesh.h"
#include <algorithm>

constexpr int MASK_4_BITS = 0xF;
constexpr int MASK_5_BITS = 0x1F;

class Block {
public:
    // Constructor
    Block(uint8_t x = 0, uint8_t y = 0, uint8_t z = 0, uint8_t r = 0, uint8_t g = 0, uint8_t b = 0);

    // Getters
    uint8_t Get_X() const;
    uint8_t Get_Y() const;
    uint8_t Get_Z() const;
    uint8_t Get_R() const;
    uint8_t Get_G() const;
    uint8_t Get_B() const;

    // Setters
    void Set_X(uint8_t x);
    void Set_Y(uint8_t y);
    void Set_Z(uint8_t z);
    void Set_R(uint8_t r);
    void Set_G(uint8_t g);
    void Set_B(uint8_t b);

    // Set all values at once
    void Set_All(uint8_t x, uint8_t y, uint8_t z, uint8_t r, uint8_t g, uint8_t b);

    // Generate cube vertices
    std::unique_ptr<GLfloat[]> Generate_Cube_Vertices() const;

private:
    uint32_t data;
};

#endif // !BLOCK_H
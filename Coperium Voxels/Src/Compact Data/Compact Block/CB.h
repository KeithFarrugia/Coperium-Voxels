#pragma once
#ifndef CMP_BLOCK_H
#define CMP_BLOCK_H

#include <GLFW/glfw3.h>
#include <cstdint>
#include <memory>

#include "../Cube Mesh/CCM.h"
#include "../Cube Mesh/SCM.h"

class CB {
public:
    CB();
    CB( const int x, 
        const int y, 
        const int z, 
        const int r, 
        const int g, 
        const int b);

    // --------------------------------- SETTERS
    void Set_X(const int x);
    void Set_Y(const int y);
    void Set_Z(const int z);
    void Set_R(const int r);
    void Set_G(const int g);
    void Set_B(const int b);

    void Set_All(const int x,
                 const int y, 
                 const int z, 
                 const int r, 
                 const int g, 
                 const int b);

    // --------------------------------- GETTERS
    int Get_X() const;
    int Get_Y() const;
    int Get_Z() const;
    int Get_R() const;
    int Get_G() const;
    int Get_B() const;

    // --------------------------------- GENERATION
    std::unique_ptr<GLfloat[]> Generate_Mesh()const;
    std::unique_ptr<GLfloat[]> Generate_Mesh_Old()const;

private:
    uint32_t data;

    // --------------------------------- MASK VALUES
    static constexpr uint8_t    MASK_4_BIT = 0xF ;
    static constexpr uint8_t    MASK_6_BIT = 0x3F;

    static constexpr uint32_t   X_MASK  = 0xF0000000;
    static constexpr uint32_t   Y_MASK  = 0x0FC00000;
    static constexpr uint32_t   Z_MASK  = 0x003C0000;
    static constexpr uint32_t   R_MASK  = 0x0003C000;
    static constexpr uint32_t   G_MASK  = 0x00003C00;
    static constexpr uint32_t   B_MASK  = 0x000003C0;

    // --------------------------------- SHIFT VALUES
    static constexpr uint8_t    X_SHIFT = 28;
    static constexpr uint8_t    Y_SHIFT = 22;
    static constexpr uint8_t    Z_SHIFT = 18;
    static constexpr uint8_t    R_SHIFT = 14;
    static constexpr uint8_t    G_SHIFT = 10;
    static constexpr uint8_t    B_SHIFT = 6 ;
};

#endif // !CMP_BLOCK_H
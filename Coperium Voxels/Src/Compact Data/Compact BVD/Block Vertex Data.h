#pragma once
#ifndef CUSTOM_32BIT_TYPE_H
#define CUSTOM_32BIT_TYPE_H

#include <GLFW/glfw3.h>
#include <cstring>
#include <cstdint>
#include <cmath>

class Block_VD {
public:
    // Constructor
    Block_VD();

    void    Set_X(float f);
    void    Set_X(const int sign, const uint8_t mantissa, const uint8_t fraction);
    float   Get_X() const;

    void    Set_Y(float f);
    void    Set_Y(const int sign, const uint8_t mantissa, const uint8_t fraction);
    float   Get_Y() const;

    void    Set_Z(float f);
    void    Set_Z(const int sign, const uint8_t mantissa, const uint8_t fraction);
    float   Get_Z() const;

    static GLfloat  Convert (const float x, const float y, const float z);
    static void     Shift   (Block_VD& co_ordinates, 
                             const float x, const float y, const float z);

private:
    GLfloat value;  // 32-bit floating-point storage
    // Helper to access and manipulate the bits
    void     Set_Bits   (const uint32_t bits);
    uint32_t Get_Bits   ()const;
    
    int     X_Sign      ()const;
    uint8_t X_Mantissa  ()const;
    uint8_t X_Fraction  ()const;

    int     Y_Sign      ()const;
    uint8_t Y_Mantissa  ()const;
    uint8_t Y_Fraction  ()const;

    int     Z_Sign      ()const;
    uint8_t Z_Mantissa  ()const;
    uint8_t Z_Fraction  ()const;
};

#endif // CUSTOM_32BIT_TYPE_H

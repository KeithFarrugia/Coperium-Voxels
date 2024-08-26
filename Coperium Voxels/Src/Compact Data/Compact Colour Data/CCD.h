#pragma once
#ifndef CMP_COL_DATA_H
#define CMP_COL_DATA_H

#include <cstdint>
#include <cstring>

class CCD {
public:
    CCD();
    CCD(float data);

    // --------------------------------- Setters
    void    Set_R   (int    r);
    void    Set_G   (int    g);
    void    Set_B   (int    b);
    void    Set_A   (int    a   = 255);

    void    Set_R   (float  r);
    void    Set_G   (float  g);
    void    Set_B   (float  b);
    void    Set_A   (float  a   = 1.0f);

    // --------------------------------- GETTERS
    int     Get_R   () const;
    int     Get_G   () const;
    int     Get_B   () const;
    int     Get_A   () const;

    float   Get_Rf  () const;
    float   Get_Gf  () const;
    float   Get_Bf  () const;
    float   Get_Af  () const;

    // --------------------------------- CONVERSION
    float To_Float  () const;
    void  From_Float(float value);

    // --------------------------------- COMPACTION
    static float Compact(int      r, 
                         int      g, 
                         int      b, 
                         int      a = 255);

    static float Compact(float    r, 
                         float    g, 
                         float    b, 
                         float    a = 1.0f);
    // --------------------------------- SCALING
    void Scale(float    rScale, float   gScale, float   bScale, float   aScale = 1.0f);
    void Scale(int      rScale, int     gScale, int     bScale, int     aScale = 255 );

private:
    uint32_t data;

    // --------------------------------- MASK VALUES
    static constexpr int    MASK_8_BIT  = 0xFF;

    static constexpr uint32_t   R_MASK  = 0xFF000000;
    static constexpr uint32_t   G_MASK  = 0x00FF0000;
    static constexpr uint32_t   B_MASK  = 0x0000FF00;
    static constexpr uint32_t   A_MASK  = 0x000000FF;

    // --------------------------------- SHIFT VALUES
    static constexpr int    R_SHIFT = 24;
    static constexpr int    G_SHIFT = 16;
    static constexpr int    B_SHIFT = 8 ;
    static constexpr int    A_SHIFT = 0 ;
};

#endif // !CMP_COL_DATA_H
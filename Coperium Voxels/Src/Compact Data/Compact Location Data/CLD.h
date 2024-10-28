#pragma once
#ifndef CMP_LOC_DATA_H
#define CMP_LOC_DATA_H

#include <cstring> 
#include <cstdint>
#include <cmath>

class CLD {
public:
    CLD();
    CLD(float val);

    // --------------------------------- X
    void    Set_X ( const float     f);
    void    Set_X ( const bool      sign, 
                    const uint8_t   mantissa, 
                    const uint8_t   fraction);
    float   Get_X ()const;

    // --------------------------------- Y
    void    Set_Y ( const float     f);
    void    Set_Y ( const bool      sign, 
                    const uint8_t   mantissa, 
                    const uint8_t   fraction);
    float   Get_Y ()const;

    // --------------------------------- Z
    void    Set_Z ( const float     f);
    void    Set_Z ( const bool      sign, 
                    const uint8_t   mantissa,
                    const uint8_t   fraction);
    float   Get_Z ()const;

    // --------------------------------- UTILITY
    float   To_Float    ()const;
    void    From_Float  ( const float f);

    void    Shift       ( const float x, 
                          const float y,
                          const float z);

    static float Compact( const float x, 
                          const float y,
                          const float z);

private:
    uint32_t data;

    // --------------------------------- SHIFT VALES
    static constexpr uint8_t    X_S_SHIFT   = 31;
    static constexpr uint8_t    X_M_SHIFT   = 27;
    static constexpr uint8_t    X_F_SHIFT   = 22;
    static constexpr uint8_t    Y_S_SHIFT   = 21;
    static constexpr uint8_t    Y_M_SHIFT   = 15;
    static constexpr uint8_t    Y_F_SHIFT   = 10;
    static constexpr uint8_t    Z_S_SHIFT   = 9 ;
    static constexpr uint8_t    Z_M_SHIFT   = 5 ;
    static constexpr uint8_t    Z_F_SHIFT   = 0 ;

    // --------------------------------- MASK VALUES
    static constexpr uint8_t    MASK_1_BIT  = 0x1   ;
    static constexpr uint8_t    MASK_4_BIT  = 0xF   ;
    static constexpr uint8_t    MASK_5_BIT  = 0x1F  ;
    static constexpr uint8_t    MASK_6_BIT  = 0x3F  ;

    static constexpr uint32_t   X_MASK      = 0xFFC00000;
    static constexpr uint32_t   Y_MASK      = 0x003FFC00;
    static constexpr uint32_t   Z_MASK      = 0x000003FF;

    // --------------------------------- DIVISER
    static constexpr float      DIVISOR     = 32.f; // 2^5

    // --------------------------------- CONVERTERS
    float Combine_To_Float(     const bool      sign,
                                const uint8_t   mantissa,
                                const uint8_t   fraction    ) const;
    void  Decompose_From_Float( const float     f,
                                bool&           sign,
                                uint8_t&        mantissa,
                                uint8_t&        fraction    ) const;

};

#endif // !CMP_LOC_DATA_H
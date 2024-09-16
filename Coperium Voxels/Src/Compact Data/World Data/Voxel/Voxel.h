#pragma once
#ifndef CMP_CUBE_DATA_H
#define CMP_CUBE_DATA_H

#include <cstdint>
#include <string>
#include <iostream>

#include "Voxel_Loc.h"
#include "Voxel_Type_List.h"

class Voxel {
public:
    Voxel();
    Voxel(const uint32_t data);

    // --------------------------------- Setters
    void    Set_L   (const int  l   );
    void    Set_R   (const int  r   );
    void    Set_G   (const int  g   );
    void    Set_B   (const int  b   );
    void    Set_Type(const int  type);

    // --------------------------------- Getters
    int     Get_L   () const;
    int     Get_R   () const;
    int     Get_G   () const;
    int     Get_B   () const;
    int     Get_Type() const;

    // --------------------------------- Compaction and Expansion
    uint32_t Compact(int l, int r, int g, int b, int type) const;
    void     From_Compact(uint32_t data);


    std::string To_String();

private:
    uint32_t data;

    // --------------------------------- MASK VALUES
    static constexpr int        MASK_4_BIT  = 0xF;

    static constexpr uint32_t   L_MASK      = 0xF0000000;
    static constexpr uint32_t   R_MASK      = 0x0F000000;
    static constexpr uint32_t   G_MASK      = 0x00F00000;
    static constexpr uint32_t   B_MASK      = 0x000F0000;

    // --------------------------------- SHIFT VALUES
    static constexpr int    L_SHIFT = 28;
    static constexpr int    R_SHIFT = 24;
    static constexpr int    G_SHIFT = 20;
    static constexpr int    B_SHIFT = 16;

    // --------------------------------- MASK and SHIFT for TYPE (16 bits)
    static constexpr uint32_t TYPE_MASK = 0x0000FFFF;
    static constexpr int      TYPE_SHIFT = 0;
};

// --------------------------------- Hash Specialization
namespace std {
    template <>
    struct hash<Voxel_Loc> {
        std::size_t operator()(const Voxel_Loc& loc) const noexcept {
            // Use the internal 'data' field as the hash
            return std::hash<uint16_t>()(loc.Compact(loc.Get_X(), loc.Get_Y(), loc.Get_Z()));
        }
    };
}

#endif // !CMP_CUBE_DATA_H

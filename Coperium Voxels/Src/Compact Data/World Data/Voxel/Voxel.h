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

    // --------------------------------- Setters (inline implementations)
    inline void Set_L(const int l) {
        data &= ~L_MASK;
        data |= (l & MASK_4_BIT) << L_SHIFT;
    }

    inline void Set_R(const int r) {
        data &= ~R_MASK;
        data |= (r & MASK_4_BIT) << R_SHIFT;
    }

    inline void Set_G(const int g) {
        data &= ~G_MASK;
        data |= (g & MASK_4_BIT) << G_SHIFT;
    }

    inline void Set_B(const int b) {
        data &= ~B_MASK;
        data |= (b & MASK_4_BIT) << B_SHIFT;
    }

    inline void Set_Type(const int type) {
        data &= ~TYPE_MASK;
        data |= (type & TYPE_MASK) << TYPE_SHIFT;
    }

    // --------------------------------- Getters (inline implementations)
    inline int Get_L() const {
        return (data >> L_SHIFT) & MASK_4_BIT;
    }

    inline int Get_R() const {
        return (data >> R_SHIFT) & MASK_4_BIT;
    }

    inline int Get_G() const {
        return (data >> G_SHIFT) & MASK_4_BIT;
    }

    inline int Get_B() const {
        return (data >> B_SHIFT) & MASK_4_BIT;
    }

    inline int Get_Type() const {
        return (data >> TYPE_SHIFT) & TYPE_MASK;
    }

    // --------------------------------- Compaction and Expansion (inline implementation)
    inline uint32_t Compact(int l, int r, int g, int b, int type) const {
        return (l << L_SHIFT) |
            (r << R_SHIFT) |
            (g << G_SHIFT) |
            (b << B_SHIFT) |
            (type << TYPE_SHIFT);
    }

    inline void From_Compact(uint32_t packedData) {
        data = packedData;
    }

    // --------------------------------- To String (inline implementation)
    std::string To_String();

private:
    uint32_t data;

    // --------------------------------- MASK VALUES
    static constexpr int        MASK_4_BIT = 0xF;

    static constexpr uint32_t   L_MASK = 0xF0000000;
    static constexpr uint32_t   R_MASK = 0x0F000000;
    static constexpr uint32_t   G_MASK = 0x00F00000;
    static constexpr uint32_t   B_MASK = 0x000F0000;

    // --------------------------------- SHIFT VALUES
    static constexpr int    L_SHIFT = 28;
    static constexpr int    R_SHIFT = 24;
    static constexpr int    G_SHIFT = 20;
    static constexpr int    B_SHIFT = 16;

    // --------------------------------- MASK and SHIFT for TYPE (16 bits)
    static constexpr uint32_t TYPE_MASK = 0x0000FFFF;
    static constexpr int      TYPE_SHIFT = 0;
};

// --------------------------------- Hash Specialization for Voxel_Loc
namespace std {
    template <>
    struct hash<Voxel_Loc> {
        std::size_t operator()(const Voxel_Loc& loc) const noexcept {
            return std::hash<uint16_t>()(loc.Compact(loc.Get_X(), loc.Get_Y(), loc.Get_Z()));
        }
    };
}

#endif // !CMP_CUBE_DATA_H

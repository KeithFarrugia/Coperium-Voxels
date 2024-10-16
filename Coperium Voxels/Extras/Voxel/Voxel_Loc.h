#pragma once
#ifndef VOXEL_LOCATION_H
#define VOXEL_LOCATION_H

#include <cstdint>


constexpr int VOX_LOC_MAX = 16384;

class Voxel_Loc {
public:
    Voxel_Loc();
    Voxel_Loc(const uint16_t data);

    // --------------------------------- Setters
    void    Set_X(const int    x);
    void    Set_Y(const int    y);
    void    Set_Z(const int    z);

    // --------------------------------- Getters
    int     Get_X() const;
    int     Get_Y() const;
    int     Get_Z() const;

    // --------------------------------- Compaction and Expansion
    static uint16_t Compact(const int x, const int y, const int z);
    void            From_Compact(const uint16_t data);

    // --------------------------------- Comparison Operators
    bool operator==(const Voxel_Loc& other) const;

private:
    uint16_t data;

    // --------------------------------- MASK VALUES
    static constexpr uint16_t X_MASK = 0x3C00;
    static constexpr uint16_t Y_MASK = 0x03F0;
    static constexpr uint16_t Z_MASK = 0x000F;

    // --------------------------------- SHIFT VALUES
    static constexpr int    X_SHIFT = 10;
    static constexpr int    Y_SHIFT = 4;
    static constexpr int    Z_SHIFT = 0;
};

#endif // !VOXEL_LOCATION_H

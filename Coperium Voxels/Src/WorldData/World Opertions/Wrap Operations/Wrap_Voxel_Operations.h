#pragma once
#ifndef WRAPAROUND_HELPERS_H
#define WRAPAROUND_HELPERS_H

#include "../World_Constants.h"


constexpr inline int vox_inc_x(int x) {
    return MIN_ID_V_X + (((x - MIN_ID_V_X) + 1) & MASK_VOXELS_X);
}
constexpr inline int vox_dec_x(int x) {
    return MIN_ID_V_X + (((x - MIN_ID_V_X) - 1) & MASK_VOXELS_X);
}
constexpr inline int vox_inc_y(int y) {
    return MIN_ID_V_Y + (((y - MIN_ID_V_Y) + 1) & MASK_VOXELS_Y);
}
constexpr inline int vox_dec_y(int y) {
    return MIN_ID_V_Y + (((y - MIN_ID_V_Y) - 1) & MASK_VOXELS_Y);
}
constexpr inline int vox_inc_z(int z) {
    return MIN_ID_V_Z + (((z - MIN_ID_V_Z) + 1) & MASK_VOXELS_Z);
}
constexpr inline int vox_dec_z(int z) {
    return MIN_ID_V_Z + (((z - MIN_ID_V_Z) - 1) & MASK_VOXELS_Z);
}

constexpr inline int vox_inc_x(int x, int scale) {
    return MIN_ID_V_X + (((x - MIN_ID_V_X) + scale) & MASK_VOXELS_X);
}
constexpr inline int vox_dec_x(int x, int scale) {
    return MIN_ID_V_X + (((x - MIN_ID_V_X) - scale) & MASK_VOXELS_X);
}
constexpr inline int vox_inc_y(int y, int scale) {
    return MIN_ID_V_Y + (((y - MIN_ID_V_Y) + scale) & MASK_VOXELS_Y);
}
constexpr inline int vox_dec_y(int y, int scale) {
    return MIN_ID_V_Y + (((y - MIN_ID_V_Y) - scale) & MASK_VOXELS_Y);
}
constexpr inline int vox_inc_z(int z, int scale) {
    return MIN_ID_V_Z + (((z - MIN_ID_V_Z) + scale) & MASK_VOXELS_Z);
}
constexpr inline int vox_dec_z(int z, int scale) {
    return MIN_ID_V_Z + (((z - MIN_ID_V_Z) - scale) & MASK_VOXELS_Z);
}

#endif // WRAPAROUND_HELPERS_H
#pragma once
#ifndef VOXEL_TYPE_LIST_H
#define VOXEL_TYPE_LIST_H


typedef enum{
	INVALID,
	AIR,
	NORMAL
}voxel_type_t;


inline std::string Voxel_Type_To_String(int type) {
    voxel_type_t t = static_cast<voxel_type_t>(type);

    switch (t) {
    case voxel_type_t::INVALID:     return "INVALID";
    case voxel_type_t::AIR:         return "AIR";
    case voxel_type_t::NORMAL:      return "NORMAL";
    default:                        return "UNKNOWN";
    }
}


#endif // !VOXEL_TYPE_LIST_H
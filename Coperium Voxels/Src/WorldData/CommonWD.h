#pragma once
#ifndef COMMON_WORLD_DATA
#define COMMON_WORLD_DATA

#include <COIL/DataStructures/IndexedAvlTree/IndexedAvlTree.h>
#include <GLM/glm.hpp>
#include <vector>


#include "../Data Structure/AVL_DataStructure.h"
#include "../Data Structure/UM_DataStructure.h"
#include "World Opertions/World_Constants.h"
#include "World Opertions/Location/World_Loc_Data.h"
#include "World Opertions/Location/World_Loc_Conversion.h"

typedef enum class lod_Level_t : int {
    UNSET   = -1,   NORMAL  =  0,
    LOD_2   =  2,   LOD_4   =  4,
    LOD_8   =  8,   LOD_16  = 16
}lod_Level_t;

constexpr bool operator>=(lod_Level_t lhs, lod_Level_t rhs) {
    return static_cast<int>(lhs) >= static_cast<int>(rhs);
}

// Compare a lod_Level_t with an int.
constexpr bool operator>=(lod_Level_t lhs, int rhs) {
    return static_cast<int>(lhs) >= rhs;
}

// Compare an int with a lod_Level_t.
constexpr bool operator>=(int lhs, lod_Level_t rhs) {
    return lhs >= static_cast<int>(rhs);
}

typedef enum {
    AIR,
    NORMAL
}voxel_type_t;


typedef struct vox_data_t {
    glm::ivec3  position        = glm::ivec3(0);
    glm::ivec3  colour          = glm::ivec3(0);
    int         type            = AIR;
    bool        solid           = false;
    bool        transparency    = false;
    rel_loc_t   rel             = rel_loc_t::WORLD_LOC;
}vox_data_t;


typedef struct chunk_data_t {
    lod_Level_t l_o_d;
    bool        updated;
}chunk_data_t;

typedef struct world_data_t {

}world_data_t;



class World;
class Sector;
class Chunk;
class Voxel;

typedef AvlTreeDataStructure <sector_loc_t, Sector>  sectors_t;
typedef UnorderedMapDataStructure <chunk_loc_t , Chunk >  chunks_t;
typedef std::vector<Voxel>                           voxels_t;

typedef std::pair<chunk_loc_t   &   , Chunk &> chunk_pair_t;
typedef std::pair<sector_loc_t  &   , Sector&> sector_pair_t;

#endif // !COMMON_WORLD_DATA

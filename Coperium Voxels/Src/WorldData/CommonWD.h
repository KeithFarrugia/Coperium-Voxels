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




typedef enum {
    AIR,
    NORMAL
}voxel_type_t;


typedef struct vox_data_t {
    glm::ivec3  position;
    glm::ivec3  colour;
    int         type;
    bool        solid;
    bool        transparency;
    rel_loc_t   rel = rel_loc_t::WORLD_LOC;
}vox_data_t;


class World;
class Sector;
class Chunk;
class Voxel;

typedef AvlTreeDataStructure <sector_loc_t, Sector>  sectors_t;
typedef AvlTreeDataStructure <chunk_loc_t , Chunk >  chunks_t;
typedef std::vector<Voxel>                           voxels_t;

#endif // !COMMON_WORLD_DATA

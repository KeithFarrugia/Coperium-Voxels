#pragma once
#ifndef WORLD_H
#define WORLD_H
#include <COIL/DataStructures/IndexedAvlTree/IndexedAvlTree.h>
#include <GLM/glm.hpp>
#include "../Operations.h"

constexpr int SECTOR_X_MAX = 512;
constexpr int SECTOR_Z_MAX = 512;
constexpr int CHUNK_X_MAX = 16;
constexpr int CHUNK_Y_MAX = 64;
constexpr int CHUNK_Z_MAX = 16;

typedef struct{
    glm::ivec3 position;
    glm::ivec3 colour;
    int        light;
}vox_data_t;

typedef enum {
    WORLD_LOC,
    SECTOR_LOC,
    CHUNK_LOC,
    VOXEL_LOC,
}rel_loc_t;

class Sector;

class World{
public:
    World();
    ~World();

    void Get_Voxel      ();
    void Get_Chunk      ();
    void Get_Sector     ();

    void Create_Voxel   (vox_data_t data);
    void Create_Chunk   ();
    void Create_Sector  ();

    void Remove_Voxel   ();
    void Remove_Chunk   ();
    void Remove_Sector  ();

    glm::ivec3  Convert_Loc    (glm::ivec3 value, rel_loc_t from, rel_loc_t to);

    sector_tree_t Get_All_Sectrs ();

private:
    typedef struct {
        uint32_t location;

        void Set(const glm::ivec2 vec) {
            uint32_t x_sign = (vec.x >> 31) & 0x1;
            uint32_t z_sign = (vec.y >> 31) & 0x1;
            uint32_t abs_x  = (vec.x ^ (-x_sign)) + x_sign;
            uint32_t abs_z  = (vec.y ^ (-z_sign)) + z_sign;

            location =  (x_sign << 31) | (abs_x << 16) |
                        (z_sign << 0)  | (abs_z << 15);
        }
        int X() const {
            int32_t x = (location >> 16) & 0x7FFF;
            int32_t sign = (location >> 31) & 0x1;
            return (x ^ (-sign)) + sign;
        }
        int Z() const {
            int32_t z = (location >> 0) & 0x7FFF;
            int32_t sign = (location >> 15) & 0x1;
            return (z ^ (-sign)) + sign;
        }
        static uint32_t Compact(const glm::ivec2 vec) {
            uint32_t x_sign = (vec.x >> 31) & 0x1;
            uint32_t z_sign = (vec.y >> 31) & 0x1;
            uint32_t abs_x  = (vec.x ^ (-x_sign)) + x_sign;
            uint32_t abs_z  = (vec.y ^ (-z_sign)) + z_sign;

            return  (x_sign << 31) | (abs_x << 16) |
                    (z_sign << 0)  | (abs_z << 15);
        }
    }sector_loc_t;

    typedef Coil::IndexedAvlTree<sector_loc_t, Sector> sector_tree_t;

    sector_tree_t tree;


};

#endif // !WORLD_H


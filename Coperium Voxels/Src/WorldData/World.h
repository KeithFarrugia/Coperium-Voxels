#pragma once
#ifndef WORLD_H
#define WORLD_H
#include "CommonWD.h"


class World{
private:

public:
    World();
    ~World();

    Voxel * Get_Voxel   (glm::ivec3 pos, rel_loc_t rel);
    Chunk * Get_Chunk   (glm::ivec3 pos, rel_loc_t rel);
    Sector* Get_Sector  (glm::ivec3 pos, rel_loc_t rel);

    void Create_Voxel   (vox_data_t data);
    void Create_Chunk   (glm::ivec3 pos, rel_loc_t rel);
    void Create_Sector  (glm::ivec3 pos, rel_loc_t rel);

    void Remove_Voxel   (glm::ivec3 pos, rel_loc_t rel);
    void Remove_Chunk   (glm::ivec3 pos, rel_loc_t rel);
    void Remove_Sector  (glm::ivec3 pos, rel_loc_t rel);

    sectors_t* Get_All_Sectrs ();

private:

    sectors_t sectors;


};


class Sector {
private:

public:
    Sector();
    ~Sector();

    Voxel* Get_Voxel(glm::ivec3 pos, rel_loc_t rel);
    Chunk* Get_Chunk(glm::ivec3 pos, rel_loc_t rel);

    void Create_Voxel(vox_data_t data);
    void Create_Chunk(glm::ivec3 pos, rel_loc_t rel);

    void Remove_Voxel(glm::ivec3 pos, rel_loc_t rel);
    void Remove_Chunk(glm::ivec3 pos, rel_loc_t rel);

    chunks_t* Get_All_Chunks();

private:

    chunks_t chunks;


};


class Chunk {
private:

public:
    Chunk();
    ~Chunk();

    Voxel* Get_Voxel(glm::ivec3 pos, rel_loc_t rel);

    void Create_Voxel(vox_data_t data);

    void Remove_Voxel(glm::ivec3 pos, rel_loc_t rel);

    voxels_t Get_All_Voxels();

private:
    voxels_t voxels;
};


#endif // !WORLD_H


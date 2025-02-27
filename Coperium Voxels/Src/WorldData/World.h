#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <COIL/Mesh/Basic_Mesh.h>
#include "CommonWD.h"


class World{
public:
     World();
     World(const World& other);
    ~World();

    Voxel * Get_Voxel   (glm::ivec3 pos, rel_loc_t rel);
    Chunk * Get_Chunk   (glm::ivec3 pos, rel_loc_t rel);
    Sector* Get_Sector  (glm::ivec3 pos, rel_loc_t rel);

    Sector* Get_Sector  (sector_loc_t id);

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
public:
     Sector();
     Sector(const Sector& other);
    ~Sector();

    Voxel* Get_Voxel(glm::ivec3 pos, rel_loc_t rel);
    Chunk* Get_Chunk(glm::ivec3 pos, rel_loc_t rel);

    Chunk* Get_Chunk(chunk_loc_t id);

    void Create_Voxel(vox_data_t data);
    void Create_Chunk(glm::ivec3 pos, rel_loc_t rel);

    void Remove_Voxel(glm::ivec3 pos, rel_loc_t rel);
    void Remove_Chunk(glm::ivec3 pos, rel_loc_t rel);

    chunks_t* Get_All_Chunks();

private:

    chunks_t chunks;


};


class Chunk {
public:
     Chunk();
     Chunk(const Chunk& other);
    ~Chunk();

    Voxel* Get_Voxel(glm::ivec3 pos, rel_loc_t rel);
    const Voxel* Get_Voxel(glm::ivec3 pos, rel_loc_t rel) const;
    Voxel* Get_Voxel(glm::ivec3 pos);
    const Voxel* Get_Voxel(glm::ivec3 pos)const;

    void Create_Voxel(vox_data_t data);

    void Remove_Voxel(glm::ivec3 pos, rel_loc_t rel);

    voxels_t* Get_All_Voxels();

    void Generate_Mesh(World& w, const chunk_loc_t chunk_id, const sector_loc_t sector_id, const Chunk& generic_chunk);
    void Draw_Mesh();
private:
    Coil::Basic_Mesh mesh;
    voxels_t voxels;
};


class Voxel {
public:
     Voxel();
     Voxel(const Voxel& other);
     Voxel(const vox_data_t voxelData);
    ~Voxel();
    void SetSolid       (bool       s);
    void SetTransparency(bool       t);
    void SetR           (uint8_t    r);
    void SetG           (uint8_t    g);
    void SetB           (uint8_t    b);
    void SetType        (uint32_t   t);

    // Getters
    bool        IsSolid         () const;
    bool        IsAir           () const;
    bool        IsTransparent   () const;
    uint8_t     GetR            () const;
    uint8_t     GetG            () const;
    uint8_t     GetB            () const;
    glm::vec3   GetColour       () const;
    uint32_t    GetType         () const;

    static Voxel Compact(const vox_data_t voxelData);
    void Display() const;

private:
    uint32_t data;

};


#endif // !WORLD_H


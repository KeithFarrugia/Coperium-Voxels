#pragma once
#ifndef SECTOR_H
#define SECTOR_H

#include <unordered_map>

#include "../Chunk/Chunk.h"
#include "../Operations.h"


typedef std::unordered_map<uint32_t, Chunk> chunk_set_t;

constexpr auto SECTOR_X_MAX = 512;
constexpr auto SECTOR_Z_MAX = 512;

class Sector {
public:
    Sector();
    Sector(uint32_t offset);
    
    void    Add_Voxel       (const glm::ivec3   position,
                             const glm::ivec3   colour  ,
                             const int          l       ,
                             const int          type    );
    void    Remove_Voxel    (const glm::ivec3   position);

    void     Create_Chunk   (const int x, const int y, const int z);
    void     Add_Chunk      (const Chunk& chunk);

    void     Remove_Chunk   (const int x, const int y, const int z);

    Voxel    Get_Voxel      (const int x, const int y, const int z);

    chunk_set_t* Get_Chunks();

    Chunk* Get_Chunk_L (const int x, const int y, const int z);
    Chunk* Get_Chunk_S (const int x, const int y, const int z);


    int      Get_Offset_X   () const;
    int      Get_Offset_Z   () const;
    void     Set_Offset     (int x, int z);
    uint32_t Get_Offset     ();

    void     Display();

    static uint32_t     Compact                 (const int x, const int z);
    static glm::ivec3   Convert_Sector_To_Local (const glm::ivec3 sector_pos);
    static glm::ivec3   Convert_Sector_To_Chunk (const glm::ivec3 sector_pos);

private:
    // --------------------------------- MASK VALUES
    static constexpr int MASK_1_BITS    = 0x1;
    static constexpr int MASK_15_BITS   = 0x7FFF;

    // --------------------------------- SHIFT VALUES
    static constexpr int X_M_SHIFT = 16;
    static constexpr int X_S_SHIFT = 31;
    static constexpr int Z_M_SHIFT = 0 ;
    static constexpr int Z_S_SHIFT = 15;

    uint32_t sector_offset;

    chunk_set_t chunks;
};

#endif // !SECTOR_H

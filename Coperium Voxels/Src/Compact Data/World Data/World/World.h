#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>

#include "../Sector/Sector.h"
#include "../Operations.h"


typedef std::unordered_map<uint32_t, Sector> sector_set_t;

class World {
public:
    World();
    ~World();


    void Add_Voxel          (const glm::ivec3   position,
                             const glm::ivec3   colour  ,
                             const int          l       ,
                             const int          type    );

    void Remove_Voxel       (const glm::ivec3   position);

    void Create_Sector      (const int          x       ,
                             const int          z       );

    void Add_Sector         (const Sector&      sector  );

    void Clear_Sectors      ();

    Voxel   Get_Voxel       (const int x, const int y, const int z);
    Sector* Get_Sector_L    (const int x, const int y, const int z);
    Sector* Get_Sector_W    (const int x, const int y, const int z);
    Chunk*  Get_Chunk       (const glm::ivec3   position);

    sector_set_t*   Get_Sectors();

    void Display();

    static glm::ivec3 Convert_World_To_Local(const glm::ivec3 world_pos);
    static glm::ivec3 Convert_World_To_Sector(const glm::ivec3 world_pos);


private:

    sector_set_t sectors;
};

#endif // !WORLD_H

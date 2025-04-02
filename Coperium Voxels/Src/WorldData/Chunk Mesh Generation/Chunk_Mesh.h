#pragma once
#ifndef CHUNK_MESH_GENERATION_H
#define CHUNK_MESH_GENERATION_H

#include "../World.h"
#include <COIL/Camera/Camera.h>
#include "../../Compact Data/Cube Mesh/CCMS.h"
#include <bitset>

typedef enum n_chunk_t {
    LEFT_NEIGH      = 0,
    RIGHT_NEIGH     = 1,
    UP_NEIGH        = 2,
    DOWN_NEIGH      = 3,
    FRONT_NEIGH     = 4,
    BACK_NEIGH      = 5,
    NUM_NEIGHBOURS  = 6,
} n_chunk_t;

typedef enum n_column_t {
    NEIGHBOR    = 0,
    CENTER      = 1,
    NUM_COLUMNS = 2,
}n_column_t;

typedef struct neighbouring_chunks_t {
    Chunk* chunks[NUM_NEIGHBOURS][NUM_COLUMNS];

    neighbouring_chunks_t() {
        for (int i = 0; i < NUM_NEIGHBOURS; i++) {
            for (int j = 0; j < NUM_COLUMNS; j++) {
                chunks[i][j] = nullptr;
            }
        }
    }

    neighbouring_chunks_t(
        const Chunk* left, const Chunk* right, const Chunk* up,
        const Chunk* down, const Chunk* front, const Chunk* back,
        const Chunk* center
    ) {
        chunks[LEFT_NEIGH   ][NEIGHBOR] = const_cast<Chunk*>(left   );
        chunks[RIGHT_NEIGH  ][NEIGHBOR] = const_cast<Chunk*>(right  );
        chunks[UP_NEIGH     ][NEIGHBOR] = const_cast<Chunk*>(up     );
        chunks[DOWN_NEIGH   ][NEIGHBOR] = const_cast<Chunk*>(down   );
        chunks[FRONT_NEIGH  ][NEIGHBOR] = const_cast<Chunk*>(front  );
        chunks[BACK_NEIGH   ][NEIGHBOR] = const_cast<Chunk*>(back   );

        for (int i = 0; i < NUM_NEIGHBOURS; i++) {
            chunks[i][CENTER] = const_cast<Chunk*>(center);
        }
    }

    inline Chunk* Get_Up(int y) const {
        return chunks[UP_NEIGH][static_cast<int>(y < MAX_ID_V_Y)];
    }

    inline Chunk* Get_Down(int y) const {
        return chunks[DOWN_NEIGH][static_cast<int>(y > MIN_ID_V_Y)];
    }

    inline Chunk* Get_Left(int x) const {
        return chunks[LEFT_NEIGH][static_cast<int>(x > MIN_ID_V_X)];
    }

    inline Chunk* Get_Right(int x) const {
        return chunks[RIGHT_NEIGH][static_cast<int>(x < MAX_ID_V_X)];
    }

    inline Chunk* Get_Front(int z) const {
        return chunks[FRONT_NEIGH][static_cast<int>(z < MAX_ID_V_Z)];
    }

    inline Chunk* Get_Back(int z) const {
        return chunks[BACK_NEIGH][static_cast<int>(z > MIN_ID_V_Z)];
    }

} neighbouring_chunks_t;

extern int total_faces_generated;
static inline int Count_Set_Bits(cube_faces_t flags) {
    return static_cast<int>(std::bitset<8>(static_cast<uint8_t>(flags)).count());
}
const neighbouring_chunks_t get_chunk_neighbours(
    World& w, chunk_pair_t chunk, sector_pair_t sector, const Chunk& generic_chunk);

void Generate_Chunk_Mesh(World& w, sector_pair_t sector, chunk_pair_t chunk, const Chunk& generic_chunk);
void Generate_Chunk_Mesh(World& w, sector_pair_t sector, chunk_pair_t chunk, const Chunk& generic_chunk, int l_o_d);

void Generate_Single_Chunk(World& world, sector_pair_t sector_pair, chunk_pair_t chunk_pair, const glm::vec3& camera_pos);
void Generate_All_Chunk_Meshes(World& world, Coil::Camera& camera);
void Generate_All_Chunk_Meshes_LOD_PASS(World& world, Coil::Camera& camera, bool check_mov, int update_interval_ms);


#endif // !CHUNK_MESH_GENERATION_H

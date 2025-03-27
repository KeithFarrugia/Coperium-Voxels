#pragma once
#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include "../WorldData/World.h"
// Computes the neighbour chunk for a given offset (dx, dy, dz)
// relative to the current chunk. Returns generic_chunk if no valid neighbour exists.


typedef struct full_neigh_chunk_t {
    Chunk* neighbor_chunks[3][3][3][2];
    full_neigh_chunk_t() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    for (int n = 0; n < 2; n++) {
                        neighbor_chunks[i][j][k][n] = nullptr;
                    }
                }
            }
        }
    }
    inline Chunk* Get_Neighbour(glm::ivec3 index, glm::ivec3 pos) {
        //printf("%d, %d, %d\n", index.x, index.y, index.z);
        int n_or_c = static_cast<int>(
            pos.x <= MAX_ID_V_X && pos.x >= MIN_ID_V_X &&
            pos.y <= MAX_ID_V_Y && pos.y >= MIN_ID_V_Y &&
            pos.z <= MAX_ID_V_Z && pos.z >= MIN_ID_V_Z
        );
        return neighbor_chunks[index.x][index.y][index.z][n_or_c];
    }
}full_neigh_chunk_t;








const Chunk* Get_Chunk_Neighbour(
    World& w,
    chunk_pair_t chunk,
    sector_pair_t sector,
    const Chunk* generic_chunk,
    int dx, int dy, int dz
) {
    // Get current chunk position
    glm::ivec3 current_pos(chunk.first.X(), chunk.first.Y(), chunk.first.Z());
    glm::ivec3 new_pos = current_pos + glm::ivec3(dx, dy, dz);

    // Start with the current sector
    int sector_x = sector.first.X();
    int sector_z = sector.first.Z();
    int local_x = new_pos.x;
    int local_z = new_pos.z;

    // Handle X-axis transitions
    if (new_pos.x < MIN_ID_C_X) {
        if (sector_x > MIN_ID_S_X) {
            sector_x--; local_x = MAX_ID_C_X;

        } else { return generic_chunk; }

    } else if (new_pos.x > MAX_ID_C_X) {
        if (sector_x < MAX_ID_S_X) {
            sector_x++; local_x = MIN_ID_C_X;

        } else { return generic_chunk; }
    }

    // Handle Z-axis transitions
    if (new_pos.z < MIN_ID_C_Z) {
        if (sector_z > MIN_ID_S_Z) {
            sector_z--; local_z = MAX_ID_C_Z;
        }else { return generic_chunk; }

    } else if (new_pos.z > MAX_ID_C_Z) {
        if (sector_z < MAX_ID_S_Z) {
            sector_z++;
            local_z = MIN_ID_C_Z;

        } else { return generic_chunk; }
    }

    // Handle Y-axis (no sector transitions allowed)
    if (new_pos.y < MIN_ID_C_Y || new_pos.y > MAX_ID_C_Y) {
        return generic_chunk;
    }

    // Get the target sector only once
    Sector* target_sector = &sector.second;
    if (sector_x != sector.first.X() || sector_z != sector.first.Z()) {
        target_sector = w.Get_Sector(sector_loc_t::Compact(glm::ivec2(sector_x, sector_z)));
        if (!target_sector)
            return generic_chunk;
    }

    // Retrieve the chunk
    const Chunk* candidate = target_sector->Get_Chunk(
        chunk_loc_t::Compact(glm::ivec3(local_x, new_pos.y, local_z))
    );
    return candidate ? candidate : generic_chunk;
}








// Computes the full set of neighbour chunks.
// The result is stored in a 3x3x3 array where the center (index [1][1][1]) is the current chunk.
// The indices correspond to offsets: index 0 = -1, 1 = 0, 2 = +1 in each axis.
void Get_Full_Chunk_Neighbours(
    World& w,
    chunk_pair_t chunk,
    sector_pair_t sector,
    const Chunk* generic_chunk,
    full_neigh_chunk_t& neighbour_set
) {
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            for (int dz = -1; dz <= 1; dz++) {
                glm::ivec3 index = glm::ivec3(dx + 1, dy + 1, dz + 1);

                neighbour_set.neighbor_chunks[index.x][index.y][index.z][1] = 
                    &chunk.second;
                neighbour_set.neighbor_chunks[index.x][index.y][index.z][0] = 
                    const_cast<Chunk*>(
                        Get_Chunk_Neighbour(w, chunk, sector, generic_chunk, dx, dy, dz)
                    );
            }
        }
    }
}
constexpr inline glm::ivec3 wrap_voxel_position(const glm::ivec3& pos, const glm::ivec3& offset) {
    int new_x = MIN_ID_V_X + (((pos.x - MIN_ID_V_X) + offset.x) & MASK_VOXELS_X);
    int new_y = MIN_ID_V_Y + (((pos.y - MIN_ID_V_Y) + offset.y) & MASK_VOXELS_Y);
    int new_z = MIN_ID_V_Z + (((pos.z - MIN_ID_V_Z) + offset.z) & MASK_VOXELS_Z);
    return glm::ivec3(new_x, new_y, new_z);
}
// Count alive neighbours for a voxel at local voxel coordinates (x, y, z)
// in the current chunk. Uses the precomputed full neighbour chunk array.
// For voxels near the chunk boundary, we "wrap" the coordinate to the appropriate edge.
// Count alive neighbours for a voxel at local coordinates (x, y, z)
// using the precomputed full neighbour set.
int CountAliveNeighbours(full_neigh_chunk_t& n_set, int x, int y, int z) {
    int alive_count = 0;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            for (int dz = -1; dz <= 1; dz++) {
                if (dx == 0 && dy == 0 && dz == 0) continue;
                glm::ivec3 index = glm::ivec3(dx, dy, dz);
                glm::ivec3 neighbour_pos_w = wrap_voxel_position(glm::ivec3(x, y, z), index);
                glm::ivec3 neighbour_pos_h = glm::ivec3(x, y, z) + index;
                Chunk* target_chunk = n_set.Get_Neighbour(index + glm::ivec3(1), neighbour_pos_h);
                if (!target_chunk) continue;

                const Voxel* neighbour_voxel = target_chunk->Get_Voxel(neighbour_pos_w, rel_loc_t::CHUNK_LOC);
                if (neighbour_voxel && neighbour_voxel->GetR() > 0)
                    alive_count++;
            }
        }
    }
    return alive_count;
}

void UpdateGameOfLife(World& source_world, World& dest_world, Chunk* generic_chunk, bool& toggle) {
    static int callCounter = 0;
    if (callCounter < 1000) {
        callCounter++;
        return;
    }
    callCounter = 0;
    toggle = !toggle;
    sectors_t* sectors = source_world.Get_All_Sectrs();
    if (!sectors) return;

    for (auto sector_pair : *sectors) {
        Sector* dest_sector = dest_world.Get_Sector(sector_pair.first);

        chunks_t* chunks = sector_pair.second.Get_All_Chunks();

        for (auto chunk_pair : *chunks) {
            Chunk* dest_chunk = dest_sector->Get_Chunk(chunk_pair.first);
            full_neigh_chunk_t neighbour_set;
            Get_Full_Chunk_Neighbours(source_world, chunk_pair, sector_pair, generic_chunk, neighbour_set);

            for (int x = 0; x < CHUNK_SIZE_X; x++) {
                for (int y = 0; y < 1; y++) {
                    for (int z = 0; z < CHUNK_SIZE_Z; z++) {
                        glm::ivec3 vox_loc = glm::ivec3(x, y, z);
                        Voxel* src_voxel = chunk_pair.second.Get_Voxel(vox_loc);
                        Voxel* dest_voxel = dest_chunk->Get_Voxel(vox_loc);

                        dest_voxel->SetR(src_voxel->GetR());
                        dest_voxel->SetG(src_voxel->GetG());
                        dest_voxel->SetB(src_voxel->GetB());

                        if (src_voxel->IsAir()) { continue; }


                        int alive_count = CountAliveNeighbours(neighbour_set, x, y, z);

                        if (src_voxel->GetR() > 0) {  // Alive
                            if (alive_count < 2 || alive_count > 3) {
                                dest_voxel->SetR(0); dest_voxel->SetG(0); dest_voxel->SetB(0); // Death
                                dest_chunk->Get_Chunk_Data().updated = true;
                            }
                        }
                        else {  // Dead
                            if (alive_count == 3) {
                                dest_voxel->SetR(15); dest_voxel->SetG(15); dest_voxel->SetB(15); // Birth
                                dest_chunk->Get_Chunk_Data().updated = true;
                            }
                        }
                    }
                }
            }
        }
    }
}
void InitializeGameOfLife(World& world, const std::vector<glm::ivec3>& live_voxel_coords) {
    // First, get all sectors and set all voxels to dead (optional)
    sectors_t* sectors = world.Get_All_Sectrs();
    if (!sectors)
        return;

    // Iterate through all sectors and chunks to set every voxel to "dead" (black)
    for (auto sector_pair : *sectors) {
        chunks_t* chunks = sector_pair.second.Get_All_Chunks();
        if (!chunks)
            continue;
        for (auto chunk_pair : *chunks) {
            for (int x = 0; x < CHUNK_SIZE_X; x++) {
                for (int y = 0; y < CHUNK_SIZE_Y; y++) {
                    for (int z = 0; z < CHUNK_SIZE_Z; z++) {
                        Voxel* voxel = chunk_pair.second.Get_Voxel(glm::ivec3(x, y, z));
                        if (voxel) {
                            voxel->SetR(0);
                            voxel->SetG(0);
                            voxel->SetB(0);
                        }
                    }
                }
            }
        }
    }

    // Now, for each provided world coordinate, find the corresponding voxel and set it to "alive" (white)
    for (const auto& world_coord : live_voxel_coords) {
        glm::ivec3 local_coord;
        Voxel* voxel = world.Get_Voxel(world_coord, rel_loc_t::WORLD_LOC);
        if (voxel) {
            voxel->SetR(15);  // Maximum red component (white)
            voxel->SetG(15);
            voxel->SetB(15);
        }
    }
}
#endif // !GAME_OF_LIFE_H
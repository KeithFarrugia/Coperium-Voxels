#pragma once
#ifndef CHUNK_MANAGEMENT_H
#define CHUNK_MANAGEMENT_H

#include "../World.h"
#include <COIL/Camera/Camera.h>
#include "WorldManager.h"

const std::string WORLD_SAVES_DIR = "World_Saves";

void Store_Chunk(const std::string& world_name, sector_pair_t sector_pair, chunk_pair_t chunk_pair);
bool Read_Chunk(const std::string& world_name, sector_loc_t sector_location, chunk_loc_t chunk_location, Chunk& chunk);

void Set_Neighbours_to_Update(World& world, const glm::ivec3& sector, const glm::ivec3& chunk);

void Load_New_Chunks    (WorldManager& wm,const glm::ivec3& current_sector, const glm::ivec3& current_chunk, void (*create_chunk_func)(Chunk&, glm::ivec3 offset));
void Unload_Far_Chunks  (WorldManager& wm, const glm::ivec3& curr_position);

void Update_Chunks(WorldManager& wm, Coil::Camera& camera);
void Load_All_Chunks (WorldManager& wm);
void Store_All_Chunks(WorldManager& wm);
#endif // !CHUNK_MANAGEMENT_H
#pragma once
#ifndef CHUNK_MANAGEMENT_H
#define CHUNK_MANAGEMENT_H

#include "../World.h"
#include <COIL/Camera/Camera.h>

void Set_Neighbours_to_Update(World& world, const glm::ivec3& sector, const glm::ivec3& chunk);
void LoadNewChunks(World& world, const glm::ivec3& current_sector, const glm::ivec3& current_chunk);
void Unload_Far_Chunks(World& world, const glm::ivec3& curr_position);

void Update_Chunks(World& world, Coil::Camera& camera);
#endif // !CHUNK_MANAGEMENT_H
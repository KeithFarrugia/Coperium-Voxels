#pragma once
#ifndef WORLD_MESH_FUNCTIONS_H
#define WORLD_MESH_FUNCTIONS_H

#include <COIL/Shaders/Shader.h>

#include "World/World.h"
void Re_Generate_Chunk_Mesh(World& w, glm::ivec3 position);

void Generate_All_Chunk_Meshes(World& w);


void Render_Chunk_Meshes(World& w, Coil::Shader& s);



#endif // !WORLD_MESH_FUNCTIONS_H

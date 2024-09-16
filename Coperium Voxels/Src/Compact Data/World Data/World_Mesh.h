#pragma once
#ifndef WORLD_MESH_FUNCTIONS_H
#define WORLD_MESH_FUNCTIONS_H

#include <COIL/Shaders/Shader.h>

#include "World/World.h"

void Generate_Chunk_Meshes(World& w);


void Render_Chunk_Meshes(World& w, Coil::Shader& s);



#endif // !WORLD_MESH_FUNCTIONS_H

#pragma once
#ifndef VOXEL_STUFF_H
#define VOXEL_STUFF_H

#include "WorldData/World.h"
#include <chrono>
#include "WorldData/Create_Generic_Chunks.h"
#include <COIL/Shaders/Shader.h>
#include "WorldData/Chunk Mesh Generation/Chunk Mesh.h"

constexpr int GRID_SIZE_F_X = 16;
constexpr int GRID_SIZE_F_Y = 64;
constexpr int GRID_SIZE_F_Z = 16;

constexpr int GRID_SIZE_S_X = 0;
constexpr int GRID_SIZE_S_Y = 0;
constexpr int GRID_SIZE_S_Z = 0;


void generate_blocks_and_mesh(World& world) {
    Chunk generic_chunk = Chunk();
    Create_Air_Chunk(generic_chunk);


    auto start = std::chrono::high_resolution_clock::now();
    for (int x = GRID_SIZE_S_X; x < GRID_SIZE_F_X; x++) {
        for (int y = GRID_SIZE_S_Y; y < GRID_SIZE_F_Y; y++) {
            for (int z = GRID_SIZE_S_Z; z < GRID_SIZE_F_Z; z++) {
                vox_data_t som = vox_data_t{
                        glm::ivec3(x, y, z),                // position
                        glm::ivec3(x, (int)(y / 4.0f), z),  // color
                        voxel_type_t::NORMAL,               // type
                        true,                               // solid
                        false,                              // transparency
                        rel_loc_t::WORLD_LOC                // Relative
                };
                world.Create_Voxel(som);
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken to create voxels: " << std::fixed << std::setprecision(6)
        << duration.count() << " seconds." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    sectors_t* sectors = world.Get_All_Sectrs();
    for (sector_pair_t sector : *sectors) {
        chunks_t* chunks = sector.second.Get_All_Chunks();
        for (chunk_pair_t chunk_pair : *chunks) {
            Generate_Chunk_Mesh(world, chunk_pair, sector, generic_chunk);
        }
    }
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Time taken to Generate Mesh: " << std::fixed << std::setprecision(6)
        << duration.count() << " seconds." << std::endl;
}


void render_voxels(World& world, Coil::Shader& shader, GLuint vertex_offset) {

    sectors_t* sectors = world.Get_All_Sectrs();
    for (auto sector : *sectors) {
        chunks_t* chunks = sector.second.Get_All_Chunks();
        for (auto pair : *chunks) {

            glm::ivec3 offset = glm::vec3(
                pair.first.X() * CHUNK_SIZE_X + sector.first.X() * SECTR_SIZE_X,
                pair.first.Y() * CHUNK_SIZE_Y,
                pair.first.Z() * CHUNK_SIZE_Z + sector.first.Z() * SECTR_SIZE_Z
            );
            shader.Set_Vec3(vertex_offset, offset);

            pair.second.Draw_Mesh();
        }
    };
}



#endif // !VOXEL_STUFF_H

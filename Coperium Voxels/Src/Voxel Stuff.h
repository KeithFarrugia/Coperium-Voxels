#pragma once
#ifndef VOXEL_STUFF_H
#define VOXEL_STUFF_H

#include "WorldData/World.h"
#include <chrono>
#include "WorldData/Create_Generic_Chunks.h"
#include <COIL/Shaders/Shader.h>
#include "WorldData/Chunk Mesh Generation/Chunk_Mesh.h"
#include <GLM/gtx/norm.hpp>
#include "WorldData/World Opertions/Wrap Operations/Wrap_Chunk_Sector_Operations.h"
#include "WorldData/Chunk_Management/Manage_Chunks.h"

constexpr int GRID_SIZE_F_X = 32;
constexpr int GRID_SIZE_F_Y = 64;
constexpr int GRID_SIZE_F_Z = 16;

constexpr int GRID_SIZE_S_X = 0;
constexpr int GRID_SIZE_S_Y = 0;
constexpr int GRID_SIZE_S_Z = 0;

glm::ivec3 last_position;
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <cstdint>
#include <glm/vec3.hpp> // Include GLM for vector types

// Define a simple structure to hold voxel data
struct Magica_Vox {
    uint8_t x, y, z, colorIndex;
};

struct VoxData {
    int sizeX, sizeY, sizeZ;
    std::vector<Magica_Vox> voxels;
};

VoxData readVoxFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file)
        throw std::runtime_error("Failed to open VOX file.");

    // Read header: magic string and version
    char magic[5] = { 0 };
    file.read(magic, 4);
    if (std::strncmp(magic, "VOX ", 4) != 0)
        throw std::runtime_error("Not a valid VOX file.");

    int version;
    file.read(reinterpret_cast<char*>(&version), sizeof(int));

    VoxData voxData = { 0, 0, 0, {} };

    // Parse chunks (a simplified approach)
    while (file) {
        char chunkId[5] = { 0 };
        file.read(chunkId, 4);
        if (!file) break;

        int chunkSize = 0, childChunkSize = 0;
        file.read(reinterpret_cast<char*>(&chunkSize), sizeof(int));
        file.read(reinterpret_cast<char*>(&childChunkSize), sizeof(int));

        std::string id(chunkId);
        if (id == "SIZE") {
            file.read(reinterpret_cast<char*>(&voxData.sizeX), sizeof(int));
            file.read(reinterpret_cast<char*>(&voxData.sizeY), sizeof(int));
            file.read(reinterpret_cast<char*>(&voxData.sizeZ), sizeof(int));
        }
        else if (id == "XYZI") {
            int numVoxels = 0;
            file.read(reinterpret_cast<char*>(&numVoxels), sizeof(int));
            voxData.voxels.resize(numVoxels);
            file.read(reinterpret_cast<char*>(voxData.voxels.data()), numVoxels * sizeof(Voxel));
        }
        else {
            // Skip any other chunks
            file.seekg(chunkSize, std::ios::cur);
        }
    }
    return voxData;
}

void importVoxelsToWorld(World& world, const VoxData& voxData) {
    for (const auto& voxel : voxData.voxels) {
        vox_data_t som = vox_data_t{
            glm::ivec3(voxel.x, voxel.z, voxel.y),          // position
            glm::ivec3(voxel.x, voxel.z, voxel.y),          // color
            voxel_type_t::NORMAL,                           // type
            true,                                           // solid
            false,                                          // transparency
            rel_loc_t::WORLD_LOC                            // Relative
        };
        world.Create_Voxel(som);
    }
}

void generate_blocks(World& world) {

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
}






void render_voxels(World& world, Coil::Shader& shader, GLuint vertex_offset) {
    auto start_time = std::chrono::high_resolution_clock::now();  // Start timing

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

    auto end_time = std::chrono::high_resolution_clock::now();  // End timing

    // Calculate the duration in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    //std::cout << "render_voxels took " << duration << " ms" << std::endl;
}

#endif // !VOXEL_STUFF_H

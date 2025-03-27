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
constexpr int GRID_SIZE_F_Y = 1;
constexpr int GRID_SIZE_F_Z = 32;

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
                        glm::ivec3(0,0,0),  // color
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






void render_voxels(World& world, Coil::Shader& shader, GLuint vertex_offset, const Coil::Camera& camera) {
    auto start_time = std::chrono::high_resolution_clock::now();

    // Precompute camera values for this frame.
    glm::vec3 camPos = camera.Get_Position();
    glm::vec3 camFront = camera.Get_Front(); // assumed normalized

    // Get all sectors from the world.
    sectors_t* sectors = world.Get_All_Sectrs();
    for (auto sector : *sectors) {
        // (Optional) Sector-level culling could be inserted here if sectors have bounding volumes.

        // Get the chunks for this sector.
        chunks_t* chunks = sector.second.Get_All_Chunks();
        for (auto pair : *chunks) {

            // Compute the world-space offset for this chunk.
            glm::ivec3 offset = glm::ivec3(
                pair.first.X() * CHUNK_SIZE_X + sector.first.X() * SECTR_SIZE_X,
                pair.first.Y() * CHUNK_SIZE_Y,
                pair.first.Z() * CHUNK_SIZE_Z + sector.first.Z() * SECTR_SIZE_Z
            );

            // Compute vector from the camera's position to the chunk.
            glm::vec3 camToChunk = glm::vec3(offset) - camPos;

            // Dot product with the normalized camera front.
            // No need to normalize camToChunk since sign of dot product is sufficient.
            if (glm::dot(camToChunk, camFront) <= 0.0f) {
                continue; // Skip rendering this chunk if it's behind the camera.
            }

            // Otherwise, set the shader uniform and draw the mesh.
            shader.Set_Vec3(vertex_offset, offset);
            pair.second.Draw_Mesh();
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    // Optional: print or log the rendering time.
    // std::cout << "render_voxels took " << duration << " microseconds." << std::endl;
}

const std::vector<glm::ivec3> directions = {
    glm::ivec3(1, 0, 0),
    glm::ivec3(-1, 0, 0),
    glm::ivec3(0, 0, 1),
    glm::ivec3(0, 0, -1)
};

// Global variables
static std::queue<glm::ivec3> cubes;
static bool initialized = false;

// Initializes the animation, called once
void Init_Lightning_Animation() {
    if (!initialized) {
        srand(static_cast<unsigned>(time(0))); // Seed RNG once
        cubes.push(glm::ivec3(0, 0, 0)); // Add initial block
        initialized = true;
    }
}

// Returns a random valid direction avoiding already colored blocks
glm::ivec3 getValidDirection(World& world, glm::ivec3 pos) {
    std::vector<glm::ivec3> validDirections;

    for (const auto& dir : directions) {
        glm::ivec3 newPos = pos + dir;
        Voxel* voxel = world.Get_Voxel(newPos, rel_loc_t::WORLD_LOC);
        if (voxel && voxel->IsAir()) continue; // Skip air blocks

        if (voxel) {
            // Check if voxel is already colored
            if (voxel->GetR() == 3 && voxel->GetG() == 3 && voxel->GetB() == 6)
                continue; // Already part of the trail, ignore
        }

        validDirections.push_back(dir);
    }

    if (validDirections.empty()) return glm::ivec3(0, 0, 0); // No valid move

    return validDirections[rand() % validDirections.size()]; // Pick a random valid direction
}

// Lightning animation function
void Lightning_Animation(WorldManager& wm) {
    static int callCounter = 0;
    callCounter++;

    if (callCounter < 200) return;
    callCounter = 0;

    World& world = wm.Get_World();

    if (!initialized) Init_Lightning_Animation();
    if (cubes.empty()) return;

    glm::ivec3 pos = cubes.front();
    cubes.pop();

    Chunk* chunk = world.Get_Chunk(pos, rel_loc_t::WORLD_LOC);
    if (chunk) {
        Voxel* voxel = chunk->Get_Voxel(Convert_Loc_2_Offset(pos, rel_loc_t::WORLD_LOC, rel_loc_t::CHUNK_LOC));
        if (!voxel->IsAir()) {
            voxel->SetR(3);
            voxel->SetG(3);
            voxel->SetB(6);
            chunk->Get_Chunk_Data().updated = true;
        }
        else {
            return;
        }
    }

    int branchChance = rand() % 100; // Random chance for branching

    int branches = (branchChance < 30) ? 2 : 1; // 30% chance to branch into two directions

    for (int i = 0; i < branches; ++i) {
        glm::ivec3 dir = getValidDirection(world, pos);
        if (dir == glm::ivec3(0, 0, 0)) return; // No valid move

        glm::ivec3 newPos = pos + dir;
        cubes.push(newPos);

        std::cout << "New cube at position: ("
            << newPos.x << ", "
            << newPos.y << ", "
            << newPos.z << ")" << std::endl;
    }
}
#endif // !VOXEL_STUFF_H

#pragma once
#ifndef VOXEL_GENERATION_H
#define VOXEL_GENERATION_H

#include "WorldData/World.h"
#include <chrono>
#include "WorldData/Create_Generic_Chunks.h"
#include <COIL/Shaders/Shader.h>
#include <GLM/gtx/norm.hpp>
#include "WorldData/World Opertions/Wrap Operations/Wrap_Chunk_Sector_Operations.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <cstdint>
#include <glm/vec3.hpp>
#include <random>
#include <cmath> // For std::sin

/* ============================================================================
 * --------------------------- generate_blocks
 * Generates a rectangular block of voxels from start_pos (inclusive) to end_pos (exclusive),
 * with all voxels set to the specified colour.
 *
 * Parameters:
 *   world     - the World instance to add voxels to.
 *   start_pos - 3D start position (inclusive).
 *   end_pos   - 3D end position (exclusive).
 *   colour    - colour vector (RGB).
 * ============================================================================
 */
void generate_blocks(World& world, const glm::ivec3& start_pos, const glm::ivec3& end_pos, glm::ivec3 colour) {
    int count = 0;
    auto start = std::chrono::high_resolution_clock::now();

    for (int x = start_pos.x; x < end_pos.x; x++) {
        for (int y = start_pos.y; y < end_pos.y; y++) {
            for (int z = start_pos.z; z < end_pos.z; z++) {
                vox_data_t som = vox_data_t{
                    glm::ivec3(x, y, z),                // position
                    colour,                             // colour
                    voxel_type_t::NORMAL,               // type
                    true,                              // solid
                    false,                             // transparency
                    rel_loc_t::WORLD_LOC               // relative location
                };
                world.Create_Voxel(som);
                ++count;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken to create [" << count << "] voxels: "
        << duration.count() << " ms" << std::endl;
}

/* ============================================================================
 * --------------------------- generate_blocks_wave
 * Generates a wavy terrain block using two sine waves to create height variations.
 * Voxels are created from start_pos up to the calculated height for each (x,z) column.
 * Colour shade is a greyscale value mapped from voxel height.
 *
 * Parameters:
 *   world     - the World instance to add voxels to.
 *   start_pos - 3D start position (inclusive).
 *   end_pos   - 3D end position (exclusive).
 * ============================================================================
 */
void generate_blocks_wave(World& world, const glm::ivec3& start_pos, const glm::ivec3& end_pos) {
    int count = 0;
    auto start = std::chrono::high_resolution_clock::now();

    float freq1 = 0.1f;
    float freq2 = 0.05f;
    float amp1 = 8.0f;
    float amp2 = 4.0f;

    for (int x = start_pos.x; x < end_pos.x; x++) {
        for (int z = start_pos.z; z < end_pos.z; z++) {
            // Calculate wavy height using sine waves
            float height = std::sin(x * freq1) * amp1 + std::sin(z * freq2) * amp2 + 16.0f;
            int max_y = static_cast<int>(start_pos.y + height);

            for (int y = start_pos.y; y < std::min(max_y, end_pos.y); y++) {
                int shade = static_cast<int>((y / float(end_pos.y)) * 15.0f);
                shade = std::clamp(shade, 0, 15);

                vox_data_t som = vox_data_t{
                    glm::ivec3(x, y, z),              // position
                    glm::ivec3(shade, shade, shade),  // greyscale color
                    voxel_type_t::NORMAL,             // type
                    true,                            // solid
                    false,                           // transparency
                    rel_loc_t::WORLD_LOC             // relative location
                };
                world.Create_Voxel(som);
                ++count;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken to create [" << count << "] voxels: "
        << duration.count() << " ms" << std::endl;
}

/* ============================================================================
 * --------------------------- generate_checkerboard
 * Generates a 3D checkerboard pattern of solid voxels within a fixed-size block (16x64x16).
 * Voxels are white and solid in alternating positions, air otherwise.
 *
 * Parameters:
 *   world - the World instance to add voxels to.
 * ============================================================================
 */
void generate_checkerboard(World& world) {
    constexpr int SIZE_X = 16;
    constexpr int SIZE_Y = 64;
    constexpr int SIZE_Z = 16;

    auto start = std::chrono::high_resolution_clock::now();

    int solid_voxel_count = 0;

    for (int x = 0; x < SIZE_X; ++x) {
        for (int y = 0; y < SIZE_Y; ++y) {
            for (int z = 0; z < SIZE_Z; ++z) {
                bool is_solid = (x + y + z) % 2 == 0;
                if (!is_solid) continue;

                vox_data_t voxel_data = {
                    glm::ivec3(x, y, z),            // position
                    glm::ivec3(255, 255, 255),      // color (white)
                    voxel_type_t::NORMAL,           // type
                    true,                          // solid
                    false,                         // transparency
                    rel_loc_t::WORLD_LOC           // relative location
                };

                world.Create_Voxel(voxel_data);
                ++solid_voxel_count;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Checkerboard voxel generation time: "
        << std::fixed << std::setprecision(6)
        << duration.count() << " seconds.\n"
        << "Solid voxels created: " << solid_voxel_count << std::endl;
}

/* ============================================================================
 * --------------------------- generate_solid_block
 * Generates a solid rectangular block of voxels with a fixed size (16x64x16),
 * all with a light gray colour.
 *
 * Parameters:
 *   world - the World instance to add voxels to.
 * ============================================================================
 */
void generate_solid_block(World& world) {
    constexpr int SIZE_X = 16;
    constexpr int SIZE_Y = 64;
    constexpr int SIZE_Z = 16;

    auto start = std::chrono::high_resolution_clock::now();

    int solid_voxel_count = 0;

    for (int x = 0; x < SIZE_X; ++x) {
        for (int y = 0; y < SIZE_Y; ++y) {
            for (int z = 0; z < SIZE_Z; ++z) {
                vox_data_t voxel_data = {
                    glm::ivec3(x, y, z),           // position
                    glm::ivec3(200, 200, 200),     // color (light gray)
                    voxel_type_t::NORMAL,          // type
                    true,                         // solid
                    false,                        // transparency
                    rel_loc_t::WORLD_LOC          // relative location
                };

                world.Create_Voxel(voxel_data);
                ++solid_voxel_count;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Solid block voxel generation time: "
        << std::fixed << std::setprecision(6)
        << duration.count() << " seconds.\n"
        << "Solid voxels created: " << solid_voxel_count << std::endl;
}

/* ============================================================================
 * --------------------------- generate_random_block
 * Generates a rectangular block of voxels with a fixed size (16x64x16),
 * where each voxel has a probability (solid_chance) to be created as a solid voxel.
 * Voxels have a light blue colour.
 *
 * Parameters:
 *   world        - the World instance to add voxels to.
 *   solid_chance - probability between 0.0 and 1.0 that a voxel is solid.
 * ============================================================================
 */
void generate_random_block(World& world, float solid_chance) {
    constexpr int SIZE_X = 16;
    constexpr int SIZE_Y = 64;
    constexpr int SIZE_Z = 16;

    auto start = std::chrono::high_resolution_clock::now();

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    int solid_voxel_count = 0;

    for (int x = 0; x < SIZE_X; ++x) {
        for (int y = 0; y < SIZE_Y; ++y) {
            for (int z = 0; z < SIZE_Z; ++z) {
                if (dist(rng) > solid_chance) continue;

                vox_data_t voxel_data = {
                    glm::ivec3(x, y, z),           // position
                    glm::ivec3(128, 180, 255),     // color (light blue)
                    voxel_type_t::NORMAL,          // type
                    true,                         // solid
                    false,                        // transparency
                    rel_loc_t::WORLD_LOC          // relative location
                };

                world.Create_Voxel(voxel_data);
                ++solid_voxel_count;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Random voxel generation time: "
        << std::fixed << std::setprecision(6)
        << duration.count() << " seconds.\n"
        << "Solid voxels created: " << solid_voxel_count << std::endl;
}

#endif // VOXEL_GENERATION_H

#pragma once
#ifndef VOXEL_IMPORTER_H
#define VOXEL_IMPORTER_H

//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include <cstdlib>      // std::rand, std::srand
#include <ctime>        // std::time
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <glm/glm.hpp>

#include "WorldData/World.h"

//----------------------------------------------------------------------------//
//                            ENUM: VoxelColorMode                            //
//----------------------------------------------------------------------------//
enum class VoxelColorMode {
    ROYAL_BLUE,
    SKY_BLUE,
    HEIGHT_MAP,
    TERRAIN
};

//----------------------------------------------------------------------------//
//                          CLASS: VoxelImporter                              //
//----------------------------------------------------------------------------//
class VoxelImporter {
public:
    //------------------------------------------------------------------------//
    //                     STATIC INITIALIZER FOR RNG                          //
    //------------------------------------------------------------------------//
    struct Seeder {
        Seeder() { std::srand(static_cast<unsigned>(std::time(nullptr))); }
    };
    static inline Seeder seeder;

    //------------------------------------------------------------------------//
    //                         STATIC COLOR GENERATION                         //
    //------------------------------------------------------------------------//
    static glm::ivec3 GetVoxelColor(VoxelColorMode mode, int y) {
        switch (mode) {
        case VoxelColorMode::ROYAL_BLUE: return GetRoyalBlue();
        case VoxelColorMode::SKY_BLUE:   return GetSkyBlue();
        case VoxelColorMode::HEIGHT_MAP: return GetHeightMapColor(y);
        case VoxelColorMode::TERRAIN:    return GetTerrainColor(y);
        }
        return glm::ivec3(0, 0, 0); // unreachable
    }

    //------------------------------------------------------------------------//
    //                     STATIC FILE LOADING & IMPORT                       //
    //------------------------------------------------------------------------//
    static void LoadAndImport(
        const std::string& filename,
        World& world,
        VoxelColorMode colorMode
    ) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Failed to open voxel file: " + filename);
        }
        printf("Starting Loading\n");
        int x, y, z, count = 0;
        std::string line;

        // Timer setup
        auto lastReport = std::chrono::steady_clock::now();

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            if (ss >> x >> y >> z) {
                glm::ivec3 color = GetVoxelColor(colorMode, y);
                world.Create_Voxel(vox_data_t{
                    glm::ivec3(x, y, z),
                    color,
                    voxel_type_t::NORMAL,
                    true,
                    false,
                    rel_loc_t::WORLD_LOC
                    });
                ++count;
            }

            // Check elapsed time
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastReport).count() >= 1000) {
                std::cout << "Imported " << count << " voxels so far...\n";
                lastReport = now;
            }
        }

        std::cout << "Imported " << count << " voxels in total\n";
    }

private:
    //------------------------------------------------------------------------//
    //                       STATIC COLOR HELPERS                              //
    //------------------------------------------------------------------------//
    static glm::ivec3 GetRoyalBlue() {
        int r = std::clamp(4 + (std::rand() % 3 - 1), 0, 15);
        int g = std::clamp(6 + (std::rand() % 3 - 1), 0, 15);
        int b = std::clamp(14 + (std::rand() % 3 - 1), 0, 15);
        return glm::ivec3(r, g, b);
    }

    static glm::ivec3 GetSkyBlue() {
        int r = std::clamp(6 + (std::rand() % 3 - 1), 0, 15);
        int g = std::clamp(10 + (std::rand() % 3 - 1), 0, 15);
        int b = std::clamp(15 + (std::rand() % 3 - 1), 0, 15);
        return glm::ivec3(r, g, b);
    }

    static glm::ivec3 GetHeightMapColor(int y) {
        if (y >= 64) return glm::ivec3(15, 0, 0);
        if (y >= 32) {
            float f = (y - 32) / 32.0f;
            return glm::ivec3(
                static_cast<int>(f * 15),
                static_cast<int>((1 - f) * 15),
                0
            );
        }
        if (y < 0) return glm::ivec3(0, 0, 15);
        float f = y / 32.0f;
        return glm::ivec3(
            0,
            static_cast<int>(f * 15),
            static_cast<int>((1 - f) * 15)
        );
    }

    static glm::ivec3 GetTerrainColor(int y) {
        if (y < 0) return glm::ivec3(0, 0, 15);
        if (y < 48) {
            float f = y / 48.0f;
            int b = static_cast<int>((1 - f) * 15);
            int g = std::clamp(static_cast<int>(f * 7 + 4 + (std::rand() % 5 - 2)), 0, 15);
            int r = std::clamp(static_cast<int>(f * 3 + (std::rand() % 4 - 2)), 0, 15);
            return glm::ivec3(r, g, b);
        }
        if (y < 56) {
            float f = (y - 48) / 8.0f;
            glm::ivec3 s(3, 11, 0), e(8, 8, 8);
            int off = std::rand() % 5 - 2;
            return glm::ivec3(
                std::clamp(int(s.r * (1 - f) + e.r * f) + off, 0, 15),
                std::clamp(int(s.g * (1 - f) + e.g * f) + off, 0, 15),
                std::clamp(int(s.b * (1 - f) + e.b * f) + off, 0, 15)
            );
        }
        if (y < 80) {
            float f = (y - 56) / 24.0f;
            glm::ivec3 s(8, 8, 8), e(12, 12, 12);
            int off = std::rand() % 5 - 2;
            return glm::ivec3(
                std::clamp(int(s.r * (1 - f) + e.r * f) + off, 0, 15),
                std::clamp(int(s.g * (1 - f) + e.g * f) + off, 0, 15),
                std::clamp(int(s.b * (1 - f) + e.b * f) + off, 0, 15)
            );
        }
        // y >= 80
        int base = 15;
        int off = std::rand() % 3 - 1;
        return glm::ivec3(
            std::clamp(base + off, 0, 15),
            std::clamp(base + off, 0, 15),
            std::clamp(base + off, 0, 15)
        );
    }
};

#endif // VOXEL_IMPORTER_H

#pragma once
#ifndef VOXEL_IMPORTER_H
#define VOXEL_IMPORTER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding random generator
#include <glm/glm.hpp>
#include "WorldData/World.h"

// Enum for different voxel color modes
enum class VoxelColorMode {
    ROYAL_BLUE,
    SKY_BLUE,
    HEIGHT_MAP
};

class VoxelImporter {
public:
    VoxelImporter() {
        std::srand(std::time(0));  // Seed random number generator
    }

    // Function to determine voxel color based on mode
    glm::ivec3 GetVoxelColor(VoxelColorMode mode, int y) {
        switch (mode) {
        case VoxelColorMode::ROYAL_BLUE: {
            int red = std::clamp(4 + (std::rand() % 3 - 1), 0, 15);
            int green = std::clamp(6 + (std::rand() % 3 - 1), 0, 15);
            int blue = std::clamp(14 + (std::rand() % 3 - 1), 0, 15);
            return glm::ivec3(red, green, blue);
        }
        case VoxelColorMode::SKY_BLUE: {
            int red = std::clamp(6 + (std::rand() % 3 - 1), 0, 15);
            int green = std::clamp(10 + (std::rand() % 3 - 1), 0, 15);
            int blue = std::clamp(15 + (std::rand() % 3 - 1), 0, 15);
            return glm::ivec3(red, green, blue);
        }
        case VoxelColorMode::HEIGHT_MAP: {
            if (y >= 64) return glm::ivec3(15, 0, 0);  // Max Crimson Red
            if (y >= 32) {
                // Smoothly transition from green (32) to red (64)
                float factor = (y - 32) / 32.0f;
                int red = static_cast<int>(factor * 15);  // From 0 to 15 (red increases)
                int green = static_cast<int>((1.0f - factor) * 15);  // From 15 to 0 (green decreases)
                return glm::ivec3(red, green, 0);  // Red and Green transition
            }
            if (y < 0) return glm::ivec3(0, 0, 15);  // Max Royal Blue (below 0)
            // Smoothly transition from blue to green
            float factor = y / 32.0f;
            int blue = static_cast<int>((1.0f - factor) * 15);  // From 15 to 0 (blue decreases)
            int green = static_cast<int>(factor * 15);  // From 0 to 15 (green increases)
            return glm::ivec3(0, green, blue);  // Blue and Green transition
        }
        }
        return glm::ivec3(0, 0, 0);  // Default (should never reach here)
    }

    // Load from file and directly import into the world
    void LoadAndImport(const std::string& filename, World& world, VoxelColorMode colorMode) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Failed to open voxel positions file: " + filename);
        }

        int x, y, z;
        std::string line;
        int importedCount = 0;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            if (ss >> x >> y >> z) {
                glm::ivec3 voxelColor = GetVoxelColor(colorMode, y);

                world.Create_Voxel(vox_data_t{
                    glm::ivec3(x, y, z),  // Corrected axis mapping
                    voxelColor,           // Color based on selected mode
                    voxel_type_t::NORMAL, // Default type
                    true,                 // Solid
                    false,                // No transparency
                    rel_loc_t::WORLD_LOC  // World location
                    });

                ++importedCount;
            }
        }

        std::cout << "Imported " << importedCount << " voxels into the world with selected color mode!" << std::endl;
    }
};

#endif // VOXEL_IMPORTER_H

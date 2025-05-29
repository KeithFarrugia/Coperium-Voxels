#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "WorldManager.h"

namespace fs = std::filesystem;

//============================================================================//
//                          Save & Load World Settings                        //
//============================================================================//

/* ============================================================================
 * --------------------------- Save_Settings
 * Serializes the current world_settings_t struct to a binary file under:
 *   World_Saves/<world_name>/settings.bin
 *
 * Creates the necessary directories if they do not exist.
 * ============================================================================ */
void WorldManager::Save_Settings() {

    fs::path worldDir = fs::path(WORLD_SAVES_DIR) / world_name;
    fs::create_directories(worldDir);

    fs::path settingsFile = worldDir / "settings.bin";

    std::ofstream out(settingsFile, std::ios::binary | std::ios::trunc);
    if (!out) {
        std::cerr << "Error: Could not open settings file for writing: "
            << settingsFile << std::endl;
        return;
    }

    out.write(reinterpret_cast<const char*>(&settings), sizeof(settings));
    if (!out) {
        std::cerr << "Error: Failed to write settings to: "
            << settingsFile << std::endl;
    }
    out.close();
}

/* ============================================================================
 * --------------------------- Load_Settings
 * Deserializes world_settings_t from:
 *   World_Saves/<world_name>/settings.bin
 *
 * If the file does not exist or cannot be read, leaves settings at defaults.
 *
 * Returns void.
 * ============================================================================ */
void WorldManager::Load_Settings() {

    fs::path settingsFile =
        fs::path(WORLD_SAVES_DIR) / world_name / "settings.bin";

    if (!fs::exists(settingsFile)) {
        return;
    }

    std::ifstream in(settingsFile, std::ios::binary);
    if (!in) {
        std::cerr << "Error: Could not open settings file for reading: "
            << settingsFile << std::endl;
        return;
    }

    in.read(reinterpret_cast<char*>(&settings), sizeof(settings));
    if (!in) {
        std::cerr << "Error: Failed to read settings from: "
            << settingsFile << std::endl;
    }
    in.close();
}

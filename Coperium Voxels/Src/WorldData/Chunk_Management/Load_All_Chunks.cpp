#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "Manage_Chunks.h"  // Ensure this header declares Read_Chunk, WorldManager, etc.

namespace fs = std::filesystem;

/*
 * Load_All_Chunks
 * Given a world name, this function accesses the world folder,
 * iterates through each sector folder, and for each chunk file found,
 * loads the chunk data and adds it to the appropriate sector in the world.
 *
 * Parameters:
 *   world_name - the name (and folder) of the world.
 *   wm         - the WorldManager instance whose world will be updated.
 */
void Load_All_Chunks(WorldManager& wm) {
    /* ------------------------------------------
     * Finding the world file 
     * ------------------------------------------ */
    fs::path world_folder = fs::path(WORLD_SAVES_DIR) / wm.Get_World_Name();
    if (!fs::exists(world_folder) || !fs::is_directory(world_folder)) {
        std::cerr << "Error: World folder does not exist: " << world_folder << std::endl;
        return;
    }

    World& world = wm.Get_World();

    /* ------------------------------------------
     * Iterating over each sector
     * ------------------------------------------ */
    for (const auto& sector_entry : fs::directory_iterator(world_folder)) {
        if (!sector_entry.is_directory())
            continue;

        /* ------------------------------------------
         * Sector Folder name to Actual location
         * ------------------------------------------ */
        sector_loc_t sector_loc;
        try {
            sector_loc.location = static_cast<uint32_t>(std::stoi(sector_entry.path().filename().string()));

        }catch (const std::exception&) {
            std::cerr
                << "Error: Invalid sector folder name '"
                << sector_entry.path().filename().string()
                << "'. Skipping." << std::endl;
            continue;
        }

        /* ------------------------------------------
         * Creating/Finding Sector in world
         * ------------------------------------------ */
        Sector* sector = world.Get_Sector(sector_loc);
        if (!sector) {
            world.Create_Sector(sector_loc);
            sector = world.Get_Sector(sector_loc);
        }

        /* ------------------------------------------
         * Iterating over each chunk in the Sector
         * Folder
         * ------------------------------------------ */
        for (const auto& file_entry : fs::directory_iterator(sector_entry.path())) {
            if (!file_entry.is_regular_file ()           ) continue;
            if ( file_entry.path().extension() != ".dat" ) continue;

            /* ------------------------------------------
             * Chunk ID from file name
             * ------------------------------------------ */
            chunk_loc_t chunk_loc;
            try {
                chunk_loc.location = static_cast<uint16_t>(std::stoi(file_entry.path().stem().string()));

            }catch (const std::exception&) {
                std::cerr 
                    << "Error: Invalid chunk file name '"
                    << file_entry.path().stem().string() 
                    << "' in sector folder "
                    << std::to_string(sector_loc.location) 
                    << ". Skipping." << std::endl;
                continue;
            }


            /* ------------------------------------------
             * Read Chunk Data
             * ------------------------------------------ */
            Chunk chunk;
            if (Read_Chunk(wm.Get_World_Name(), sector_loc, chunk_loc, chunk)) {
                sector->Add_Chunk(chunk_loc, chunk);
                std::cout << "Loaded chunk from file: "
                    << file_entry.path() << std::endl;
            }
            else {
                std::cerr << "Failed to load chunk from file: "
                    << file_entry.path() << std::endl;
            }
        }
    }
}

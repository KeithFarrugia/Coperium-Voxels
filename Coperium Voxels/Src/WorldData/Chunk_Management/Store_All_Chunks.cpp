#include "WorldManager.h"
#include <filesystem>
#include "Manage_Chunks.h"

void Store_All_Chunks(WorldManager& wm) {
    World& world = wm.Get_World();
    sectors_t* sectors = world.Get_All_Sectrs();

    // Iterate through each sector in the world
    for (auto sector_pair : *sectors) {
        // sector_pair.first is a sector_loc_t, sector_pair.second is a pointer to the Sector
        sector_loc_t sector_loc = sector_pair.first;
        Sector& sector = *(sector_pair.second.get());


        // Get all chunks in this sector
        chunks_t* chunks = sector.Get_All_Chunks();
        // Iterate through each chunk in the sector
        for (const auto& chunk_pair : *chunks) {
            // chunk_pair.first is a chunk_loc_t, chunk_pair.second is the corresponding Chunk
            Store_Chunk(wm.Get_World_Name(), sector_pair, chunk_pair);
            std::cout << "Stored chunk (ID: "
                << chunk_pair.first.location
                << ") in sector "
                << sector_loc.location << std::endl;
        }
    }
}
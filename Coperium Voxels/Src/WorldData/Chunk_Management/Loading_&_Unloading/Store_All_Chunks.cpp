#include "../WorldManager.h"
#include <filesystem>

void WorldManager::Store_All_Chunks() {
    sectors_t* sectors = world.Get_All_Sectrs();

    for (auto sector_pair : *sectors) {
        sector_loc_t sector_loc = sector_pair.first;
        Sector& sector = *(sector_pair.second.get());


        chunks_t* chunks = sector.Get_All_Chunks();
        for (const auto& chunk_pair : *chunks) {
            Store_Chunk(sector_pair, chunk_pair);
            std::cout << "Stored chunk (ID: "
                << chunk_pair.first.location
                << ") in sector "
                << sector_loc.location << std::endl;
        }
    }
}
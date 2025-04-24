// Randomly_Delete_Chunk.cpp
#include "Manage_Chunks.h"         // for Store_Chunk, Unload_Chunk, Set_Neighbours_to_Update
#include <random>
#include <chrono>
#include <vector>
#include <utility>
#include <iostream>

void Unload_Chunk(const sector_loc_t& sector_pair, const chunk_loc_t& chunk_pair) {
    // Your chunk-unloading logic (e.g., saving data and releasing resources)
    std::cout << "Unloading chunk at "
        << "Sector(" << sector_pair.X() << ", " << sector_pair.Z() << ")"
        << "Chunk(" << chunk_pair.X() << ", " << chunk_pair.Y() << ", " << chunk_pair.Z() << ")\n";
}

void Randomly_Delete_Chunk(WorldManager& wm) {
    auto& world = wm.Get_World();
    auto* sectors = world.Get_All_Sectrs();  // assume this returns a std::map<sector_loc_t, Sector>*

    // 1) Gather all existing (sector,chunk) keys
    std::vector<std::pair<sector_loc_t, chunk_loc_t>> all_chunks;
    for (auto sector_pair : *sectors) {
        sector_loc_t sector_loc = sector_pair.first;
        auto* chunks = sector_pair.second.get()->Get_All_Chunks(); // map<chunk_loc_t,Chunk>*
        for (auto chunk_pair : *chunks) {
            all_chunks.emplace_back(sector_loc, chunk_pair.first);
        }
    }
    if (all_chunks.empty()) return;

    // 2) Pick one at random
    static std::mt19937_64 rng(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()
    );
    std::uniform_int_distribution<size_t> dist(0, all_chunks.size() - 1);
    auto const& [sector_loc, chunk_loc] = all_chunks[dist(rng)];

    // 3) Persist & unload
    //Store_Chunk(wm.Get_World_Name(), sector_loc, chunk_loc);
    Unload_Chunk(sector_loc, chunk_loc);

    // 4) Remove from in-memory and flag neighbours
    Sector* sector = world.Get_Sector(sector_loc);
    sector->Remove_Chunk(
        glm::ivec3(chunk_loc.X(), chunk_loc.Y(), chunk_loc.Z()),
        rel_loc_t::CHUNK_LOC
    );
    /*Set_Neighbours_to_Update(
        world,
        glm::ivec3(sector_loc.X(), 0, sector_loc.Z()),
        glm::ivec3(chunk_loc.X(), chunk_loc.Y(), chunk_loc.Z())
    );*/

    std::cout << "Deleted chunk at Sector("
        << sector_loc.X() << "," << sector_loc.Z()
        << ") Chunk(" << chunk_loc.X()
        << "," << chunk_loc.Y()
        << "," << chunk_loc.Z() << ")\n";
}

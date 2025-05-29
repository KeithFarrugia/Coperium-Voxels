#include "../WorldManager.h"
#include <random>
#include <chrono>
#include <vector>
#include <utility>
#include <iostream>

void WorldManager::Randomly_Delete_Chunk() {
    auto* sectors = world.Get_All_Sectrs();

    // 1) Gather all (sector, chunk) pairs
    std::vector<std::pair<sector_pair_t, chunk_pair_t>> all_chunks;
    for (auto sector_entry : *sectors) {
        Sector* sector = sector_entry.second.get();
        chunks_t* chunks = sector->Get_All_Chunks();

        for (chunk_pair_t chunk_entry : *chunks) {
            all_chunks.emplace_back(
                std::make_pair(sector_entry, chunk_entry)
            );
        }
    }

    if (all_chunks.empty()) return;

    static std::mt19937_64 rng(
        std::chrono::high_resolution_clock::now().time_since_epoch().count()
    );
    std::uniform_int_distribution<size_t> dist(0, all_chunks.size() - 1);
    auto& [sector_pair, chunk_pair] = all_chunks[dist(rng)];

    Unload_Chunk(sector_pair, chunk_pair);
}

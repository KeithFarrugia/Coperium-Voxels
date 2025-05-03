#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "../WorldManager.h"

namespace fs = std::filesystem;

/* ============================================================================
 * --------------------------- Store_Chunk
 * Serializes and saves a chunk to a file in the
 * appropriate directory structure.
 *
 * ------ Parameters ------
 * world_name   : The name of the world where the chunk belongs.
 * sector_pair  : A pair containing the sector ID and sector reference.
 * chunk_pair   : A pair containing the chunk ID and chunk reference.
 * ============================================================================
 */
void WorldManager::Store_Chunk(
    sector_pair_t   sector_pair,
    chunk_pair_t    chunk_pair
) {
    sector_loc_t sector_id = sector_pair.first;
    chunk_loc_t chunk_id = chunk_pair.first;
    Chunk& chunk = *(chunk_pair.second.get());

    fs::path sector_path =
        fs::path(WORLD_SAVES_DIR) /
        world_name /
        std::to_string(
            sector_id.location
        );

    fs::create_directories(sector_path);

    fs::path chunk_file =
        sector_path /
        (
            std::to_string(
                chunk_id.location
            )
            + ".dat"
            );


    std::ofstream out(
        chunk_file,
        std::ios::binary | std::ios::trunc
    );

    if (!out) {
        std::cerr
            << "Error: Could not open file for writing: "
            << chunk_file
            << std::endl;
        return;
    }

    chunk.serialize(out);
    out.close();
}

/* ============================================================================
 * --------------------------- Read_Chunk
 * Loads a chunk from a file and deserializes it into the chunk object.
 *
 * ------ Parameters ------
 * world_name       : The name of the world where the chunk belongs.
 * sector_location  : The encoded sector location.
 * chunk_location   : The encoded chunk location.
 * chunk            : The chunk object to populate with deserialized data.
 *
 * ------ Returns ------
 * bool             : True if the chunk was successfully
 *                    loaded, false otherwise.
 * ============================================================================
 */
bool WorldManager::Read_Chunk(
    sector_loc_t    sector_location,
    chunk_loc_t     chunk_location,
    Chunk& chunk
) {
    fs::path chunk_file =
        fs::path(WORLD_SAVES_DIR) / world_name /
        std::to_string(sector_location.location) /
        (std::to_string(chunk_location.location) + ".dat");

    if (!fs::exists(chunk_file)) {
        std::cerr
            << "Error: Chunk file does not exist: "
            << chunk_file << std::endl;
        return false;
    }

    std::ifstream in(chunk_file, std::ios::binary);
    if (!in) {
        std::cerr
            << "Error: Could not open file for reading: "
            << chunk_file << std::endl;
        return false;
    }

    chunk.deserialize(in);
    in.close();
    return true;
}

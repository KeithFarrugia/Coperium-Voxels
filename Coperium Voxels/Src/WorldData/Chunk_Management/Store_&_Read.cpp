#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "Manage_Chunks.h"

namespace fs = std::filesystem;

// Define the base directory for all world saves.

/* ============================================================================
 * --------------------------- Store_Chunk
 * Serializes and saves a chunk to a file in the appropriate directory structure.
 *
 * ------ Parameters ------
 * world_name: The name of the world where the chunk belongs.
 * sector_pair: A pair containing the sector ID and sector reference.
 * chunk_pair: A pair containing the chunk ID and chunk reference.
 *
 * ------ Operation ------
 * - Constructs the folder path as "World_Saves/world_name/sector_id/".
 * - Ensures the directory exists.
 * - Saves the chunk data as a binary file named "chunk_id.dat".
 * - If the file exists, it is overwritten with new data.
 * ============================================================================
 */
void Store_Chunk(const std::string& world_name, sector_pair_t sector_pair, chunk_pair_t chunk_pair) {
    sector_loc_t sector_id = sector_pair.first;
    chunk_loc_t chunk_id = chunk_pair.first;
    Chunk& chunk = *(chunk_pair.second.get());

    // Construct the directory path: World_Saves/world_name/sector_id/
    fs::path sector_path = fs::path(WORLD_SAVES_DIR) / world_name / std::to_string(sector_id.location);
    fs::create_directories(sector_path); // Ensure directory exists

    // Construct the chunk file path: .../chunk_id.dat
    fs::path chunk_file = sector_path / (std::to_string(chunk_id.location) + ".dat");

    // Open file in binary mode and write chunk data
    std::ofstream out(chunk_file, std::ios::binary | std::ios::trunc);
    if (!out) {
        std::cerr << "Error: Could not open file for writing: " << chunk_file << std::endl;
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
 * world_name: The name of the world where the chunk belongs.
 * sector_location: The encoded sector location.
 * chunk_location: The encoded chunk location.
 * chunk: The chunk object to populate with deserialized data.
 *
 * ------ Returns ------
 * bool: True if the chunk was successfully loaded, false otherwise.
 *
 * ------ Operation ------
 * - Constructs the expected file path "World_Saves/world_name/sector_id/chunk_id.dat".
 * - If the file exists, reads the chunk data.
 * - Deserializes the chunk from the binary file.
 * - Returns true if successful, otherwise false.
 * ============================================================================
 */
bool Read_Chunk(
    const std::string& world_name,
    sector_loc_t sector_location,
    chunk_loc_t chunk_location,
    Chunk& chunk
) {
    // Construct the chunk file path: World_Saves/world_name/sector_id/chunk_id.dat
    fs::path chunk_file = fs::path(WORLD_SAVES_DIR) / world_name /
        std::to_string(sector_location.location) /
        (std::to_string(chunk_location.location) + ".dat");

    // Check if the file exists
    if (!fs::exists(chunk_file)) {
        std::cerr << "Error: Chunk file does not exist: " << chunk_file << std::endl;
        return false;
    }

    // Open file in binary mode and read chunk data
    std::ifstream in(chunk_file, std::ios::binary);
    if (!in) {
        std::cerr << "Error: Could not open file for reading: " << chunk_file << std::endl;
        return false;
    }

    chunk.deserialize(in);
    in.close();
    return true;
}

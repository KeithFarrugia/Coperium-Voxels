
#include "Manage_Chunks.h"
#include "../World Opertions/Wrap Operations/Wrap_Chunk_Sector_Operations.h"
#include "../Create_Generic_Chunks.h"

constexpr int load_radius = 1;

void Load_Chunk(World& world, const glm::ivec3& sectorPos, const glm::ivec3& chunkPos) {
    // Retrieve or create the sector
    Sector* sector = world.Get_Sector(sectorPos, rel_loc_t::SECTOR_LOC);
    if (!sector) {
        world.Create_Sector(sectorPos, rel_loc_t::SECTOR_LOC);
        sector = world.Get_Sector(sectorPos, rel_loc_t::SECTOR_LOC);
    }

    // Create a new chunk
    Chunk newChunk;
    Create_Solid_Chunk(newChunk);

    // Add the chunk to the sector
    sector->Add_Chunk(chunkPos, newChunk);

    Set_Neighbours_to_Update(world, sectorPos, chunkPos);

    std::cout << "Loaded chunk at Sector(" << sectorPos.x << ", " << sectorPos.z
        << ") Chunk(" << chunkPos.x << ", " << chunkPos.y << ", " << chunkPos.z << ")\n";
}


void LoadNewChunks(World& world, const glm::ivec3& current_sector, const glm::ivec3& current_chunk) {
    glm::ivec3 sector_new = glm::ivec3(0), chunk_new = glm::ivec3(0);

    for (int dx = -load_radius; dx <= load_radius; ++dx) {
        for (int dz = -load_radius; dz <= load_radius; ++dz) {
            if (dx == 0 && dz == 0)
                continue;

            wrap_chunk_sec_x(current_sector.x, current_chunk.x, dx, sector_new.x, chunk_new.x);
            wrap_chunk_sec_z(current_sector.z, current_chunk.z, dz, sector_new.z, chunk_new.z);

            Sector* sector = world.Get_Sector(sector_new, rel_loc_t::SECTOR_LOC);
            bool columnExists = false;
            if (sector) {
                auto* chunks = sector->Get_All_Chunks();
                for (auto chunkPair : *chunks) {
                    if (
                        chunkPair.first.X() == chunk_new.x && 
                        chunkPair.first.Z() == chunk_new.z
                    ) {
                        columnExists = true;
                        break;
                    }
                }
            }

            if (!columnExists) {
                if (!sector) {
                    world.Create_Sector(sector_new, rel_loc_t::SECTOR_LOC);
                    sector = world.Get_Sector(sector_new, rel_loc_t::SECTOR_LOC);
                }
                Load_Chunk(world, sector_new, chunk_new);
            }
        }
    }
}

#include "WorldManager.h"
#include "../World Opertions/Wrap Operations/Wrap_Chunk_Sector_Operations.h"

struct Offset { int dx, dy, dz; };
const Offset offsets[] = {
    { -1,  0,  0 }, // Left
    {  1,  0,  0 }, // Right
    {  0, -1,  0 }, // Below
    {  0,  1,  0 }, // Above
    {  0,  0, -1 }, // Back
    {  0,  0,  1 }  // Front
};

/* ============================================================================
 * --------------------------- Set_Neighbours_to_Update
 * Marks the given base chunk and its direct neighbours (left, right, above,
 * below, front, and back) as updated.
 * 
 * ------ Parameters ------
 * world:   The world object managing sectors and chunks.
 * sector:  The sector coordinates (ivec3) for the base chunk.
 * chunk:   The chunk coordinates (ivec3) within the sector for the base chunk.
 * ============================================================================
 */
void WorldManager::Set_Neighbours_to_Update(
    const glm::ivec3& sector, const glm::ivec3& chunk
) {
    if (
        Sector* curr_sector =
        world.Get_Sector(sector, rel_loc_t::SECTOR_LOC)
        ) {
        if (
            Chunk* curr_chunk =
            curr_sector->Get_Chunk(chunk, rel_loc_t::CHUNK_LOC)
            ) {
            curr_chunk->Get_Chunk_Data().updated = true;
        }
    }

    for (auto off : offsets) {
        glm::ivec3
            n_sector_pos = glm::ivec3(0),
            n_chunk_pos = glm::ivec3(0);

        wrap_chunk_sec_x(
            sector.x, chunk.x, off.dx, n_sector_pos.x, n_chunk_pos.x
        );
        wrap_chunk_sec_y(
            sector.y, chunk.y, off.dy, n_sector_pos.y, n_chunk_pos.y
        );
        wrap_chunk_sec_z(
            sector.z, chunk.z, off.dz, n_sector_pos.z, n_chunk_pos.z
        );

        if (
            Sector* n_sector =
            world.Get_Sector(n_sector_pos, rel_loc_t::SECTOR_LOC)
            ) {
            if (
                Chunk* n_chunk =
                n_sector->Get_Chunk(n_chunk_pos, rel_loc_t::CHUNK_LOC)
                ) {
                n_chunk->Get_Chunk_Data().updated = true;
            }
        }
    }
}

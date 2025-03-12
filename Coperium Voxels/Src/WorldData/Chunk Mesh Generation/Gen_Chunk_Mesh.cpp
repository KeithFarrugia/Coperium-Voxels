#include "Chunk_Mesh.h"
#include "Calc_LOD.h"
#include "../Create_Generic_Chunks.h"

glm::ivec3 last_pos;
Chunk generic_c = Create_Air_Chunk();


/* ============================================================================
 * --------------------------- Generate_Single_Chunk
 * Generates or updates the mesh of a single chunk based on its LOD.
 *
 * ------ Parameters ------
 * world:       The game world containing all sectors and chunks.
 * sector_id:   The sector ID where the chunk is located.
 * chunk_id:    The chunk ID within the sector.
 * camera_pos:  The camera position for LOD calculation.
 * generic_chunk: A reference chunk used for mesh generation.
 * ============================================================================
 */
void Generate_Single_Chunk(
    World&              world      ,
    sector_pair_t       sector_pair,
    chunk_pair_t        chunk_pair ,
    const glm::vec3&    camera_pos
) {

    lod_Level_t new_lod = Compute_LOD(
        sector_pair.first, chunk_pair.first, camera_pos
    );
    if (
        chunk_pair.second.Get_Chunk_Data().l_o_d  != new_lod || 
        chunk_pair.second.Get_Chunk_Data().updated
    ){
        if (new_lod == lod_Level_t::NORMAL) {
            Generate_Chunk_Mesh(world, sector_pair, chunk_pair, generic_c);

        }else {
            Generate_Chunk_Mesh(world, sector_pair, chunk_pair, generic_c, static_cast<int>(new_lod));
        }
    }

    // Update chunk LOD
    chunk_pair.second.Get_Chunk_Data().l_o_d    = new_lod;
    chunk_pair.second.Get_Chunk_Data().updated  = false;
}




void Generate_All_Chunk_Meshes(World& world, Coil::Camera& camera) {
    const glm::vec3 camera_pos = camera.Get_Position();
    const glm::ivec3 curr_position(
        glm::round(camera_pos.x),
        glm::round(camera_pos.y),
        glm::round(camera_pos.z)
    );

    if (curr_position == last_pos) { return; }
    last_pos = curr_position;

    // Iterate over all sectors and chunks
    sectors_t* sectors = world.Get_All_Sectrs();
    for (sector_pair_t sector_pair : *sectors) {
        chunks_t* chunks = sector_pair.second.Get_All_Chunks();
        for (chunk_pair_t chunk_pair : *chunks) {
            Generate_Single_Chunk(
                world, 
                sector_pair, chunk_pair, 
                camera_pos
            );
        }
    }
}
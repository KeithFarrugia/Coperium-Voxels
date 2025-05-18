#pragma once
#ifndef World_Creation_Functions_H
#define World_Creation_Functions_H

#include "WorldData/Chunk_Management/WorldManager.h"
#include "WorldData/Create_Generic_Chunks.h"
#include "VoxelModel_Loader.h"

void Load_World_From_text(WorldManager& wm) {
    VoxelImporter::LoadAndImport(wm.Get_World_Name() + ".txt", wm.Get_World(), VoxelColorMode::HEIGHT_MAP);
}

void CheckerBoard(WorldManager& wm) {
    generate_checkerboard(wm.Get_World());
}

void WaveWorld(WorldManager& wm) {
    generate_blocks_wave(wm.Get_World(),glm::ivec3(-512, 0, -512), glm::ivec3(512, 64, 512));
}

void Create_Static_Model_World(WorldManager& world) {
    world.Load_Settings();

    // 3) Get a reference to the settings struct
    world_settings_t& s = world.Get_Settings();

    //=== World Loading & Storage ===
    s.mass_load = false;   // load entire world on start
    s.auto_load = false;   // auto load chunks when needed
    s.auto_unload = false;   // auto unload far chunks
    s.allow_load_from_file = false;   // allow loading chunks from disk
    s.allow_chunk_generation = false;   // allow procedural chunk creation
    s.allow_chunk_store = false;   // allow saving chunks to disk

    //=== Rendering & Mesh Updates ===
    s.render_world = true;    // draw the world
    s.mesh_changes = true;    // allow mesh regeneration
    s.update_interval_ms = 250;     // update meshes every 250 ms

    //=== Level of Detail (LOD) ===
    s.use_lod = false;   // enable LOD system
    s.dynamic_lod = true;   // compute LOD only once
    s.smart_update = true;    // skip LOD if camera is still


    Create_Air_Chunk(s.generic_chunk);  // default prototype chunk

    //=== Debug & Development ===
    s.smart_render = false;   // only draw visible chunks
    s.debug = false;    // enable debug logging

    world.Set_Initialise_Callback(Load_World_From_text);

    // 5) Continue with your initialization
    //for (int i = 0; i < 100; i++) {
        world.Initialise();
    //}

}


#endif // !World_Creation_Functions_H
#pragma once
#ifndef WORLD_CREATION_FUNCTIONS_H
#define WORLD_CREATION_FUNCTIONS_H

#include "WorldData/Chunk_Management/WorldManager.h"
#include "WorldData/Create_Generic_Chunks.h"
#include "VoxelModel_Loader.h"
#include "Voxel_Gen_Util_Func.h"
#include "Animation Stuff/Game_of_Life.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>

/* ============================================================================
 * --------------------------- Load_World_From_Heightmap
 * Loads a voxel model from a text file using height-map colour mapping.
 * Suitable for terrain or mountain models.
 * ============================================================================ */
inline void Load_World_From_Heightmap(WorldManager& wm) {
    VoxelImporter::LoadAndImport(
        wm.Get_World_Name() + ".txt",
        wm.Get_World(),
        VoxelColorMode::HEIGHT_MAP
    );
}

/* ============================================================================
 * --------------------------- Load_World_From_Terrain
 * Loads a voxel model from a text file using terrain-specific colour mapping.
 * Alternative mode for terrain or mountain models.
 * ============================================================================ */
inline void Load_World_From_Terrain(WorldManager& wm) {
    VoxelImporter::LoadAndImport(
        wm.Get_World_Name() + ".txt",
        wm.Get_World(),
        VoxelColorMode::TERRAIN
    );
}

/* ============================================================================
 * --------------------------- Load_World_From_Sky_Blue
 * Loads a voxel model from a text file using sky-blue colour mapping.
 * Suitable for models like Sponza or similar.
 * ============================================================================ */
inline void Load_World_From_Sky_Blue(WorldManager& wm) {
    VoxelImporter::LoadAndImport(
        wm.Get_World_Name() + ".txt",
        wm.Get_World(),
        VoxelColorMode::SKY_BLUE
    );
}


/* ============================================================================
 * --------------------------- CheckerBoard
 * Generates a checkerboard voxel pattern for visual testing.
 * ============================================================================ */
inline void CheckerBoard(WorldManager& wm) {
    generate_checkerboard(wm.Get_World());
}

/* ============================================================================
 * --------------------------- WaveWorld
 * Generates a wave-like landscape pattern using procedural generation.
 * ============================================================================ */
inline void WaveWorld(WorldManager& wm) {
    generate_blocks_wave(
        wm.Get_World(),
        glm::ivec3(-512, 0, -512),
        glm::ivec3(512, 64, 512)
    );
}

/* ============================================================================
 * --------------------------- FlatWorld
 * Fills a flat solid world from coordinates [-val, 0, -val] to [val, 1, val].
 * ============================================================================ */
inline void FlatWorld(WorldManager& wm) {
    constexpr int val = 128;
    generate_blocks(
        wm.Get_World(),
        glm::ivec3(-val, 0, -val),
        glm::ivec3(val, 1, val),
        glm::ivec3(0, 0, 0)
    );
}

/* ============================================================================
 * --------------------------- Create_Static_Model_World
 * Initialises world settings for static model usage, disables procedural
 * generation, enables loading from disk, and sets an import callback.
 * ============================================================================ */
inline void Create_Static_Model_World(WorldManager& world) {
    world.Load_Settings();
    world_settings_t& s = world.Get_Settings();

    // === World Loading & Storage ===
    s.mass_load              = false;   // Load entire world on start
    s.auto_load              = false;    // Auto-load chunks when needed
    s.auto_unload            = false;    // Auto-unload distant chunks
    s.allow_load_from_file   = false;    // Load chunks from disk
    s.allow_chunk_generation = false;   // Procedural chunk creation disabled
    s.allow_chunk_store      = false;    // Save chunks to disk

    // === Rendering & Mesh Updates ===
    s.render_world           = true;    // Enable world rendering
    s.mesh_changes           = true;    // Enable mesh regeneration
    s.update_interval_ms     = 250;     // Mesh update interval (ms)

    // === Level of Detail (LOD) ===
    s.use_lod                = true;    // Enable LOD
    s.dynamic_lod            = true;    // Recompute LOD only on movement
    s.smart_update           = true;    // Skip LOD updates if camera is static

    // === Debug & Development ===
    s.smart_render           = true;    // Only render visible chunks
    s.debug                  = false;   // Disable debug logs

    // === Default Chunk Prototype ===
    Create_Air_Chunk(s.generic_chunk);

    // === Initialisation Callback ===
    world.Set_Initialise_Callback(
        world.Get_World_Name() == "sponza"? 
        Load_World_From_Sky_Blue : 
        Load_World_From_Terrain
    );

    // === Initialise World ===
    world.Initialise();
}

/* ============================================================================
 * --------------------------- Create_Conway_Game
 * Sets up world parameters for running Conway's Game of Life simulation.
 * Disables loading and storing chunks to focus on simulation logic.
 * ============================================================================ */
inline void Create_Conway_Game(WorldManager& world) {
    world.Load_Settings();
    world_settings_t& s = world.Get_Settings();

    // === World Loading & Storage ===
    s.mass_load               = false;  // Load entire world on start
    s.auto_load               = false;  // Disable auto-load chunks
    s.auto_unload             = false;  // Disable auto-unload chunks
    s.allow_load_from_file    = false;  // Disable loading chunks from disk
    s.allow_chunk_generation  = false;  // Procedural chunk creation disabled
    s.allow_chunk_store       = false;  // Disable saving chunks to disk

    // === Rendering & Mesh Updates ===
    s.render_world          = true;     // Enable world rendering
    s.mesh_changes          = true;     // Enable mesh regeneration
    s.update_interval_ms    = 10;       // Faster mesh update interval (ms)

    // === Level of Detail (LOD) ===
    s.use_lod               = false;    // Disable LOD
    s.dynamic_lod           = false;    // No LOD recomputation on movement
    s.smart_update          = true;     // Skip updates if camera static

    // === Debug & Development ===
    s.smart_render          = false;    // Render all chunks, no culling
    s.debug                 = false;    // Disable debug logs

    // === Default Chunk Prototype ===
    Create_Air_Chunk(s.generic_chunk);

    // === Initialisation Callback ===
    world.Set_Initialise_Callback(FlatWorld);

    // === Create Game of Life instance and bind update callback ===
    constexpr int val = 128;
    auto gol = std::make_shared<GameOfLife>(
        -val, val, -val, val,
        std::vector<Cell>{ {0, 0}, {0, 1}, {0, 2}, {-1, 1}, {1, 1} },
        250
    );

    // Capture by value to keep shared_ptr alive inside the lambda
    world.Set_Update_Callback([=](WorldManager& wm) mutable {
        gol->Update(wm, glm::ivec3(-val, 0, -val), glm::ivec3(val, 0, val));
    });

    // === Initialise World ===
    world.Initialise();
}

/* ============================================================================
 * --------------------------- Create_Wave_World
 * Sets world parameters for a wave-like procedural landscape without chunk
 * loading or storing.
 * ============================================================================ */
inline void Create_Wave_World(WorldManager& world) {
    world.Load_Settings();
    world_settings_t& s = world.Get_Settings();

    // === World Loading & Storage ===
    s.mass_load              = false;   // Load entire world on start
    s.auto_load              = false;   // Disable auto-load chunks
    s.auto_unload            = false;   // Disable auto-unload chunks
    s.allow_load_from_file   = false;   // Disable loading chunks from disk
    s.allow_chunk_generation = false;   // Procedural chunk creation disabled
    s.allow_chunk_store      = false;   // Disable saving chunks to disk

    // === Rendering & Mesh Updates ===
    s.render_world           = true;    // Enable world rendering
    s.mesh_changes           = true;    // Enable mesh regeneration
    s.update_interval_ms     = 250;     // Mesh update interval (ms)

    // === Level of Detail (LOD) ===
    s.use_lod                = false;   // Disable LOD
    s.dynamic_lod            = false;   // No LOD recomputation on movement
    s.smart_update           = true;    // Skip updates if camera is static

    // === Debug & Development ===
    s.smart_render           = true;    // Render only visible chunks
    s.debug                  = false;   // Disable debug logs

    // === Default Chunk Prototype ===
    Create_Air_Chunk(s.generic_chunk);

    // === Initialisation Callback ===
    world.Set_Initialise_Callback(WaveWorld);

    // === Initialise World ===
    world.Initialise();
}

/* ============================================================================
 * --------------------------- Create_Dynamic_World
 * Configures world for dynamic chunk loading/unloading with file storage and
 * disables procedural generation.
 * ============================================================================ */
inline void Create_Dynamic_World(WorldManager& world) {
    world.Load_Settings();
    world_settings_t& s = world.Get_Settings();

    world.Set_World_Name("mount"); // Default name for dynamic world

    // === World Loading & Storage ===
    s.mass_load              = false;   // Load entire world on start
    s.auto_load              = true;    // Enable auto-load chunks
    s.auto_unload            = true;    // Enable auto-unload distant chunks
    s.allow_load_from_file   = true;    // Allow loading chunks from disk
    s.allow_chunk_generation = false;   // Procedural chunk creation disabled
    s.allow_chunk_store      = true;    // Save chunks to disk
    s.chunk_radius           = 6;       // Chunk load/unload radius

    // === Rendering & Mesh Updates ===
    s.render_world           = true;    // Enable world rendering
    s.mesh_changes           = true;    // Enable mesh regeneration
    s.update_interval_ms     = 250;     // Mesh update interval (ms)

    // === Level of Detail (LOD) ===
    s.use_lod                = false;   // Disable LOD
    s.dynamic_lod            = false;   // No LOD recomputation on movement
    s.smart_update           = true;    // Skip updates if camera is static

    // === Debug & Development ===
    s.smart_render           = false;   // Render all chunks, no culling
    s.debug                  = false;   // Disable debug logs

    // === Default Chunk Prototype ===
    Create_Air_Chunk(s.generic_chunk);

    // === Initialisation Callback ===
    world.Set_Initialise_Callback(Load_World_From_Heightmap);

    // === Initialise World ===
    world.Initialise();
}

/* ============================================================================
 * --------------------------- Create_Default_World
 * Dispatches world creation based on the world name property.
 * Supports: mount, sponza (static), canway, wave, dynamic.
 * Exits with error if unknown world name.
 * ============================================================================ */
inline void Create_Default_World(WorldManager& world) {
    std::string name = world.Get_World_Name();
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    if (name == "mount" || name == "sponza") {
        Create_Static_Model_World(world);
    }
    else if (name == "conway") {
        Create_Conway_Game(world);
    }
    else if (name == "wave") {
        Create_Wave_World(world);
    }
    else if (name == "dynamic") {
        Create_Dynamic_World(world);
    }
    else {
        std::cerr << "Error: Unknown default world name '" << world.Get_World_Name() << "'. Exiting.\n";
        std::exit(EXIT_FAILURE);
    }
}

#endif // WORLD_CREATION_FUNCTIONS_H

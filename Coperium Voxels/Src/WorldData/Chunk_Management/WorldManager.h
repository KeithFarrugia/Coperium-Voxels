#pragma once
#ifndef WORLD_MANAGER_H
#define WORLD_MANAGER_H

//----------------------------------------------------------------------------//
//                                  INCLUDES                                  //
//----------------------------------------------------------------------------//
#include <chrono>
#include <functional>
#include <string>

#include "../World.h"
#include "Mesh Generation/Calc_LOD.h"
#include <COIL/Shaders/Shader.h>

//----------------------------------------------------------------------------//
//                               CONSTANTS & ALIASES                          //
//----------------------------------------------------------------------------//
static const std::string WORLD_SAVES_DIR = "World_Saves";
//------------------------------------------------------------------------//
//                            SETTINGS STRUCT                             //
//------------------------------------------------------------------------//
typedef struct world_settings_t {
    //=== World Loading & Storage ===
    bool mass_load              = false;  // Load entire world from save on init
    bool auto_load              = false;  // Auto-load new chunks when needed
    bool auto_unload            = false;  // Auto-unload far-away chunks
    bool allow_load_from_file   = true;   // Permit loading chunk from disk
    bool allow_chunk_generation = true;   // Permit procedural chunk generation
    bool allow_chunk_store      = true;   // Permit saving chunks to disk

    //=== Rendering & Mesh Updates ===
    bool render_world           = true;   // Enable world rendering
    bool mesh_changes           = true;   // Allow chunk mesh updates
    int  update_interval_ms     = 500;    // Minimum ms between mesh updates

    //=== Level of Detail (LOD) ===
    bool use_lod                = true;   // Enable LOD-based mesh detail
    bool dynamic_lod            = true;   // Recompute LOD on camera movement
    bool smart_update           = true;   // Skip LOD if camera hasn’t moved

    lod_dst_set_t lod_set       = lod_dst_set_t(
                                    50.0f  * 50.0f,     // NORMAL
                                    100.0f * 100.0f,    // LOD_2
                                    200.0f * 200.0f,    // LOD_4
                                    400.0f * 400.0f     // LOD_8
                                   );                   // Distance thresholds per LOD

    //=== World Generation ===
    int  chunk_radius           = 1;      // Radius (in chunks) around player
    Chunk generic_chunk;                  // Prototype chunk for mesh generation

    //=== Debug & Development ===
    bool smart_render           = true;   // Render only visible chunks
    bool debug                  = false;  // Enable debug logging
}world_settings_t;

//----------------------------------------------------------------------------//
//                            CLASS: WorldManager                             //
//----------------------------------------------------------------------------//
class WorldManager {
public:
    
    //------------------------------------------------------------------------//
    //                              CONSTRUCTION                              //
    //------------------------------------------------------------------------//
    WorldManager(const std::string& world_name);
    ~WorldManager();

    //------------------------------------------------------------------------//
    //                                CALLBACKS                               //
    //------------------------------------------------------------------------//
    void Set_Initialise_Callback    (std::function<void(WorldManager&)> func);
    void Set_Load_Callback          (std::function<void(WorldManager&)> func);
    void Set_Unload_Callback        (std::function<void(WorldManager&)> func);
    void Set_Render_Callback        (std::function<void(WorldManager&)> func);
    void Set_Update_Callback        (std::function<void(WorldManager&)> func);
    void Set_Generate_Mesh_Callback (std::function<void(WorldManager&)> func);

    void Set_Chunk_Generation_Callback(
        std::function<void(Chunk&, glm::ivec3 offset)> func
    );

    //------------------------------------------------------------------------//
    //                             LIFECYCLE METHODS                          //
    //------------------------------------------------------------------------//
    void Initialise     (bool load_settings = true);
    void Load_Settings  ();
    void Save_Settings  ();

    void Save_World     ();
    void Mass_Load      ();

    void Update         (glm::vec3 player_position);
    void Generate_Mesh  (glm::vec3 player_position);

    void Render(
        Coil::Shader&   shader,
        GLuint          vertex_offset,
        glm::vec3       player_position,
        glm::vec3       player_front
    );
    //------------------------------------------------------------------------//
    //                         DYNAMIC CHUNK OPERATIONS                       //
    //------------------------------------------------------------------------//
    void Dynamic_Update_Chunks      (glm::vec3 player_position);
    void Generate_All_Chunk_Meshes  (glm::vec3 player_position);
    void Randomly_Delete_Chunk      ();
    void Set_Neighbours_to_Update   (
        const glm::ivec3& sector, 
        const glm::ivec3& chunk
    );

    //------------------------------------------------------------------------//
    //                             GETTERS / SETTERS                          //
    //------------------------------------------------------------------------//
    const std::string&  Get_World_Name  () const;
    void                Set_World_Name  (const std::string& name);

    world_settings_t&   Get_Settings    ();
    void                Set_Settings    (const world_settings_t& new_settings);

    World&              Get_World       ();

private:
    //------------------------------------------------------------------------//
    //                         PRIVATE HELPER FUNCTIONS                       //
    //------------------------------------------------------------------------//
    void    Load_New_Chunks     (
        const glm::ivec3&       current_sector,
        const glm::ivec3&       current_chunk
    );
    void    Load_Chunk          (
        const glm::ivec3&       sector_pos,
        const glm::ivec3&       chunk_pos
    );
    void    Load_All_Chunks     ();


    void    Unload_Chunk        (
        const sector_pair_t&    sector_pair,
        const chunk_pair_t&     chunk_pair
    );
    void    Unload_Far_Chunks   (const glm::ivec3& curr_position);
    void    Store_All_Chunks    ();


    bool Read_Chunk(
        sector_loc_t sector_location,
        chunk_loc_t  chunk_location,
        Chunk&       chunk
    );
    void Store_Chunk(
        sector_pair_t sector_pair,
        chunk_pair_t  chunk_pair
    );

    //------------------------------------------------------------------------//
    //                           PRIVATE DATA MEMBERS                         //
    //------------------------------------------------------------------------//
    std::string         world_name;
    world_settings_t    settings;
    World               world;

    // Callbacks storage
    std::function<void(WorldManager&)>            initialise_callback;
    std::function<void(WorldManager&)>            load_callback;
    std::function<void(WorldManager&)>            unload_callback;
    std::function<void(WorldManager&)>            render_callback;
    std::function<void(WorldManager&)>            update_callback;
    std::function<void(WorldManager&)>            generate_mesh_callback;
    std::function<void(Chunk&, glm::ivec3)>       chunk_generation_callback;

    // State tracking
    glm::ivec3  last_chunk    = { INT_MIN, INT_MIN, INT_MIN };
    glm::ivec3  last_position = { INT_MIN, INT_MIN, INT_MIN };

    std::chrono::steady_clock::time_point last_update_time
        = std::chrono::steady_clock::now();

    int   time_acc_ms           = 0;
    bool  initial_update        = true;
    float unload_threshold      = 0;
    float last_no_chunks_drawn  = 0;
};

#endif // WORLD_MANAGER_H

#pragma once
#ifndef WORLD_MANAGER_H
#define WORLD_MANAGER_H

#include "../World.h"
#include <functional>
#include <string>

struct World_Settings {
    bool render_world = true;
    bool auto_load = false;
    bool auto_unload = false;
    bool auto_generate = true;
};

class WorldManager {
public:
    /* ============================================================================
     * --------------------------- WorldManager Constructor
     * Initializes a WorldManager object with a specified world name.
     * ============================================================================ */
    WorldManager(const std::string& world_name);

    /* ============================================================================
     * --------------------------- WorldManager Destructor
     * Cleans up resources used by the WorldManager.
     * ============================================================================ */
    ~WorldManager();

    // Set lambda callbacks
    void Set_Initialise_Callback(std::function<void(WorldManager&)> func);
    void Set_Load_Callback(std::function<void(WorldManager&)> func);
    void Set_Unload_Callback(std::function<void(WorldManager&)> func);
    void Set_Render_Callback(std::function<void(WorldManager&)> func);
    void Set_Update_Callback(std::function<void(WorldManager&)> func);
    void Set_Generate_Mesh_Callback(std::function<void(WorldManager&)> func);

    // Lifecycle functions
    void Initialise();
    void Load();
    void Unload();
    void Render();
    void Update();
    void Generate_Mesh();

    // Getters and Setters
    const std::string& Get_World_Name() const;
    void Set_World_Name(const std::string& name);

    World_Settings& Get_Settings();
    void Set_Settings(const World_Settings& new_settings);

    World& Get_World();

private:
    std::string world_name;
    World_Settings settings;
    World world;

    std::function<void(WorldManager&)> initialise_callback;
    std::function<void(WorldManager&)> load_callback;
    std::function<void(WorldManager&)> unload_callback;
    std::function<void(WorldManager&)> render_callback;
    std::function<void(WorldManager&)> update_callback;
    std::function<void(WorldManager&)> generate_mesh_callback;
};

#endif // WORLD_MANAGER_H

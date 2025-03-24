#include "WorldManager.h"

/* ============================================================================
 * --------------------------- WorldManager Constructor
 * Initializes a WorldManager object with a specified world name.
 * ============================================================================ */
WorldManager::WorldManager(const std::string& world_name) 
: world_name(world_name), world() {}

/* ============================================================================
 * --------------------------- WorldManager Destructor
 * Cleans up resources used by the WorldManager.
 * ============================================================================ */
WorldManager::~WorldManager() {}

/* ============================================================================
 * --------------------------- Set Initialise Callback
 * Assigns a lambda function to be executed when initializing the world.
 * ============================================================================ */
void WorldManager::Set_Initialise_Callback(std::function<void(WorldManager&)> func) {
    initialise_callback = func;
}

/* ============================================================================
 * --------------------------- Set Load Callback
 * Assigns a lambda function to be executed when loading the world.
 * ============================================================================ */
void WorldManager::Set_Load_Callback(std::function<void(WorldManager&)> func) {
    load_callback = func;
}

/* ============================================================================
 * --------------------------- Set Unload Callback
 * Assigns a lambda function to be executed when unloading the world.
 * ============================================================================ */
void WorldManager::Set_Unload_Callback(std::function<void(WorldManager&)> func) {
    unload_callback = func;
}

/* ============================================================================
 * --------------------------- Set Render Callback
 * Assigns a lambda function to be executed when rendering the world.
 * ============================================================================ */
void WorldManager::Set_Render_Callback(std::function<void(WorldManager&)> func) {
    render_callback = func;
}

/* ============================================================================
 * --------------------------- Set Update Callback
 * Assigns a lambda function to be executed when updating the world.
 * ============================================================================ */
void WorldManager::Set_Update_Callback(std::function<void(WorldManager&)> func) {
    update_callback = func;
}

/* ============================================================================
 * --------------------------- Set Generate Mesh Callback
 * Assigns a lambda function to be executed when generating the world mesh.
 * ============================================================================ */
void WorldManager::Set_Generate_Mesh_Callback(std::function<void(WorldManager&)> func) {
    generate_mesh_callback = func;
}

/* ============================================================================
 * --------------------------- Initialise World
 * Calls the initialise callback if it has been set.
 * ============================================================================ */
void WorldManager::Initialise() {
    if (initialise_callback) initialise_callback(*this);
}

/* ============================================================================
 * --------------------------- Load World
 * Calls the load callback if it has been set.
 * ============================================================================ */
void WorldManager::Load() {
    if (load_callback) load_callback(*this);
}

/* ============================================================================
 * --------------------------- Unload World
 * Calls the unload callback if it has been set.
 * ============================================================================ */
void WorldManager::Unload() {
    if (unload_callback) unload_callback(*this);
}

/* ============================================================================
 * --------------------------- Render World
 * Calls the render callback if it has been set and rendering is enabled.
 * ============================================================================ */
void WorldManager::Render() {
    if (render_callback && settings.render_world) render_callback(*this);
}

/* ============================================================================
 * --------------------------- Update World
 * Calls the update callback if it has been set.
 * ============================================================================ */
void WorldManager::Update() {
    if (update_callback) update_callback(*this);
}

/* ============================================================================
 * --------------------------- Generate Mesh
 * Calls the generate mesh callback if it has been set and auto generation is enabled.
 * ============================================================================ */
void WorldManager::Generate_Mesh() {
    if (generate_mesh_callback && settings.auto_generate) generate_mesh_callback(*this);
}

/* ============================================================================
 * --------------------------- Get World Name
 * Returns the name of the world.
 * ============================================================================ */
const std::string& WorldManager::Get_World_Name() const {
    return world_name;
}

/* ============================================================================
 * --------------------------- Set World Name
 * Updates the name of the world.
 * ============================================================================ */
void WorldManager::Set_World_Name(const std::string& name) {
    world_name = name;
}

/* ============================================================================
 * --------------------------- Get Settings
 * Returns a reference to the settings struct.
 * ============================================================================ */
World_Settings& WorldManager::Get_Settings() {
    return settings;
}

/* ============================================================================
 * --------------------------- Set Settings
 * Updates the settings of the world manager.
 * ============================================================================ */
void WorldManager::Set_Settings(const World_Settings& new_settings) {
    settings = new_settings;
}

/* ============================================================================
 * --------------------------- Get World
 * Returns a reference to the managed world.
 * ============================================================================ */
World& WorldManager::Get_World() {
    return world;
}

#include "WorldManager.h"

/* ============================================================================
 * --------------------------- WorldManager Constructor
 * Initializes a WorldManager object with a specified world name.
 * ============================================================================ */
WorldManager::WorldManager(const std::string& world_name) 
: world_name(world_name), world() {
}

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

void WorldManager::Set_Chunk_Generation_Callback(
    std::function<void(Chunk&, glm::ivec3 offset)> func
){
    chunk_generation_callback = func;
}

/* ============================================================================
 * --------------------------- Initialise World
 * Calls the initialise callback if it has been set.
 * ============================================================================ */
void WorldManager::Initialise(bool load_settings) {
    if (load_settings)          Load_Settings();
    if (settings.mass_load)     Mass_Load();
    if (initialise_callback)    initialise_callback(*this);
    unload_threshold =
        settings.chunk_radius * CHUNK_SIZE_X *
        settings.chunk_radius * CHUNK_SIZE_Z;
}


void WorldManager::Save_World(){
    Store_All_Chunks();
}

void WorldManager::Mass_Load(){
    Load_All_Chunks();
}

/* ============================================================================
 * --------------------------- Render World
 * Calls the render callback if it has been set and rendering is enabled.
 * ============================================================================ */
void WorldManager::Render(
    Coil::Shader&   shader,
    GLuint          vertex_offset,
    glm::vec3       player_position,
    glm::vec3       player_front
) {
    if (render_callback && settings.render_world) render_callback(*this);
    if (!settings.render_world) return;
    size_t drawn = 0;
    sectors_t* sectors = world.Get_All_Sectrs();
    for (sector_pair_t sector_pair : *sectors) {
        chunks_t* chunks = sector_pair.second->Get_All_Chunks();
        for (chunk_pair_t chunk_pair : *chunks) {

            glm::vec3 offset = {
                sector_pair.first.X() * SECTR_SIZE_X + chunk_pair.first.X() * CHUNK_SIZE_X,
                                                       chunk_pair.first.Y() * CHUNK_SIZE_Y,
                sector_pair.first.Z() * SECTR_SIZE_Z + chunk_pair.first.Z() * CHUNK_SIZE_Z
            };

            if (settings.smart_render) {
                glm::vec3 toChunk = offset - player_position;
                if (glm::dot(toChunk, player_front) <= 0.0f) {
                    continue;
                }
            }

            shader.Set_Vec3(vertex_offset, offset);
            chunk_pair.second->Draw_Mesh();
            ++drawn;
        }
    }

    if (drawn != last_no_chunks_drawn && settings.debug) {
        std::cout << "Chunks drawn this frame: " << drawn << std::endl;
        last_no_chunks_drawn = static_cast<float>(drawn);
    }
}


/* ============================================================================
 * --------------------------- Update World
 * Calls the update callback if it has been set.
 * ============================================================================ */
void WorldManager::Update(glm::vec3 player_position) {

    Dynamic_Update_Chunks(player_position);
    if (update_callback) update_callback(*this);
    
    Generate_Mesh(player_position);
    initial_update = false;
}

/* ============================================================================
 * --------------------------- Generate Mesh
 * Calls the generate mesh callback if it has been set and auto generation is enabled.
 * ============================================================================ */
void WorldManager::Generate_Mesh(glm::vec3 player_position) {
    if (generate_mesh_callback) generate_mesh_callback(*this);
    if (settings.mesh_changes || initial_update) {
        Generate_All_Chunk_Meshes(player_position);
    }
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
world_settings_t& WorldManager::Get_Settings() {
    return settings;
}

/* ============================================================================
 * --------------------------- Set Settings
 * Updates the settings of the world manager.
 * ============================================================================ */
void WorldManager::Set_Settings(const world_settings_t& new_settings) {
    settings = new_settings;
}

/* ============================================================================
 * --------------------------- Get World
 * Returns a reference to the managed world.
 * ============================================================================ */
World& WorldManager::Get_World() {
    return world;
}

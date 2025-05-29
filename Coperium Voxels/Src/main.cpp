#include <COIL/Utility/Initializer.h>
#include <COIL/Window/Window.h>
#include "WorldData/Chunk_Management/WorldManager.h"
#include "World Creation Functions.h"
#include "VoxelApp.h"

int main() {
    Coil::Logger::init_logger(Coil::LOG_TO_FILE);
    Coil::Initialise_Opengl();
    Coil::Initialise_GLAD();

    Coil::Window window("Voxel Test Case", 1500, 1000);

    WorldManager world("mount");

    // Check Readme.md for information on World Configurations
    Create_Default_World(world);

    VoxelApp app(window, world);
    app.Run();

    return 0;
}
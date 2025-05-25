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

    WorldManager world_1("mount");
    Create_Static_Model_World(world_1);

    VoxelApp app(window, world_1);
    app.Run();

    return 0;
}
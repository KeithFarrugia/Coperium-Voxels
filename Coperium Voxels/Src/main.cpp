#include <COIL/Utility.h>
#include <COIL/Shaders/Shader.h>
#include <COIL/Mesh/Basic_Mesh.h>
#include <COIL/Window/Window.h>
#include <COIL/Camera/Fly Camera/Fly_Camera.h>

#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>  // For FPS calculation

#include "WorldData/World.h"

//#include "EditorCamera.h"
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

constexpr int GRID_SIZE_F_X = 128;
constexpr int GRID_SIZE_F_Y = 64;
constexpr int GRID_SIZE_F_Z = 128;

constexpr int GRID_SIZE_S_X = -128;
constexpr int GRID_SIZE_S_Y = 0;
constexpr int GRID_SIZE_S_Z = -128;

int main() {
    World w;

    auto start = std::chrono::high_resolution_clock::now();

    for (int x = GRID_SIZE_S_X; x < GRID_SIZE_F_X; x++) {
        for (int y = GRID_SIZE_S_Y; y < GRID_SIZE_F_Y; y++) {
            for (int z = GRID_SIZE_S_Z; z < GRID_SIZE_F_Z; z++) {
                w.Create_Voxel(vox_data_t{
                        glm::ivec3(x, y, z),    // position
                        glm::ivec3(0, 0, 0),    // colour
                        voxel_type_t::NORMAL,   // type
                        true,                   // solid
                        false,                  // transparency
                        rel_loc_t::WORLD_LOC    // Relative
                    });
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Time taken to create voxels: " << std::fixed << std::setprecision(6)
        << duration.count() << " seconds." << std::endl;

    return 0;
}

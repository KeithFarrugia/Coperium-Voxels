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


int main() {
    glm::vec3 x = glm::vec3(1010, 0, 1010);

    std::cout << "\n----------------------------- ID -----------------------------\n";

    glm::vec3 Sec_ID = World::Convert_Loc_2_ID(x, rel_loc_t::WORLD_LOC, rel_loc_t::SECTOR_LOC);
    std::cout << "W -> S : [" << Sec_ID.x << "] [" << Sec_ID.y << "] [" << Sec_ID.z << "]\n";

    glm::vec3 Chunk_ID = World::Convert_Loc_2_ID(x, rel_loc_t::WORLD_LOC, rel_loc_t::CHUNK_LOC);
    std::cout << "W -> C : [" << Chunk_ID.x << "] [" << Chunk_ID.y << "] [" << Chunk_ID.z << "]\n";



    std::cout << "\n----------------------------- Loc -----------------------------\n";

    glm::vec3 Sec_Loc = World::Convert_Loc_2_Offset(x, rel_loc_t::WORLD_LOC, rel_loc_t::SECTOR_LOC);
    std::cout << "W -> S : [" << Sec_Loc.x << "] [" << Sec_Loc.y << "] [" << Sec_Loc.z << "]\n";

    glm::vec3 Chunk_Loc = World::Convert_Loc_2_Offset(x, rel_loc_t::WORLD_LOC, rel_loc_t::CHUNK_LOC);
    std::cout << "W -> C : [" << Chunk_Loc.x << "] [" << Chunk_Loc.y << "] [" << Chunk_Loc.z << "]\n";


    std::cout << "\n----------------------------- ID -----------------------------\n";

    glm::vec3 Chunk_ID2 = World::Convert_Loc_2_ID(Sec_Loc, rel_loc_t::SECTOR_LOC, rel_loc_t::CHUNK_LOC);
    std::cout << "S -> C : [" << Chunk_ID2.x << "] [" << Chunk_ID2.y << "] [" << Chunk_ID2.z << "]\n";


    std::cout << "\n----------------------------- Loc -----------------------------\n";
    glm::vec3 Chunk_Loc2 = World::Convert_Loc_2_Offset(Sec_Loc, rel_loc_t::SECTOR_LOC, rel_loc_t::CHUNK_LOC);
    std::cout << "W -> C : [" << Chunk_Loc2.x << "] [" << Chunk_Loc2.y << "] [" << Chunk_Loc2.z << "]\n";

}
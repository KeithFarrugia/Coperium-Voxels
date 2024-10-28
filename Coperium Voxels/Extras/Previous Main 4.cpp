#include <COIL/Utility.h>
#include <COIL/Shaders/Shader.h>
#include <COIL/Mesh/Basic_Mesh.h>
#include <COIL/Window/Window.h>
#include <COIL/Camera/Fly Camera/Fly_Camera.h>

#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_opengl3.h>
#include <IMGUI/imgui_impl_glfw.h>

#include <iostream>
#include <vector>
#include <iomanip>

#include "Compact Data/Compact Location Data/CLD.h"
#include "Compact Data/Compact Colour Data/CCD.h"
#include "Compact Data/Compact Block/CB.h"
#include "Utility/Render Testing.h"

#include "Compact Data/World Data/World/World.h"
#include "Compact Data/Cube Mesh/CCMS.h"



int main() {
    // Initialize Logger and OpenGL
    Coil::Logger::init_logger(Coil::LOG_TO_FILE);
    Coil::Initialise_Opengl();
    Coil::Initialise_GLAD();

    // Create Window
    Coil::Window window("Hello World", 640, 480);
    //window.EnableVsync();
    window.FF_Clockwise();
    window.EnableDepthTest();
    window.EnableCulling();
    glfwSwapInterval(0);

    Coil::Shader shader(std::string("Basic"));
    Coil::Basic_Mesh mesh;
    Coil::Fly_Camera camera(window, 0, 0, 2);
    camera.Take_Over_All_Input();

    World w;
    Voxel v;
    //world.Add_Voxel(glm::ivec3(0, 0, 0), glm::ivec3(0, 0, 0), 15, voxel_type_t::AIR);
    //Voxel v = world.Get_Voxel(0, 0, 0);
    
    std::vector<GLfloat> vertex_mesh;
    std::vector<GLuint>  index_mesh;

    int vertex_offset = 0; int index_offset = 0;


    w.Add_Voxel(glm::ivec3(-1, 0, 0), glm::ivec3(15, 0, 0), 15, voxel_type_t::NORMAL);
    w.Add_Voxel(glm::ivec3(-2, 0, 0), glm::ivec3(15, 15, 0), 15, voxel_type_t::NORMAL);
    w.Add_Voxel(glm::ivec3(0, 0, 0), glm::ivec3(15, 0, 0), 15, voxel_type_t::NORMAL);
    
    w.Display();

    /*for (auto& sector_entry : *w.Get_Sectors()) {
        std::cout   << "\n---------------- Sector [" 
                    << sector_entry.second.Get_Offset_X() << "] [" 
                    << sector_entry.second.Get_Offset_Z() << "] ----------------"
                    << std::endl;

        for (auto& chunk_entry : *sector_entry.second.Get_Chunks()) {
            std::cout   << "\t Chunk ["
                        << chunk_entry.second.Get_Offset_X() << "] ["
                        << chunk_entry.second.Get_Offset_Y() << "] ["
                        << chunk_entry.second.Get_Offset_Z() << "]"
                        << std::endl;

            for (auto& voxel_entry : *chunk_entry.second.Get_Voxels()) {
                std::cout   << "Voxel ["
                            << voxel_entry.first.Get_X() << "] ["
                            << voxel_entry.first.Get_Y() << "] ["
                            << voxel_entry.first.Get_Z() << "]"
                            << std::endl;
                std::cout << voxel_entry.second.To_String();
                std::cout << "\n";

                glm::ivec3 position = glm::vec3(
                    voxel_entry.first.Get_X() + chunk_entry.second.Get_Offset_X() * CHUNK_X_MAX + sector_entry.second.Get_Offset_X() * SECTOR_X_MAX,
                    voxel_entry.first.Get_Y() + chunk_entry.second.Get_Offset_Y() * CHUNK_Y_MAX,
                    voxel_entry.first.Get_Z() + chunk_entry.second.Get_Offset_Z() * CHUNK_Z_MAX + sector_entry.second.Get_Offset_Z() * SECTOR_Z_MAX
                );
                glm::ivec3 colour = glm::vec3(
                    voxel_entry.second.Get_R(),
                    voxel_entry.second.Get_G(),
                    voxel_entry.second.Get_B()
                );

                CubeFaceFlags flags = static_cast<CubeFaceFlags>(0);

                if  (w.Get_Voxel(position.x+1,  position.y,     position.z  ).Get_Type() != voxel_type_t::NORMAL) {
                    flags = (CubeFaceFlags)(flags | CubeFaceFlags::RIGHT_FACE);

                }if (w.Get_Voxel(position.x-1,  position.y,     position.z  ).Get_Type() != voxel_type_t::NORMAL) {
                    flags = (CubeFaceFlags)(flags | CubeFaceFlags::LEFT_FACE);

                }if (w.Get_Voxel(position.x,    position.y+1,   position.z  ).Get_Type() != voxel_type_t::NORMAL) {
                    flags = (CubeFaceFlags)(flags | CubeFaceFlags::TOP_FACE);

                }if (w.Get_Voxel(position.x,    position.y-1,   position.z  ).Get_Type() != voxel_type_t::NORMAL) {
                    flags = (CubeFaceFlags)(flags | CubeFaceFlags::BOTTOM_FACE);

                }if (w.Get_Voxel(position.x,    position.y,     position.z+1).Get_Type() != voxel_type_t::NORMAL) {
                    flags = (CubeFaceFlags)(flags | CubeFaceFlags::BACK_FACE);
                        
                }if (w.Get_Voxel(position.x,    position.y,     position.z-1).Get_Type() != voxel_type_t::NORMAL) {
                    flags = (CubeFaceFlags)(flags | CubeFaceFlags::FRONT_FACE);

                }
                AddCubeMeshToArrays(
                    position        ,   colour      ,
                    vertex_mesh     ,   index_mesh  ,
                    vertex_offset   ,  index_offset ,
                    flags
                );
            }
        }
    }*/
    //mesh.Configure_Mesh(
    //    vertex_mesh.data(),
    //    sizeof(GLfloat),
    //    vertex_offset * FACE_NUM_ELEMENTS,
    //    GL_FLOAT,
    //    FACE_NUM_ELEMENTS
    //);

    //// Configure the index buffer
    //mesh.Configure_Index_Buffer(
    //    index_mesh.data(),
    //    sizeof(GLuint),
    //    index_offset
    //);

    //mesh.Add_Vertex_Set(0, 1, 0);
    //mesh.Add_Vertex_Set(1, 1, 1);
    //mesh.Clean_Mesh();

    //shader.Add_Shaders(
    //    Coil::shader_list_t{
    //        Coil::shader_info_t{"compact_v2.vert", Coil::shader_type_t::VERTEX_SHADER},
    //        Coil::shader_info_t{"compact_v2.frag", Coil::shader_type_t::FRAGMENT_SHADER}
    //    });
    //shader.Compile_And_Link();

    //while (!window.Is_Closed()) {
    //    int width, height;
    //    window.Get_Size(width, height);

    //    // Clear screen
    //    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //    glm::mat4 model = glm::mat4(1.0f);

    //    shader.Use();
    //    shader.Set_Matrix4("projection" , camera.Calc_Projection_Matrix());
    //    shader.Set_Matrix4("view"       , camera.Calc_View_Matrix());
    //    shader.Set_Matrix4("model"      , model);

    //    mesh.Draw_Mesh(false);


    //    // Swap buffers
    //    window.SwapBuffers();

    //    // Poll events and update camera
    //    glfwPollEvents();
    //    camera.Update();
    //}

    //// Cleanup and exit
    //window.Del();
    //glfwTerminate();

    return 0;
}
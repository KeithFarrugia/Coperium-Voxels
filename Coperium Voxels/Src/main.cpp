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
#include <chrono>  // For FPS calculation

#include "Compact Data/Compact Location Data/CLD.h"
#include "Compact Data/Compact Colour Data/CCD.h"
#include "Compact Data/Compact Block/CB.h"
#include "Compact Data/World Data/World/World.h"
#include "Compact Data/Cube Mesh/CCMS.h"
#include "Compact Data/World Data/World_Mesh.h"

constexpr int GRID_SIZE_X = 16;
constexpr int GRID_SIZE_Y = 64;
constexpr int GRID_SIZE_Z = 16;

int main() {
    // Initialize Logger and OpenGL
    Coil::Logger::init_logger(Coil::LOG_TO_FILE);
    Coil::Initialise_Opengl();
    Coil::Initialise_GLAD();

    // Create Window
    Coil::Window window("Hello World", 640, 480);
    window.FF_Clockwise();
    window.EnableDepthTest();
    window.EnableCulling();
    glfwSwapInterval(0);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window.Get_Window(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    Coil::Shader shader(std::string("Basic"));
    Coil::Fly_Camera camera(window, 0, 0, 2);
    camera.Take_Over_All_Input();

    World w;

    for (int x = 0; x < GRID_SIZE_X; x++) {
        for (int y = 0; y < GRID_SIZE_Y; y++) {
            for (int z = 0; z < GRID_SIZE_Z; z++) {
                w.Add_Voxel(glm::ivec3(x, y, z), glm::ivec3(x, (int)(y / 4.0f), z), 15, voxel_type_t::NORMAL);
            }
        }
    }

    //w.Display();
    Generate_Chunk_Meshes(w);

    shader.Add_Shaders(
        Coil::shader_list_t{
            Coil::shader_info_t{"compact_v2.vert", Coil::shader_type_t::VERTEX_SHADER},
            Coil::shader_info_t{"compact_v2.frag", Coil::shader_type_t::FRAGMENT_SHADER}
        });
    shader.Compile_And_Link();

    // Variables for FPS calculation
    float fps = 0.0f;
    int frames = 0;
    auto start = std::chrono::high_resolution_clock::now();

    while (!window.Is_Closed()) {
        int width, height;
        window.Get_Size(width, height);

        // Clear screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);

        shader.Use();
        shader.Set_Matrix4("projection", camera.Calc_Projection_Matrix());
        shader.Set_Matrix4("view", camera.Calc_View_Matrix());
        shader.Set_Matrix4("model", model);

        Render_Chunk_Meshes(w, shader);

        // Calculate FPS
        frames++;
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        if (duration.count() >= 1.0f) {
            fps = frames / duration.count();
            frames = 0;
            start = end;
        }

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Set the ImGui window position to the top-left corner
        ImGui::SetNextWindowPos(ImVec2(0, 0));  // Top-left corner
        ImGui::SetNextWindowSize(ImVec2(200, 20));  // Set the size of the box

        // Show FPS in ImGui
        ImGui::Begin("FPS Display", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
        ImGui::Text("FPS: %.1f", fps);
        ImGui::End();

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        window.SwapBuffers();

        // Poll events and update camera
        glfwPollEvents();
        camera.Update();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    window.Del();
    glfwTerminate();

    return 0;
}

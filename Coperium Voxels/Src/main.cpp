#include <COIL/Utility.h>
#include <COIL/Shaders/Shader.h>
#include <COIL/Mesh/Basic_Mesh.h>
#include <COIL/Window/Window.h>
#include <COIL/Camera/Fly Camera/Fly_Camera.h>

#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>  // For FPS calculation

#include "Compact Data/Compact Location Data/CLD.h"
#include "Compact Data/Compact Colour Data/CCD.h"
#include "Compact Data/Compact Block/CB.h"
//#include "Compact Data/World Data/World/World.h"
#include "Compact Data/Cube Mesh/CCMS.h"
#include "Compact Data/World Data/World_Mesh.h"
#include "EditorCamera.h"
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

constexpr int GRID_SIZE_S_X = 64;
constexpr int GRID_SIZE_S_Y = 64;
constexpr int GRID_SIZE_S_Z = 64;
constexpr int GRID_SIZE_F_X = -64;
constexpr int GRID_SIZE_F_Y = 0;
constexpr int GRID_SIZE_F_Z = -64;

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


    Coil::Shader shader(std::string("Basic"));

    World w;

    auto start_c = std::chrono::high_resolution_clock::now();
    Chunk c;
    for (int x = GRID_SIZE_F_X; x < GRID_SIZE_S_X; x++) {
        for (int y = GRID_SIZE_F_Y; y < GRID_SIZE_S_Y; y++) {
            for (int z = GRID_SIZE_F_Z; z < GRID_SIZE_S_Z; z++) {
                w.Add_Voxel(glm::ivec3(x, y, z), glm::ivec3(x, (int)(y / 4.0f), z), 15, voxel_type_t::NORMAL);
            }
        }
    }

    auto end_c = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_c - start_c;
    std::cout << "Time to fill the 3D array: " << elapsed.count() << " seconds\n";



    
    
    /*std::vector<std::vector<std::vector<int>>> array(GRID_SIZE_S_X, std::vector<std::vector<int>>(GRID_SIZE_S_Y, std::vector<int>(GRID_SIZE_S_Z)));

    auto start_c = std::chrono::high_resolution_clock::now();
    Chunk c;
    for (int x = 0; x < GRID_SIZE_S_X; x++) {
        for (int y = 0; y < GRID_SIZE_S_Y; y++) {
            for (int z = 0; z < GRID_SIZE_S_Z; z++) {
                array[x][y][z] = x + y + z;
            }
        }
    }
    auto end_c = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_c - start_c;
    std::cout << "Time to fill the 3D array: " << elapsed.count() << " seconds\n";*/
    




    Generate_All_Chunk_Meshes(w);

    EditorCamera camera(window, w, 0, -3, 2);

    shader.Add_Shaders(
        Coil::shader_list_t{
            Coil::shader_info_t{"compact_v2.vert", Coil::shader_type_t::VERTEX_SHADER},
            Coil::shader_info_t{"compact_v2.frag", Coil::shader_type_t::FRAGMENT_SHADER}
        });
    shader.Compile_And_Link();

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window.Get_Window(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
    io.WantCaptureMouse = true;
    io.WantCaptureKeyboard = false;

    // Variables for FPS calculation
    float fps = 0.0f;
    int frames = 0;
    auto start = std::chrono::high_resolution_clock::now();

    // Color picker variable
    float color[4] = { 0.0f, 1.0f, 0.0f, 1.0f };  // Default to green color

    while (!window.Is_Closed()) {
        int width, height;
        window.Get_Size(width, height);

        // Clear screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  // Use selected color for the clear color
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

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Display FPS in the top left
        ImGui::SetNextWindowPos(ImVec2(10, 10));  // Top-left corner
        ImGui::Begin("FPS Window", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("FPS: %.1f", fps);
        ImGui::End();

        // Color Picker UI (Color Wheel Style)
        ImGui::SetNextWindowPos(ImVec2(10, 50));  // Below the FPS counter
        ImGui::Begin("Color Picker", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

        // ImGui ColorPicker (with color wheel image)
        ImGui::ColorPicker4("Pick a Color", color, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_PickerHueWheel);

        ImGui::End();

        // Render ImGui
        ImGui::Render();
        ImDrawData* draw_data = ImGui::GetDrawData();
        if (draw_data != nullptr) {
            ImGui_ImplOpenGL3_RenderDrawData(draw_data);
        }

        // Swap buffers
        window.SwapBuffers();

        // Poll events and update camera
        glfwPollEvents();
        camera.Update();
    }

    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    window.Del();
    glfwTerminate();

    return 0;
}
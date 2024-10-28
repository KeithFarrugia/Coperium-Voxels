#include <COIL/Utility.h>
#include <COIL/Shaders/Shader.h>
#include <COIL/Mesh/Basic_Mesh.h>
#include <COIL/Window/Window.h>
#include <COIL/Camera/Fly Camera/Fly_Camera.h>

#include <iostream>
#include <iomanip>
#include <chrono>  // For FPS calculation
#include "WorldData/World.h"
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

constexpr int GRID_SIZE_F_X = 128;
constexpr int GRID_SIZE_F_Y = 64;
constexpr int GRID_SIZE_F_Z = 128;

constexpr int GRID_SIZE_S_X = -128;
constexpr int GRID_SIZE_S_Y = 0;
constexpr int GRID_SIZE_S_Z = -128;
int main() {

    Coil::Logger::init_logger(Coil::LOG_TO_FILE);
    Coil::Initialise_Opengl();
    Coil::Initialise_GLAD();



    Coil::Window window("Voxel Test Case", 640, 480);
    window.FF_Clockwise();
    window.EnableDepthTest();
    window.EnableCulling();
    glfwSwapInterval(0);

    Coil::Shader shader(std::string("Basic"));
    World w;
    //w.Create_Voxel(vox_data_t{
    //    glm::ivec3(0, 0, 0),                // position
    //    glm::ivec3(15, 15, 15),  // color
    //    voxel_type_t::NORMAL,               // type
    //    true,                               // solid
    //    false,                              // transparency
    //    rel_loc_t::WORLD_LOC                // Relative
    //});
    //w.Create_Voxel(vox_data_t{
    //    glm::ivec3(-2, 0, 0),                // position
    //    glm::ivec3(0, 0, 15),  // color
    //    voxel_type_t::NORMAL,               // type
    //    true,                               // solid
    //    false,                              // transparency
    //    rel_loc_t::WORLD_LOC                // Relative
    //});
    //w.Create_Voxel(vox_data_t{
    //    glm::ivec3(-1, 0, 0),                // position
    //    glm::ivec3(0, 0, 15),  // color
    //    voxel_type_t::NORMAL,               // type
    //    true,                               // solid
    //    false,                              // transparency
    //    rel_loc_t::WORLD_LOC                // Relative
    //});
    auto start = std::chrono::high_resolution_clock::now();
    for (int x = GRID_SIZE_S_X; x < GRID_SIZE_F_X; x++) {
        for (int y = GRID_SIZE_S_Y; y < GRID_SIZE_F_Y; y++) {
            for (int z = GRID_SIZE_S_Z; z < GRID_SIZE_F_Z; z++) {
                w.Create_Voxel(vox_data_t{
                        glm::ivec3(x, y, z),                // position
                        glm::ivec3(x, (int)(y / 4.0f), z),  // color
                        voxel_type_t::NORMAL,               // type
                        true,                               // solid
                        false,                              // transparency
                        rel_loc_t::WORLD_LOC                // Relative
                    });
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken to create voxels: " << std::fixed << std::setprecision(6)
        << duration.count() << " seconds." << std::endl;

    start = std::chrono::high_resolution_clock::now();
    sectors_t* sectors = w.Get_All_Sectrs();
    for (auto [sectorLoc, sector] : *sectors) {
        chunks_t* chunks = sector.Get_All_Chunks();
        for (auto [chunkLoc, chunk] : *chunks) {
            chunk.Generate_Mesh(w, chunkLoc, sectorLoc);
        }
    }
    end = std::chrono::high_resolution_clock::now();
     duration = end - start;
    std::cout << "Time taken to Generate Mesh: " << std::fixed << std::setprecision(6)
        << duration.count() << " seconds." << std::endl;

    



    Coil::Fly_Camera camera(window, 0, -1, 1);
    camera.Take_Over_All_Input();

    shader.Add_Shaders(
        Coil::shader_list_t{
            Coil::shader_info_t{"compact_v2.vert", Coil::shader_type_t::VERTEX_SHADER},
            Coil::shader_info_t{"compact_v2.frag", Coil::shader_type_t::FRAGMENT_SHADER}
        });
    shader.Compile_And_Link();

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
    start = std::chrono::high_resolution_clock::now();


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

        for (auto [sectorLoc, sector] : *sectors) {
            chunks_t* chunks = sector.Get_All_Chunks();
            for (auto [chunkLoc, chunk] : *chunks) {

                glm::ivec3 offset = glm::vec3(
                    chunkLoc.X() * CHUNK_SIZE_X + sectorLoc.X() * SECTR_SIZE_X,
                    chunkLoc.Y() * CHUNK_SIZE_Y,
                    chunkLoc.Z() * CHUNK_SIZE_Z + sectorLoc.Z() * SECTR_SIZE_Z
                );

                shader.Set_Vec3("vertex_offset", offset);

                chunk.Draw_Mesh();
            }
        };

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


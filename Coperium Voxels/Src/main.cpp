#include <COIL/Utility.h>
#include <COIL/Shaders/Shader.h>
#include <COIL/Mesh/Basic_Mesh.h>
#include <COIL/Window/Window.h>
#include <COIL/Camera/Fly Camera/Fly_Camera.h>

#include <iostream>
#include <chrono>
#include "WorldData/World.h"
#include "WorldData/Create_Generic_Chunks.h"
#include "Voxel Stuff.h"
#include "Imgui_setup.h"

void setupShader(Coil::Shader& shader) {
    shader.Add_Shaders({
        Coil::shader_info_t{"compact_v2.vert", Coil::shader_type_t::VERTEX_SHADER},
        Coil::shader_info_t{"compact_v2.frag", Coil::shader_type_t::FRAGMENT_SHADER}
        });
    shader.Compile_And_Link();
}

void setupWindow(Coil::Window& window) {
    window.FF_Clockwise();
    window.EnableDepthTest();
    window.EnableCulling();
    glfwSwapInterval(0);
}

void calculateFPS(int& frames, auto& start, float& fps) {
    frames++;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    if (duration.count() >= 1.0f) {
        fps = frames / duration.count();
        frames = 0;
        start = end;
    }
}





/* ============================================================================
 *                                  MAIN
 * ============================================================================
 */


int main() {
    Coil::Logger::init_logger(Coil::LOG_TO_FILE);
    Coil::Initialise_Opengl();
    Coil::Initialise_GLAD();

    Coil::Window window("Voxel Test Case", 640, 480);
    setupWindow(window);

    World w;
    generate_blocks_and_mesh(w);

    Coil::Shader shader("Basic");
    setupShader(shader);

    Coil::Fly_Camera camera(window, 0, -1, 1);
    camera.Take_Over_All_Input();

    // Initialize ImGui
    InitializeImGui(window);

    // FPS and color state
    float fps = 0.0f;
    int frames = 0;
    auto start = std::chrono::high_resolution_clock::now();
    float color[4] = { 0.0f, 1.0f, 0.0f, 1.0f };  // Default to green color

    GLuint vertex_offset = shader.Get_Uniform("vertex_offset");

    // Main rendering loop
    while (!window.Is_Closed()) {
        int width, height;
        window.Get_Size(width, height);

        // Clear screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  // Use selected color for the clear color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);

        // Use shader and set matrices
        shader.Use();
        shader.Set_Matrix4("projection", camera.Calc_Projection_Matrix());
        shader.Set_Matrix4("view", camera.Calc_View_Matrix());
        shader.Set_Matrix4("model", model);

        // Render voxels
        render_voxels(w, shader, vertex_offset);

        // Calculate FPS
        calculateFPS(frames, start, fps);

        // Render ImGui frame
        RenderImGuiFrame(fps, color);

        // Swap buffers and update camera
        window.SwapBuffers();
        glfwPollEvents();
        camera.Update();
    }

    // Cleanup ImGui
    CleanupImGui();

    // Cleanup window and terminate GLFW
    window.Del();
    glfwTerminate();

    return 0;
}

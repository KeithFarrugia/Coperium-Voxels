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

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window.Get_Window(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    bool optimise = true;


    // Configure Mesh
    Coil::Shader shader(std::string("Basic"));
    Coil::Basic_Mesh mesh;


    if (optimise == true) {
        Render_Compact_Cube_Mesh(mesh, shader);
    } else {
        Render_Simple_Cube_Mesh(mesh, shader);
    }




    // Initialize Camera
    Coil::Fly_Camera camera(window, 0, 0, 2);
    camera.Take_Over_All_Input();

    // Main rendering loop
    while (!window.Is_Closed()) {
        int width, height;
        window.Get_Size(width, height);

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Clear screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);

        shader.Use();
        shader.Set_Matrix4("projection", camera.Calc_Projection_Matrix());
        shader.Set_Matrix4("view", camera.Calc_View_Matrix());
        shader.Set_Matrix4("model", model);

        mesh.Draw_Mesh(false);

        // Render ImGui UI
        ImGui::Begin("FPS Counter");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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

    // Cleanup and exit
    window.Del();
    glfwTerminate();

    return 0;
}

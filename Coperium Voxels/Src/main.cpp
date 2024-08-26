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
#include "Compact Data/Block Mesh/CBM.h"

constexpr int GRID_SIZE_X = 16;
constexpr int GRID_SIZE_Y = 64;
constexpr int GRID_SIZE_Z = 16;

std::unique_ptr<GLfloat[]> FlattenMeshVector(const std::vector<std::unique_ptr<GLfloat[]>>& meshes, int& totalSize) {
    totalSize = 0;
    for (const auto& mesh : meshes) {
        totalSize += COMPACT_CUBE_SIZE;
    }

    auto flattenedMesh = std::make_unique<GLfloat[]>(totalSize);
    size_t offset = 0;
    for (const auto& mesh : meshes) {
        std::copy(mesh.get(), mesh.get() + COMPACT_CUBE_SIZE, flattenedMesh.get() + offset);
        offset += COMPACT_CUBE_SIZE;
    }
    return flattenedMesh;
}

int main() {
    // Initialize Logger and OpenGL
    Coil::Logger::init_logger(Coil::LOG_TO_FILE);
    Coil::Initialise_Opengl();
    Coil::Initialise_GLAD();

    // Create Window
    Coil::Window window("Hello World", 640, 480);
    window.EnableVsync();
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

    // Create Cube Meshes
    std::vector<std::unique_ptr<GLfloat[]>> cubeMeshes;
    for (int x = 0; x < GRID_SIZE_X; x++) {
        for (int y = 0; y < GRID_SIZE_Y; y++) {
            for (int z = 0; z < GRID_SIZE_Z; z++) {
                CB cube(x, y, z, x, (int)(y / 4.0f), z);
                auto sub_mesh = cube.Generate_Mesh();
                cubeMeshes.push_back(std::move(sub_mesh));
            }
            printf("G Colour %d at [%d]\n", (int)(y / 4.0f), y);
        }
    }

    int totalSize = 0;
    auto cubesMesh = FlattenMeshVector(cubeMeshes, totalSize);

    // Configure Mesh
    Coil::Basic_Mesh mesh;
    mesh.Configure_Mesh(
        cubesMesh.get(),
        sizeof(GLfloat),
        totalSize,
        GL_FLOAT,
        2
    );

    mesh.Add_Vertex_Set(0, 1, 0);
    mesh.Add_Vertex_Set(1, 1, 1);
    mesh.Clean_Mesh();

    // Initialize Shader
    Coil::Shader shader(std::string("Basic"));
    shader.Add_Shaders(
        Coil::shader_list_t{
            Coil::shader_info_t{ "compact_v2.vert", Coil::shader_type_t::VERTEX_SHADER   },
            Coil::shader_info_t{ "compact_v2.frag", Coil::shader_type_t::FRAGMENT_SHADER }
        });
    shader.Compile_And_Link();

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

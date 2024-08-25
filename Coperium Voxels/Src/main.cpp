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

#include "Compact Data/Compact Block/Block.h"

GLenum error;

int main(void) {

    Coil::Logger::init_logger(Coil::LOG_TO_FILE);
    Coil::Initialise_Opengl();
    Coil::Initialise_GLAD();


    Coil::Window window("Hello World", 640, 480);
    window.EnableVsync();
    window.FF_Clockwise();
    window.EnableDepthTest();
    window.EnableCulling();
                    
    // --------------------------------- MESH

    GLfloat* vert_comb = new GLfloat[216 * 5                 * 5 * 5];

    Block block;
    for (uint8_t x = 0; x < 5; x++){
        for (uint8_t y = 0; y < 5; y++){
            for (uint8_t z = 0; z < 5; z++){
                block.Set_All(x, y, z, x, y, z);

                std::unique_ptr<GLfloat[]> vert;
                vert = (block.Generate_Cube_Vertices());

                size_t offset = 216 * (x + y * 5 + z * 25);
                std::copy(vert.get(), vert.get() + 216, vert_comb + offset);
            }
        }

    }

    Coil::Basic_Mesh mesh;
    mesh.Configure_Mesh(
        vert_comb,
        sizeof(GLfloat),
        216*5 *5 *5,
        GL_FLOAT,
        6
    );
    mesh.Add_Vertex_Set(0, 3, 0);
    mesh.Add_Vertex_Set(1, 3, 3);
    mesh.Clean_Mesh();

    // --------------------------------- Shader

    Coil::Shader shader(std::string("Basic"));
    shader.Add_Shaders(
        Coil::shader_list_t{
            Coil::shader_info_t{ "basic.vert", Coil::shader_type_t::VERTEX_SHADER   },
            Coil::shader_info_t{ "basic.frag", Coil::shader_type_t::FRAGMENT_SHADER }
        });
    shader.Compile_And_Link();

    // --------------------------------- CAMERA
    Coil::Fly_Camera camera(window, 0,0, 2);
    camera.Take_Over_All_Input();
    // Main loop
    while (!window.Is_Closed()) {
        int width, height;
        window.Get_Size(width, height);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);

        shader.Use();
        shader.Set_Matrix4("projection", camera.Calc_Projection_Matrix());
        shader.Set_Matrix4("view", camera.Calc_View_Matrix());
        shader.Set_Matrix4("model", model);

        mesh.Draw_Mesh(false);
        window.SwapBuffers();

        // Poll for and process events
        glfwPollEvents();
        camera.Update();

        error = glGetError();       if (error != GL_NO_ERROR) { printf("OpenGL error: %d\n", error); }
    }

    // Clean up and exit
    window.Del();
    glfwTerminate();

    return 0;
}

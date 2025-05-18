#include <COIL/Utility/Initializer.h>
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
#include "Animation Stuff/Game_of_Life.h"
#include "VoxelModel_Loader.h"
#include "WorldData/Chunk_Management/WorldManager.h"
#include "World Creation Functions.h"
#include "WorldData/Chunk_Management/Mesh Generation/Chunk_Mesh.h"
#include "loosingit.h"


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



void renderQuad();

Chunk temp_c = Create_Air_Chunk();

/* ============================================================================
 *                                  MAIN
 * ============================================================================
 */


int main() {
    printf("SOMETING PLEASE\n");
    bool r_was_pressed = false;

    Coil::Logger::init_logger(Coil::LOG_TO_FILE);
    Coil::Initialise_Opengl();
    Coil::Initialise_GLAD();

    Coil::Window window("Voxel Test Case", 1500, 1000);
    setupWindow(window);

    WorldManager world_1(std::string("mount"));
    GameOfLife gol(-val, val, -val, val, { {0, 0}, {0, 1}, {0, 2}, {-1, 1}, {1, 1} }, 100);
    Create_Static_Model_World(world_1);
    

    Coil::Fly_Camera camera(window, 0, 65, 0);
    camera.Take_Over_All_Input();

    // Initialize ImGui
    InitializeImGui(window);

    // FPS and color state
    float   fps = 0.0f;
    int     frames = 0;
    auto    start = std::chrono::high_resolution_clock::now();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    float color[4] = { 0.0f, 1.0f, 0.0f, 1.0f };  // Default to green color

    int width, height;
    window.Get_Size(width, height);

    unsigned int gBuffer;
    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    unsigned int gPosition, gNormal, gColorSpec;

    // - position color buffer
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB10_A2, width, height, 0, GL_RGBA, GL_UNSIGNED_INT_10_10_10_2, NULL);;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

    // - normal color buffer
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB10_A2, width, height, 0, GL_RGBA, GL_UNSIGNED_INT_10_10_10_2, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

    // - color + specular color buffer
    glGenTextures(1, &gColorSpec);
    glBindTexture(GL_TEXTURE_2D, gColorSpec);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB10_A2, width, height, 0, GL_RGBA, GL_UNSIGNED_INT_10_10_10_2, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gColorSpec, 0);

    // - tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);



    Coil::Shader buffer_shader = Coil::Shader("Buffer");
    buffer_shader.Add_Shaders({
        Coil::shader_info_t{"buffer.vert", Coil::shader_type_t::VERTEX_SHADER},
        Coil::shader_info_t{"buffer.frag", Coil::shader_type_t::FRAGMENT_SHADER}
        });
    buffer_shader.Compile_And_Link();

    Coil::Shader deferred_shader = Coil::Shader("Deffered");
    deferred_shader.Add_Shaders({
        Coil::shader_info_t{"deferred.vert", Coil::shader_type_t::VERTEX_SHADER},
        Coil::shader_info_t{"deferred.frag", Coil::shader_type_t::FRAGMENT_SHADER}
        });
    deferred_shader.Compile_And_Link();
    deferred_shader.Use();
    deferred_shader.Set_Int("gPosition", 0);
    deferred_shader.Set_Int("gNormal", 1);
    deferred_shader.Set_Int("gAlbedoSpec", 2);

    //for (int i = 0; i < 100; i++) {
        world_1.Force_Generate_Meshes(camera.Get_Position());
    //}


    GLuint vertex_offset = buffer_shader.Get_Uniform("vertex_offset");
    /* ============================================================================
     *                                  Render
     * ============================================================================
     */
    //Update_Chunks(w, camera);
    //Testing_STUFF(w, camera);
    // Main rendering loop
    //Init_Lightning_Animation();
    std::vector<glm::ivec3> initial_live_voxels = {
        // First glider (front)
        glm::ivec3(1, 0, 0),
        glm::ivec3(2, 0, 1),
        glm::ivec3(0, 0, 2),
        glm::ivec3(1, 0, 2),
        glm::ivec3(2, 0, 2),

    };
    //generate_multiple_density_sweep(world_1, 100);
    //generate_lod_density_sweep(world_1,100);
    int call_counter_a = 0;
    //Generate_All_Chunk_Meshes_LOD_PASS(world_1.Get_World(), camera, false, 50);
    //world_1.Force_Generate_Meshes(camera.Get_Position());
    while (!window.Is_Closed()) {
        
        glm::mat4 model = glm::mat4(1.0f);

        // Use shader and set matrices

        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        buffer_shader.Use();
        buffer_shader.Set_Matrix4("projection", camera.Calc_Projection_Matrix());
        buffer_shader.Set_Matrix4("view", camera.Calc_View_Matrix());
        buffer_shader.Set_Matrix4("model", model);
        //Update_Chunks(world_1, camera);
        //Lightning_Animation(teapot_world);
        
        //gol.Update(world_1, glm::ivec3(-64,0,-64), glm::ivec3(64, 0, 64));
        //UpdateGameOfLife(teapot_world.Get_World(), &temp_c);
        //Generate_All_Chunk_Meshes_LOD_PASS(teapot_world.Get_World(), camera, false, 500);
        gol.Update(world_1, glm::ivec3(-val, 0, -val), glm::ivec3(val, 0, val));
        world_1.Update(camera.Get_Position());
        world_1.Render(buffer_shader, vertex_offset, camera.Get_Position(), camera.Get_Front());

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        deferred_shader.Use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, gColorSpec);
        renderQuad();
        glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
        // blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
        // the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
        // depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
        glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);


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



unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
            // positions        // texture Coords
             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,  // Top Right
             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // Bottom Right
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  // Top Left
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // Bottom Left
        };
        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

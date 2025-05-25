// VoxelApp.cpp
#include <glad/glad.h>
#include "VoxelApp.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Imgui_setup.h"

/* ============================================================================
 * --------------------------- TimingStats Constructor
 * Initializes the timer's starting point.
 * ============================================================================ */
VoxelApp::TimingStats::TimingStats() {
    lastTime = std::chrono::high_resolution_clock::now();
}

/* ============================================================================
 * --------------------------- TimingStats::update
 * Updates FPS, average frame time, and average CPU time.
 * ============================================================================ */
void VoxelApp::TimingStats::update(float cpuTimeMsSample) {
    frames++;
    cpuTimeSumMs += cpuTimeMsSample;
    cpuSamples++;

    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> diff = now - lastTime;

    if (diff.count() >= 1.0f) {
        fps = frames / diff.count();
        avgFrameTimeMs = 1000.0f / fps;
        avgCpuTimeMs = cpuSamples > 0 ? (float)(cpuTimeSumMs / cpuSamples) : 0.0f;

        frames = 0;
        cpuSamples = 0;
        cpuTimeSumMs = 0.0;
        lastTime = now;
    }
}

/* ============================================================================
 * --------------------------- Constructor
 * Sets up the application.
 * ============================================================================ */
VoxelApp::VoxelApp(Coil::Window& win, WorldManager& wm)
    : window(win),
    world(wm),
    camera(win, 0, 65, 0),
    buffer_shader("Buffer"),          // initialised with name
    deferred_shader("Deferred"),
    deferredRenderer(0, 0)            // will be configured in setup_renderer
{
    setup_window();
    setup_camera();
    setup_shaders();
    setup_renderer();
    setup_imgui();
    setup_gpu_query();
}

/* ============================================================================
 * --------------------------- Destructor
 * Performs any necessary cleanup.
 * ============================================================================ */
VoxelApp::~VoxelApp() {
    cleanup();
}

/* ============================================================================
 * --------------------------- setup_window
 * Configures OpenGL window states.
 * ============================================================================ */
void VoxelApp::setup_window() {
    window.FF_Clockwise();
    window.EnableDepthTest();
    window.EnableCulling();
    glfwSwapInterval(0);
}

/* ============================================================================
 * --------------------------- setup_camera
 * Initialises and locks camera input.
 * ============================================================================ */
void VoxelApp::setup_camera() {
    camera.Take_Over_All_Input();
}

/* ============================================================================
 * --------------------------- setup_shaders
 * Compiles and links shaders.
 * ============================================================================ */
void VoxelApp::setup_shaders() {
    buffer_shader.Add_Shaders({
        Coil::shader_info_t{"buffer.vert", Coil::shader_type_t::VERTEX_SHADER},
        Coil::shader_info_t{"buffer.frag", Coil::shader_type_t::FRAGMENT_SHADER}
        });
    buffer_shader.Compile_And_Link();

    deferred_shader.Add_Shaders({
        Coil::shader_info_t{"deferred.vert", Coil::shader_type_t::VERTEX_SHADER},
        Coil::shader_info_t{"deferred.frag", Coil::shader_type_t::FRAGMENT_SHADER}
        });
    deferred_shader.Compile_And_Link();

    vertex_offset = buffer_shader.Get_Uniform("vertex_offset");
}

/* ============================================================================
 * --------------------------- setup_renderer
 * Configures deferred renderer.
 * ============================================================================ */
void VoxelApp::setup_renderer() {
    int width, height;
    window.Get_Size(width, height);
    deferredRenderer.Resize(width, height);
    deferredRenderer.Init(deferred_shader);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

/* ============================================================================
 * --------------------------- setup_imgui
 * Initializes the ImGui interface.
 * ============================================================================ */
void VoxelApp::setup_imgui() {
    InitializeImGui(window);
}

/* ============================================================================
 * --------------------------- setup_gpu_query
 * Prepares OpenGL GPU timing query.
 * ============================================================================ */
void VoxelApp::setup_gpu_query() {
    glGenQueries(1, &queryID);
}

/* ============================================================================
 * --------------------------- render_frame
 * Renders one frame of the application.
 * ============================================================================ */
void VoxelApp::render_frame() {
    glm::mat4 model = glm::mat4(1.0f);

    // -- 1) Prepare G-buffer (not timed) --
    deferredRenderer.BindFramebuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    buffer_shader.Use();
    buffer_shader.Set_Matrix4("projection", camera.Calc_Projection_Matrix());
    buffer_shader.Set_Matrix4("view"      , camera.Calc_View_Matrix());
    buffer_shader.Set_Matrix4("model"     , model);

    // -- 2) Start CPU timer right before update+render --
    auto cpuStart = std::chrono::high_resolution_clock::now();

    //    a) Update world state
    world.Update(camera.Get_Position());

    //    b) Issue draw calls (GPU timing still captured separately)
    glBeginQuery(GL_TIME_ELAPSED, queryID);
    world.Render(buffer_shader, vertex_offset, camera.Get_Position(), camera.Get_Front());
    glEndQuery(GL_TIME_ELAPSED);

    // -- 3) Stop CPU timer immediately after render calls --
    auto cpuEnd = std::chrono::high_resolution_clock::now();
    float cpuTimeMs = std::chrono::duration<float, std::milli>(cpuEnd - cpuStart).count();

    // -- 4) Finish G-buffer pass (not timed) --
    deferredRenderer.UnbindFramebuffer();

    // -- 5) Deferred lighting pass & clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    deferredRenderer.Render(deferred_shader);

    // -- 6) Retrieve GPU time --
    GLuint available = 0;
    while (!available) {
        glGetQueryObjectuiv(queryID, GL_QUERY_RESULT_AVAILABLE, &available);
    }
    GLuint64 gpuTimeNs = 0;
    glGetQueryObjectui64v(queryID, GL_QUERY_RESULT, &gpuTimeNs);
    float gpuTimeMs = gpuTimeNs * 1e-6f;

    // -- 7) Feed stats & UI --
    timingStats.update(cpuTimeMs);
    RenderImGuiFrame(
        timingStats.fps,
        timingStats.avgFrameTimeMs,
        timingStats.avgCpuTimeMs,
        gpuTimeMs
    );

    // -- 8) Present & poll --
    window.SwapBuffers();
    glfwPollEvents();
    camera.Update();
}

/* ============================================================================
 * --------------------------- Run
 * Main loop of the application.
 * ============================================================================ */
void VoxelApp::Run() {
    world.Force_Generate_Meshes(camera.Get_Position());
    while (!window.Is_Closed()) {
        render_frame();
    }
}

/* ============================================================================
 * --------------------------- cleanup
 * Cleans up ImGui and GPU query resources.
 * ============================================================================ */
void VoxelApp::cleanup() {
    CleanupImGui();
    glDeleteQueries(1, &queryID);
}

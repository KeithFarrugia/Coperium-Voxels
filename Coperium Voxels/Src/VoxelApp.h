#pragma once
#ifndef VOXEL_APP_H
#define VOXEL_APP_H

#include <COIL/Window/Window.h>
#include <COIL/Shaders/Shader.h>
#include <COIL/Camera/Fly Camera/Fly_Camera.h>

#include "WorldData/Chunk_Management/WorldManager.h"
#include "DeferredRenderer.h"

class VoxelApp {
public:
    VoxelApp(Coil::Window& window, WorldManager& world);
    ~VoxelApp();

    void Run();

private:
    Coil::Window& window;
    WorldManager& world;

    Coil::Fly_Camera camera;
    DeferredRenderer deferredRenderer;
    Coil::Shader buffer_shader;
    Coil::Shader deferred_shader;
    GLuint vertex_offset;
    GLuint queryID;

    struct TimingStats {
        int frames = 0;
        float fps = 0.0f;
        float avgFrameTimeMs = 0.0f;

        double cpuTimeSumMs = 0.0;
        int cpuSamples = 0;
        float avgCpuTimeMs = 0.0f;

        double gpuTimeSumMs = 0.0;
        int gpuSamples = 0;
        float avgGpuTimeMs = 0.0f;

        std::chrono::high_resolution_clock::time_point lastTime;

        TimingStats();
        void update(float cpuTimeMsSample, float gpuTimeMsSample);
    } timingStats;

    void setup_window();
    void setup_shaders();
    void setup_camera();
    void setup_renderer();
    void setup_imgui();
    void setup_gpu_query();
    void render_frame();
    void cleanup();
};

#endif // !VOXEL_APP_H

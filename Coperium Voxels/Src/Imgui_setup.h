#pragma once
#ifndef IMGUI_SETUP_H
#define IMGUI_SETUP_H

#include <COIL/Window/Window.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>

void InitializeImGui(Coil::Window& window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.Get_Window(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    io.WantCaptureMouse = true;
    io.WantCaptureKeyboard = false;
}

void RenderImGuiFrame(float fps, float avgFrameTimeMs, float avgCpuTimeMs, float gpuTimeMs) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::Begin("Performance Stats", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_AlwaysAutoResize);

    // Use fixed-width fields: %-12s left-justified label in 12 chars,
    // %8.2f right-justified numeric in 8 chars with 2 decimal places.
    ImGui::Text("%-12s %8.1f   ", "FPS:", fps);
    ImGui::Text("%-12s %8.2f ms", "Frame Time:", avgFrameTimeMs);
    ImGui::Text("%-12s %8.2f ms", "CPU Update:", avgCpuTimeMs);
    ImGui::Text("%-12s %8.2f ms", "GPU Time:", gpuTimeMs);

    ImGui::End();
    ImGui::Render();

    if (auto draw_data = ImGui::GetDrawData())
        ImGui_ImplOpenGL3_RenderDrawData(draw_data);
}




void CleanupImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

#endif // IMGUI_SETUP_H

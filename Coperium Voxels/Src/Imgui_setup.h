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

    ImGui::SetNextWindowPos(ImVec2(10, 10));  // Top-left corner
    ImGui::Begin("Performance Stats", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("FPS: %.1f", fps);
    ImGui::Text("Frame Time: %.2f ms", avgFrameTimeMs);
    ImGui::Text("CPU Update Time: %.2f ms (avg)", avgCpuTimeMs);
    ImGui::Text("GPU Time: %.2f ms", gpuTimeMs);
    ImGui::End();

    ImGui::Render();
    ImDrawData* draw_data = ImGui::GetDrawData();
    if (draw_data != nullptr) {
        ImGui_ImplOpenGL3_RenderDrawData(draw_data);
    }
}


void CleanupImGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

#endif // IMGUI_SETUP_H

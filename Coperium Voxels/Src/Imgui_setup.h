#pragma once
#ifndef IMGUI_SETUP_H
#define IMGUI_SETUP_H

#include <COIL/Window/Window.h>
#include <COIL/Shaders/Shader.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>


void InitializeImGui(Coil::Window& window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    // Initialize ImGui bindings for GLFW and OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window.Get_Window(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    io.WantCaptureMouse = true;
    io.WantCaptureKeyboard = false;
}

void RenderImGuiFrame(float fps, float color[4]) {
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
    //ImGui::SetNextWindowPos(ImVec2(10, 50));  // Below the FPS counter
    //ImGui::Begin("Color Picker", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    //// ImGui ColorPicker (with color wheel image)
    //ImGui::ColorPicker4("Pick a Color", color, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_PickerHueWheel);

    ImGui::End();

    // Render ImGui
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
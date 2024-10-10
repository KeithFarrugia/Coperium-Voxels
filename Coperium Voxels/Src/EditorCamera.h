#pragma once
#ifndef EDITOR_CAMERA_H
#define EDITOR_CAMERA_H

#include <COIL/Camera/Fly Camera/Fly_Camera.h>
#include "Compact Data/World Data/World/World.h"
#include "Compact Data/World Data/World_Mesh.h"
class EditorCamera : public Coil::Fly_Camera {
public:
    EditorCamera(Coil::Window& window, World& world)
        : Fly_Camera(window), world(world) {
        mouse_press = false;
    }

    EditorCamera(Coil::Window& window, World& world, GLfloat Pos_x, GLfloat Pos_y, GLfloat Pos_z)
        : Fly_Camera(window, Pos_x, Pos_y, Pos_z), world(world) {}

    // Override the mouse button handler to enable block placement/removal
    void Process_Mouse_Button(int button, int action, int mods) override;

private:
    std::tuple<bool, glm::vec3, glm::vec3> Raycast(glm::vec3 origin, glm::vec3 direction, float maxLength);
    bool mouse_press;
    World& world;  // Reference to the world where blocks will be placed/removed
};

#endif // !EDITOR_CAMERA_H

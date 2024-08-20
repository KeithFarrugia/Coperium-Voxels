#pragma once
#ifndef COIL_INITIALISER_H
#define COIL_INITIALISER_H

// --------------------------------- External Includes
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <IMGUI/imgui.h>

// --------------------------------- Internal Includes
#include "Logger/Logger.h"

namespace Coil {
/* ============================================================================
 * --------------------------- Initialise OpenGL
 * - Initialise GLFW
 * - Initialise Context
 *      - Get a floating point number
 *      - Extract major version (e.g., 3.4 -> 3)
 *      - Extract minor version (e.g., 3.4 -> 4)
 * ============================================================================
 */
 
inline bool Initialise_Opengl(float version = 4.4f) {

    unsigned int major_version =
        static_cast<unsigned int> (version);

    unsigned int minor_version =
        static_cast<unsigned int> ((version - major_version) * 10);

    if (!glfwInit()) {
        Logger::log("OpenGL Initialiser",
                    "Failed to Initialidse GLFW -> Terminating");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return true;
}

/* ============================================================================
 * --------------------------- Initialise GLAD
 * - Initialise GLAD for OpenGL function loading.
 * - Create a temporary GLFW window to set up an OpenGL context.
 * - Make the temporary context current for GLAD initialization.
 * - Destroy the temporary window and terminate GLFW.
 *
 * ------ Details ------
 * This function is responsible for loading the OpenGL function pointers
 * using GLAD. It creates a hidden temporary GLFW window to provide a
 * valid OpenGL context, which is necessary for GLAD to retrieve the
 * function pointers. After initializing GLAD, the temporary window is
 * destroyed, and GLFW is terminated.
 *
 * ------ Returns ------
 * true:  If GLAD initialization is successful.
 * false: If there is an error during initialization.
 * ============================================================================
 */
inline bool Initialise_GLAD() {
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow* tempWindow = glfwCreateWindow(
        1, 1, 
        "Temp Window", 
        nullptr, nullptr);
    if (!tempWindow) {
        Logger::log(
            "Glad Initialiser",
            "Failed to create temporary GLFW window");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(tempWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger::log(
            "Glad Initialiser",
            "Failed to Initialise glad");
        glfwDestroyWindow(tempWindow);
        glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
        glfwTerminate();
        return false;
    }

    // Clean up
    glfwDestroyWindow(tempWindow);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    return true;
}

}
#endif // !COIL_INITIALISER_H

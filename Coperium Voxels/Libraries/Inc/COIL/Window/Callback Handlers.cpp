#include "Window.h"

namespace Coil {

/* ============================================================================
 * ---------------------------- Size Callback
 * Called when the window is resized.
 * 
 * ------ Parameters ------
 * win:         The GLFW window that was resized.
 * width:       The new width of the window.
 * height:      The new height of the window.
 * ============================================================================
 */
void Window::Window_Size_Callback(
    GLFWwindow* win, int width, int height
){
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
    window->MakeContext();
    if (window) {
        for (const auto& callback : window->size_cf) {
            callback(*window);
        }
    }
}

/* ============================================================================
 * ------------------------ Framebuffer Size Callback
 * Called when the framebuffer of the window is resized.
 * 
 * ------ Parameters ------
 * win:         The GLFW window whose framebuffer was resized.
 * width:       The new width of the framebuffer.
 * height:      The new height of the framebuffer.
 * ============================================================================
 */
void Window::Window_Framebuffer_Size_Callback(
    GLFWwindow* win, int width, int height
){
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
    window->MakeContext();
    if (width <= 0 || height <= 0) {return;}
    glViewport(0, 0, width, height);
    if (window) {
        for (const auto& callback : window->frame_cf) {
            callback(*window);
        }
    }
}

/* ============================================================================
 * ---------------------------- Close Callback
 * Called when the window is about to close.
 * 
 * ------ Parameters ------
 * win:         The GLFW window that is about to close.
 * ============================================================================
 */
void Window::Window_Close_Callback(
    GLFWwindow* win
){
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win)); 
    if (window) {
        for (const auto& callback : window->close_cf) {
            callback(*window);
        }
    }
}

/* ============================================================================
 * -------------------------- Refresh Callback
 * Called when the window needs to be redrawn.
 * 
 * ------ Parameters ------
 * win:         The GLFW window that needs to be redrawn.
 * ============================================================================
 */
void Window::Window_Refresh_Callback(
    GLFWwindow* win
){
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
    window->MakeContext();
    if (window) {
        for (const auto& callback : window->refresh_cf) {
            callback(*window);
        }
    }
}

/* ============================================================================
 * ---------------------------- Focus Callback
 * Called when the window gains or loses focus.
 * 
 * ------ Parameters ------
 * win:         The GLFW window that gained or lost focus.
 * focused:     Whether the window is focused (1) or not (0).
 * ============================================================================
 */
void Window::Window_Focus_Callback(
    GLFWwindow* win, int focused
){
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
    window->MakeContext();

    if (window) {
        for (const auto& callback : window->focus_cf) {
            callback(*window);
        }
    }
}

/* ============================================================================
 * ---------------------------- Iconify Callback
 * Called when the window is minimized or restored.
 * 
 * ------ Parameters ------
 * win:         The GLFW window that was minimized or restored.
 * iconified:   Whether the window was minimized (1) or restored (0).
 * ============================================================================
 */
void Window::Window_Iconify_Callback(
    GLFWwindow* win, int iconified
){
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
    window->MakeContext();
    if (window) {
        for (const auto& callback : window->iconify_cf) {
            callback(*window);
        }
    }
}

/* ============================================================================
 * ----------------------------- Position Callback
 * Called when the window is moved.
 * 
 * ------ Parameters ------
 * win:         The GLFW window that was moved.
 * xpos:        The new x position of the window.
 * ypos:        The new y position of the window.
 * ============================================================================
 */
void Window::Window_Pos_Callback(
    GLFWwindow* win, int xpos, int ypos
){
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
    window->MakeContext();
    if (window) {
        for (const auto& callback : window->position_cf) {
            callback(*window);
        }
    }
}

/* ============================================================================
 * -------------------------- Content Scale Callback
 * Called when the content scale of the window changes.
 * 
 * ------ Parameters ------
 * win:         The GLFW window whose content scale changed.
 * xscale:      The new horizontal content scale.
 * yscale:      The new vertical content scale.
 * ============================================================================
 */
void Window::Window_Content_Scale_Callback(
    GLFWwindow* win, float xscale, float yscale
){
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
    window->MakeContext();
    if (window) {
        for (const auto& callback : window->content_cf) {
            callback(*window);
        }
    }
}

};
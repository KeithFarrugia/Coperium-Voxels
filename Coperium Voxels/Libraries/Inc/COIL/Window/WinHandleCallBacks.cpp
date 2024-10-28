#include "Window.h"

namespace Coil {

/* ============================================================================
 * ---------------------------- Size CB
 * Called when the window is resized.
 * 
 * ------ Parameters ------
 * win:         The GLFW window that was resized.
 * width:       The new width of the window.
 * height:      The new height of the window.
 * ============================================================================
 */
void Window::Window_Size_CB(
    GLFWwindow* win, int width, int height
){
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));

    if (window != nullptr) {
        
        if (window->previous_cb.window_size_cb  != nullptr &&
            window->allow_cb_chain              == true    ){

            window->previous_cb.window_size_cb(win, width, height);
        }

        for (const auto& callback : window->size_cf) {
            callback(*window);
        }
    }
}

/* ============================================================================
 * ------------------------ Framebuffer Size CB
 * Called when the framebuffer of the window is resized.
 * 
 * ------ Parameters ------
 * win:         The GLFW window whose framebuffer was resized.
 * width:       The new width of the framebuffer.
 * height:      The new height of the framebuffer.
 * ============================================================================
 */
void Window::Window_Framebuffer_Size_CB(
    GLFWwindow* win, int width, int height
){
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));

    if (width <= 0 || height <= 0) {return;}
    
    if (window != nullptr) {
        Window* pre = window->MakeContext();
        glViewport(0, 0, width, height);
        window->MakeContext(pre);

        if (window->previous_cb.framebuffer_size_cb != nullptr &&
            window->allow_cb_chain                  == true    ){

            window->previous_cb.framebuffer_size_cb (win, width, height);
        }

        for (const auto& callback : window->frame_cf) {
            callback(*window);
        }
    }
}

/* ============================================================================
 * ---------------------------- Close CB
 * Called when the window is about to close.
 * 
 * ------ Parameters ------
 * win:         The GLFW window that is about to close.
 * ============================================================================
 */
void Window::Window_Close_CB(
    GLFWwindow* win
){
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win)); 

    if (window != nullptr) {
        if (window->previous_cb.window_close_cb != nullptr  &&
            window->allow_cb_chain              == true     ){

            window->previous_cb.window_close_cb(win);
        }

        for (const auto& callback : window->close_cf) {
            callback(*window);
        }
    }
}

/* ============================================================================
 * -------------------------- Refresh CB
 * Called when the window needs to be redrawn.
 * 
 * ------ Parameters ------
 * win:         The GLFW window that needs to be redrawn.
 * ============================================================================
 */
void Window::Window_Refresh_CB(
    GLFWwindow* win
){
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));

    if (window != nullptr) {

        if (window->previous_cb.window_refresh_cb   != nullptr  &&
            window->allow_cb_chain                  == true     ){

            window->previous_cb.window_refresh_cb(win);
        }

        for (const auto& callback : window->refresh_cf) {
            callback(*window);
        }
    }
}

/* ============================================================================
 * ---------------------------- Focus CB
 * Called when the window gains or loses focus.
 * 
 * ------ Parameters ------
 * win:         The GLFW window that gained or lost focus.
 * focused:     Whether the window is focused (1) or not (0).
 * ============================================================================
 */
void Window::Window_Focus_CB(
    GLFWwindow* win, int focused
){
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));

    if (window != nullptr) {

        if (window->previous_cb.window_focus_cb != nullptr  &&
            window->allow_cb_chain              == true     ){

            window->previous_cb.window_focus_cb(win, focused);
        }

        for (const auto& callback : window->focus_cf) {
            callback(*window);
        }
    }
}

/* ============================================================================
 * ---------------------------- Iconify CB
 * Called when the window is minimized or restored.
 * 
 * ------ Parameters ------
 * win:         The GLFW window that was minimized or restored.
 * iconified:   Whether the window was minimized (1) or restored (0).
 * ============================================================================
 */
void Window::Window_Iconify_CB(
    GLFWwindow* win, int iconified
){
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));

    if (window != nullptr) {

        if (window->previous_cb.window_iconify_cb   != nullptr  &&
            window->allow_cb_chain                  == true     ){

            window->previous_cb.window_iconify_cb(win, iconified);
        }

        for (const auto& callback : window->iconify_cf) {
            callback(*window);
        }
    }
}
/* ============================================================================
 * ---------------------------- Maximise CB
 * Called when the window is maximised or restored.
 *
 * ------ Parameters ------
 * win:         The GLFW window that was maximised or restored.
 * maximised:   Whether the window was maximised (1) or restored (0).
 * ============================================================================
 */
void Window::Window_Maximise_CB(
    GLFWwindow* win, int maximised
){
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));

    if (window != nullptr) {

        if (window->previous_cb.window_maximised_cb != nullptr &&
            window->allow_cb_chain == true) {

            window->previous_cb.window_maximised_cb(win, maximised);
        }

        for (const auto& callback : window->maximise_cf) {
            callback(*window);
        }
    }
}

/* ============================================================================
 * ----------------------------- Position CB
 * Called when the window is moved.
 * 
 * ------ Parameters ------
 * win:         The GLFW window that was moved.
 * xpos:        The new x position of the window.
 * ypos:        The new y position of the window.
 * ============================================================================
 */
void Window::Window_Pos_CB(
    GLFWwindow* win, int xpos, int ypos
){
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
    window->MakeContext();
    if (window != nullptr) {

        if (window->previous_cb.window_pos_cb   != nullptr  &&
            window->allow_cb_chain              == true     ){

            window->previous_cb.window_pos_cb(win, xpos, ypos);
        }

        for (const auto& callback : window->position_cf) {
            callback(*window);
        }
    }
}

/* ============================================================================
 * -------------------------- Content Scale CB
 * Called when the content scale of the window changes.
 * 
 * ------ Parameters ------
 * win:         The GLFW window whose content scale changed.
 * xscale:      The new horizontal content scale.
 * yscale:      The new vertical content scale.
 * ============================================================================
 */
void Window::Window_Content_Scale_CB(
    GLFWwindow* win, float xscale, float yscale
){
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(win));
    window->MakeContext();
    if (window != nullptr) {

        if (window->previous_cb.content_scale_cb    != nullptr  &&
            window->allow_cb_chain                  == true     ){

            window->previous_cb.content_scale_cb(win, xscale, yscale);
        }

        for (const auto& callback : window->content_cf) {
            callback(*window);
        }
    }
}

};
#include "Window.h"

namespace Coil {

/* ============================================================================
 * --------------------------- Window Constructor
 * Initializes a new GLFW window with a default size, title, and no monitor.
 * Sets the user pointer to this instance for use in static callbacks.
 * ============================================================================
 */
Window::Window() {
    Window::Window("Default Title", 800, 600);
}

/* ============================================================================
 * --------------------------- Window Constructor
 * Initializes a new GLFW window with a given default size, title, 
 * and no monitor.
 * Sets the user pointer to this instance for use in static callbacks.
 * ============================================================================
 */
Window::Window(
    const std::string name,
    const int w, const int h
){
    windowed_x = 0;
    windowed_y = 0;

    windowed_w = 0;
    windowed_h = 0;

    window = glfwCreateWindow(
        w, h,
        name.c_str(),
        nullptr, nullptr
    ); 

    if (!window) {
        Logger::log(
            "Window",
            "Error : Failed to creat GLFW window"
        );
        return;
    }

    glfwSetWindowUserPointer(window, this);

    Focus();
    MakeContext();
    Configure_CallBacks();
}

/* ============================================================================
 * --------------------------- ~Window
 * Makes sure to delete the Window
 * ============================================================================
 */
Window::~Window() {
    Del();
}


/* ============================================================================
 * --------------------------- Configure_CallBacks
 * Sets GLFW callback functions for various window events.
 * This includes callbacks for size, framebuffer size, close, refresh,
 * focus, iconify, position, and content scale.
 * ============================================================================
 */
void Window::Configure_CallBacks() {
    glfwSetWindowSizeCallback
    (window, Window_Size_Callback);
    glfwSetFramebufferSizeCallback
    (window, Window_Framebuffer_Size_Callback);
    glfwSetWindowCloseCallback
    (window, Window_Close_Callback);
    glfwSetWindowRefreshCallback
    (window, Window_Refresh_Callback);
    glfwSetWindowFocusCallback
    (window, Window_Focus_Callback);
    glfwSetWindowIconifyCallback
    (window, Window_Iconify_Callback);
    glfwSetWindowPosCallback
    (window, Window_Pos_Callback);
    glfwSetWindowContentScaleCallback
    (window, Window_Content_Scale_Callback);
}

/* ============================================================================
 * --------------------------- Del
 * Destroys the GLFW window and cleans up any associated resources.
 * ============================================================================
 */
void Window::Del() {
    glfwDestroyWindow(window);
}

/* ============================================================================
 * --------------------------- Show
 * Makes the window visible.
 * ============================================================================
 */
void Window::Show() {
    glfwShowWindow(window);
}

/* ============================================================================
 * --------------------------- Hide
 * Hides the window.
 * ============================================================================
 */
void Window::Hide() {
    glfwHideWindow(window);
}

/* ============================================================================
 * --------------------------- Iconify
 * Minimizes the window to the taskbar or dock.
 * ============================================================================
 */
void Window::Iconify() {
    glfwIconifyWindow(window);
}

/* ============================================================================
 * --------------------------- Restore
 * Restores the window from its minimized state.
 * ============================================================================
 */
void Window::Restore() {
    glfwRestoreWindow(window);
}

/* ============================================================================
 * --------------------------- Maximise
 * Maximizes the window to occupy the entire screen.
 * ============================================================================
 */
void Window::Maximise() {
    glfwMaximizeWindow(window);
}

/* ============================================================================
 * --------------------------- Focus
 * Brings the window to the foreground and gives it focus.
 * ============================================================================
 */
void Window::Focus() {
    glfwFocusWindow(window);
}

/* ============================================================================
 * --------------------------- RequestAttention
 * Requests attention for the window, typically causing it to flash or 
 * otherwise alert the user.
 * ============================================================================
 */
void Window::RequestAttention() {
    glfwRequestWindowAttention(window);
}

/* ============================================================================
 * --------------------------- SwapBuffers
 * Swaps the current buffers
 * ============================================================================
 */
void Window::SwapBuffers() {
    glfwSwapBuffers(window);
}

/* ============================================================================
 * --------------------------- EnableVsync
 * Enables Vsync
 * ============================================================================
 */
void Window::EnableVsync() {
    MakeContext();
    glfwSwapInterval(1);
}

/* ============================================================================
 * --------------------------- DisableVsync
 * Disable Vsync
 * ============================================================================
 */
void Window::DisableVsync() {
    MakeContext();
    glfwSwapInterval(0);
}

/* ============================================================================
 * --------------------------- EnableDepthTest
 * Enables depth testing in OpenGL, which allows for proper rendering
 * of objects based on their depth values.
 * ============================================================================
 */
void Window::EnableDepthTest() {
    MakeContext();
    glEnable(GL_DEPTH_TEST);
}

/* ============================================================================
 * --------------------------- DisableDepthTest
 * Disables depth testing in OpenGL. This can be used when depth testing
 * is not required or to avoid depth-based rendering issues.
 * ============================================================================
 */
void Window::DisableDepthTest() {
    MakeContext();
    glDisable(GL_DEPTH_TEST);
}

/* ============================================================================
 * --------------------------- EnableCulling
 * Enables face culling in OpenGL. This causes the GPU to ignore rendering
 * of faces that are considered to be back-facing, improving performance.
 * ============================================================================
 */
void Window::EnableCulling() {
    MakeContext();
    glEnable(GL_CULL_FACE);
}

/* ============================================================================
 * --------------------------- DisableCulling
 * Disables face culling in OpenGL. This means that no faces will be ignored,
 * and all rendered faces will be processed by the GPU, which may reduce performance.
 * ============================================================================
 */
void Window::DisableCulling() {
    MakeContext();
    glDisable(GL_CULL_FACE);
}

/* ============================================================================
 * --------------------------- FF_Clockwise
 * Sets the front face winding order to clockwise. This determines which
 * direction is considered the "front" face of polygons in OpenGL.
 * ============================================================================
 */
void Window::FF_Clockwise() {
    MakeContext();
    glFrontFace(GL_CW);
}

/* ============================================================================
 * --------------------------- FF_UntiClockwise
 * Sets the front face winding order to counter-clockwise. This is the
 * default winding order used by many OpenGL applications to determine
 * which direction is considered the "front" face of polygons.
 * ============================================================================
 */
void Window::FF_UntiClockwise() {
    MakeContext();
    glFrontFace(GL_CCW);
}


/* ============================================================================
 * --------------------------- SwapBuffers
 * Swaps the current buffers
 * ============================================================================
 */
void Window::MakeContext() {
    glfwMakeContextCurrent(window);
}
/* ============================================================================
 * --------------------------- FullScreen
 * Switches the window to fullscreen mode.
 * Stores the current window position and size for later restoration.
 * ============================================================================
 */
void Window::FullScreen() {
    // Store the current window position and size
    glfwGetWindowPos    (window, &windowed_x, &windowed_y);
    glfwGetWindowSize   (window, &windowed_w, &windowed_h);

    // Get the primary monitor and its video mode
    GLFWmonitor* monitor    = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    // Switch to fullscreen
    glfwSetWindowMonitor(
        window, 
        monitor, 
        0, 
        0, 
        mode->width, 
        mode->height, 
        mode->refreshRate
    );

    // Trigger the size and position callbacks
    Window_Size_Callback(window, mode->width, mode->height);
    Window_Pos_Callback(window, 0, 0);
}

/* ============================================================================
 * --------------------------- Windowed
 * Switches the window back to windowed mode.
 * Restores the window to its previous position and size.
 * ============================================================================
 */
void Window::Windowed() {
    // Switch back to windowed mode
    glfwSetWindowMonitor(
        window, 
        nullptr, 
        windowed_x, 
        windowed_y, 
        windowed_w, 
        windowed_h, 
        0
    );

    // Trigger the size and position callbacks
    Window_Size_Callback(window, windowed_w, windowed_h);
    Window_Pos_Callback(window, windowed_x, windowed_y);
}

}

#include "Window.h"

namespace Coil {

Window* Window::current_context =  nullptr;
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

template<typename cb_t>
cb_t Window::SetCallback(
    cb_t& previous, cb_t newCallback,
    cb_t(*setFunction)(GLFWwindow*, cb_t)
){
    if (previous != newCallback) {
        previous = setFunction(window, newCallback);
    }
    return previous;
}

void Window::Configure_CallBacks() {
    previous_cb.window_size_cb      = SetCallback(previous_cb.window_size_cb, 
                                        Window_Size_CB          , glfwSetWindowSizeCallback);

    previous_cb.framebuffer_size_cb = SetCallback(previous_cb.framebuffer_size_cb,
                                        Window_Framebuffer_Size_CB, glfwSetFramebufferSizeCallback);

    previous_cb.window_close_cb     = SetCallback(previous_cb.window_close_cb,
                                        Window_Close_CB         , glfwSetWindowCloseCallback);

    previous_cb.window_refresh_cb   = SetCallback(previous_cb.window_refresh_cb, 
                                        Window_Refresh_CB       , glfwSetWindowRefreshCallback);

    previous_cb.window_focus_cb     = SetCallback(previous_cb.window_focus_cb, 
                                        Window_Focus_CB         , glfwSetWindowFocusCallback);

    previous_cb.window_iconify_cb   = SetCallback(previous_cb.window_iconify_cb, 
                                        Window_Iconify_CB       , glfwSetWindowIconifyCallback);
    
    previous_cb.window_maximised_cb = SetCallback(previous_cb.window_maximised_cb, 
                                        Window_Maximise_CB      , glfwSetWindowMaximizeCallback);

    previous_cb.window_pos_cb       = SetCallback(previous_cb.window_pos_cb, 
                                        Window_Pos_CB           , glfwSetWindowPosCallback);

    previous_cb.content_scale_cb    = SetCallback(previous_cb.content_scale_cb, 
                                        Window_Content_Scale_CB , glfwSetWindowContentScaleCallback);
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
    Window* pre = MakeContext();
    glfwSwapInterval(1);
    MakeContext(pre);
}

/* ============================================================================
 * --------------------------- DisableVsync
 * Disable Vsync
 * ============================================================================
 */
void Window::DisableVsync() {
    Window* pre = MakeContext();
    glfwSwapInterval(0);
    MakeContext(pre);
}

/* ============================================================================
 * --------------------------- EnableDepthTest
 * Enables depth testing in OpenGL, which allows for proper rendering
 * of objects based on their depth values.
 * ============================================================================
 */
void Window::EnableDepthTest() {
    Window* pre = MakeContext();
    glEnable(GL_DEPTH_TEST);
    MakeContext(pre);
}

/* ============================================================================
 * --------------------------- DisableDepthTest
 * Disables depth testing in OpenGL. This can be used when depth testing
 * is not required or to avoid depth-based rendering issues.
 * ============================================================================
 */
void Window::DisableDepthTest() {
    Window* pre = MakeContext();
    glDisable(GL_DEPTH_TEST);
    MakeContext(pre);
}

/* ============================================================================
 * --------------------------- EnableCulling
 * Enables face culling in OpenGL. This causes the GPU to ignore rendering
 * of faces that are considered to be back-facing, improving performance.
 * ============================================================================
 */
void Window::EnableCulling() {
    Window* pre = MakeContext();
    glEnable(GL_CULL_FACE);
    MakeContext(pre);
}

/* ============================================================================
 * --------------------------- DisableCulling
 * Disables face culling in OpenGL. This means that no faces will be ignored,
 * and all rendered faces will be processed by the GPU, which may reduce performance.
 * ============================================================================
 */
void Window::DisableCulling() {
    Window* pre = MakeContext();
    glDisable(GL_CULL_FACE);
    MakeContext(pre);
}

/* ============================================================================
 * --------------------------- FF_Clockwise
 * Sets the front face winding order to clockwise. This determines which
 * direction is considered the "front" face of polygons in OpenGL.
 * ============================================================================
 */
void Window::FF_Clockwise() {
    Window* pre = MakeContext();
    glFrontFace(GL_CW);
    MakeContext(pre);
}

/* ============================================================================
 * --------------------------- FF_UntiClockwise
 * Sets the front face winding order to counter-clockwise. This is the
 * default winding order used by many OpenGL applications to determine
 * which direction is considered the "front" face of polygons.
 * ============================================================================
 */
void Window::FF_UntiClockwise() {
    Window* pre = MakeContext();
    glFrontFace(GL_CCW);
    MakeContext(pre);
}

/* ============================================================================
 * --------------------------- FullScreen
 * Switches the window to fullscreen mode.
 * Stores the current window position and size for later restoration.
 * ============================================================================
 */
void Window::FullScreen() {
    Get_Position    (windowed_x , windowed_y);
    Get_Size        (windowed_w , windowed_h);

    GLFWmonitor* monitor;  Get_Monitor(&monitor);;
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    // Switch to fullscreen
    Set_Monitor(
        monitor, 
        0, 
        0, 
        mode->width, 
        mode->height, 
        mode->refreshRate
    );

    Window_Size_CB(window, mode->width, mode->height);
    Window_Pos_CB(window, 0, 0);
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
    Window_Size_CB(window, windowed_w, windowed_h);
    Window_Pos_CB(window, windowed_x, windowed_y);
}


/* ============================================================================
 * --------------------------- MakeContext
 * Makes the window the current context
 * ============================================================================
 */
Window* Window::MakeContext() {
    w_mt.lock();
    
    Window* pre_context = current_context;
    glfwMakeContextCurrent(this->window);
    current_context = this;

    w_mt.unlock();
    
    return pre_context;
}

/* ============================================================================
 * --------------------------- MakeContext
 * 
 * ============================================================================
 */
Window* Window::MakeContext( Window* win ){
    w_mt.lock();

    Window* pre_context = current_context;
    glfwMakeContextCurrent(win->window);
    current_context = this;

    w_mt.unlock();

    return pre_context;
}
}

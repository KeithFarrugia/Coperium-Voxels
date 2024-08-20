#include "Window.h"

namespace Coil {


/* ============================================================================
 * --------------------------- Get Window
 * Returns the window object
 * ============================================================================
 */
GLFWwindow* Window::Get_Window(){
    return window;
}

/* ============================================================================
 * --------------------------- Get_Position
 * Retrieves the current position of the window.
 * The position is stored in the provided x and y parameters.
 * 
 * ------ Parameters ------
 * x: Reference to an integer where the x-coordinate will be stored.
 * y: Reference to an integer where the y-coordinate will be stored.
 * ============================================================================
 */
void Window::Get_Position(int& x, int& y) const {
    glfwGetWindowPos(window, &x, &y);
}

/* ============================================================================
 * --------------------------- Get_Size
 * Retrieves the current size of the window.
 * The size is stored in the provided width and height parameters.
 * 
 * ------ Parameters ------
 * w: Reference to an integer where the width will be stored.
 * h: Reference to an integer where the height will be stored.
 * ============================================================================
 */
void Window::Get_Size(int& w, int& h) const {
    glfwGetWindowSize(window, &w, &h);
}

/* ============================================================================
 * --------------------------- Get_FrameBufferSize
 * Retrieves the size of the window's framebuffer.
 * The framebuffer size is stored in the provided width and height parameters.
 * 
 * ------ Parameters ------
 * w: Reference to an integer where the framebuffer width will be stored.
 * h: Reference to an integer where the framebuffer height will be stored.
 * ============================================================================
 */
void Window::Get_FrameBufferSize(int& w, int& h) const {
    glfwGetFramebufferSize(window, &w, &h);
}

/* ============================================================================
 * --------------------------- Get_FrameSize
 * Retrieves the size of the window's frame.
 * The frame size is stored in the provided left, right, top, and bottom parameters.
 * 
 * ------ Parameters ------
 * l: Reference to an integer where the left frame size will be stored.
 * r: Reference to an integer where the right frame size will be stored.
 * t: Reference to an integer where the top frame size will be stored.
 * b: Reference to an integer where the bottom frame size will be stored.
 * ============================================================================
 */
void Window::Get_FrameSize(int& l, int& r, int& t, int& b) const {
    glfwGetWindowFrameSize(window, &l, &t, &r, &b);
}

/* ============================================================================
 * --------------------------- Get_ContentScale
 * Retrieves the content scale of the window.
 * The content scale factors are stored in the provided x_scale and y_scale parameters.
 * 
 * ------ Parameters ------
 * x_scale: Reference to a float where the x-scale factor will be stored.
 * y_scale: Reference to a float where the y-scale factor will be stored.
 * ============================================================================
 */
void Window::Get_ContentScale(float& x_scale, float& y_scale) const {
    glfwGetWindowContentScale(window, &x_scale, &y_scale);
}

/* ============================================================================
 * --------------------------- Get_Opacity
 * Retrieves the opacity of the window.
 * The opacity value is stored in the provided o parameter.
 * 
 * ------ Parameters ------
 * o: Reference to a float where the opacity will be stored.
 * ============================================================================
 */
void Window::Get_Opacity(float& o) const {
     o = glfwGetWindowOpacity(window);
}

/* ============================================================================
 * --------------------------- Get_Monitor
 * Retrieves the monitor associated with the window if it is in fullscreen mode.
 * The monitor pointer is stored in the provided monitor parameter.
 * 
 * ------ Parameters ------
 * monitor: Pointer to a GLFWmonitor pointer where the monitor will be stored.
 * ============================================================================
 */
void Window::Get_Monitor(GLFWmonitor** monitor) const {
    *monitor = glfwGetWindowMonitor(window);
}

/* ============================================================================
 * --------------------------- Get_Attribute
 * Retrieves a specific attribute of the window.
 * The attribute value is stored in the provided result parameter.
 * 
 * ------ Parameters ------
 * attrib: The attribute to retrieve.
 * result: Reference to an integer where the attribute value will be stored.
 * ============================================================================
 */
void Window::Get_Attribute(const int attrib, int& result) const {
    result = glfwGetWindowAttrib(window, attrib);
}

/* ============================================================================
 * --------------------------- Get_RefreshRate
 * Retrieves the refresh rate of the monitor if the window is in fullscreen mode.
 * The refresh rate is stored in the provided rf parameter.
 * 
 * ------ Parameters ------
 * rf: Reference to an integer where the refresh rate will be stored.
 * ============================================================================
 */
void Window::Get_RefreshRate(int& rf) const {
    if (Is_FullScreen()) {
        GLFWmonitor* monitor = glfwGetWindowMonitor(window);
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        rf = mode->refreshRate;
    } else {
        rf = 0; // Not in fullscreen mode
    }
}

}

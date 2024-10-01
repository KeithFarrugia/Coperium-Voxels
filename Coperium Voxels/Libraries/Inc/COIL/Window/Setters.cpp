#include "Window.h"

namespace Coil {

/* ============================================================================
 * --------------------------- Set_Title
 * Sets the title of the window.
 * The title is displayed in the window's title bar.
 * 
 * ------ Parameters ------
 * title: A string representing the new title for the window.
 * ============================================================================
 */
void Window::Set_Title(std::string title) {
    glfwSetWindowTitle(window, title.c_str());
}

/* ============================================================================
 * --------------------------- Set_Icon
 * Sets the icon of the window.
 * The icon will be displayed in the window's title bar and taskbar.
 * 
 * ------ Parameters ------
 * images: A vector of GLFWimage structures representing the icon images.
 * ============================================================================
 */
void Window::Set_Icon(const std::vector<GLFWimage>& images) {
    if (!images.empty()) {
        glfwSetWindowIcon(
            window, 
            static_cast<int>(images.size()), 
            images.data()
        );
    }
}

/* ============================================================================
 * --------------------------- Set_Position
 * Sets the position of the window on the screen.
 * The window will be moved to the specified coordinates.
 * 
 * ------ Parameters ------
 * x: The new x-coordinate of the window's top-left corner.
 * y: The new y-coordinate of the window's top-left corner.
 * ============================================================================
 */
void Window::Set_Position(const int x, const int y) {
    glfwSetWindowPos(window, x, y);
}

/* ============================================================================
 * --------------------------- Set_Size
 * Sets the size of the window.
 * The window will be resized to the specified width and height.
 * 
 * ------ Parameters ------
 * w: The new width of the window.
 * h: The new height of the window.
 * ============================================================================
 */
void Window::Set_Size(const int w, const int h) {
    glfwSetWindowSize(window, w, h);
}

/* ============================================================================
 * --------------------------- Set_SizeLimit
 * Sets the minimum and maximum size limits for the window.
 * The window will be constrained to the specified size range.
 * 
 * ------ Parameters ------
 * min_w: Minimum width of the window.
 * min_h: Minimum height of the window.
 * max_w: Maximum width of the window.
 * max_h: Maximum height of the window.
 * ============================================================================
 */
void Window::Set_SizeLimit(
    const int min_w, const int min_h,
    const int max_w, const int max_h
) {
    glfwSetWindowSizeLimits(
        window,
        min_w, min_h,
        max_w, max_h
    );
}

/* ============================================================================
 * --------------------------- Set_AspectRatio
 * Sets the aspect ratio of the window.
 * The window will maintain the specified aspect ratio.
 * 
 * ------ Parameters ------
 * n: Numerator of the aspect ratio.
 * d: Denominator of the aspect ratio.
 * ============================================================================
 */
void Window::Set_AspectRatio(
    const int n, const int d
) {
    glfwSetWindowAspectRatio(
        window,
        n, d
    );
}

/* ============================================================================
 * --------------------------- Set_Monitor
 * Switches the window to fullscreen mode on the specified monitor.
 * The window will be resized to fill the monitor's screen.
 * 
 * ------ Parameters ------
 * monitor: The monitor to switch to (fullscreen mode).
 * x: The x-coordinate of the window's position on the monitor.
 * y: The y-coordinate of the window's position on the monitor.
 * w: The width of the window in fullscreen mode.
 * h: The height of the window in fullscreen mode.
 * refreshRate: The refresh rate of the monitor (use 0 for default).
 * ============================================================================
 */
void Window::Set_Monitor(
    GLFWmonitor* monitor, 
    const int x, const int y, 
    const int w, const int h, 
    const int refreshRate
){
    glfwSetWindowMonitor(
        window, monitor,
        x, y,
        w, h,
        refreshRate
    );
}

/* ============================================================================
 * --------------------------- Set_Attribute
 * Sets an attribute of the window.
 * Attributes can control various window properties such as resizing and decorations.
 * 
 * ------ Parameters ------
 * attrib: The attribute to set.
 * value: The new value for the attribute.
 * ============================================================================
 */
void Window::Set_Attribute(const int attrib, const int value) {
    glfwSetWindowAttrib(window, attrib, value);
}


/* ============================================================================
 * --------------------------- Set_Resizable
 * Sets whether the window is resizable.
 * If resizable, the user can change the window's dimensions.
 *
 * ------ Parameters ------
 * resizable: Boolean value indicating if the window should be resizable.
 * ============================================================================
 */
void Window::Set_Resizable(const bool resizable) {
    glfwSetWindowAttrib(
        window, 
        GLFW_RESIZABLE, 
        resizable ? GLFW_TRUE : GLFW_FALSE
    );
}

/* ============================================================================
 * --------------------------- Set_Decorated
 * Sets whether the window has decorations such as a title bar and borders.
 * If decorated, the window will include standard window chrome.
 *
 * ------ Parameters ------
 * decorated: Boolean value indicating if the window should be decorated.
 * ============================================================================
 */
void Window::Set_Decorated(const bool decorated) {
    glfwSetWindowAttrib(
        window, 
        GLFW_DECORATED, 
        decorated ? GLFW_TRUE : GLFW_FALSE
    );
}

/* ============================================================================
 * --------------------------- Allow_CB_Chain
 * Sets whether or not the previous
 *
 * ------ Parameters ------
 * decorated: Boolean value indicating if the window should be decorated.
 * ============================================================================
 */
void Window::Allow_CB_Chain(const bool allow_chain){
    allow_cb_chain = allow_chain;
}

}

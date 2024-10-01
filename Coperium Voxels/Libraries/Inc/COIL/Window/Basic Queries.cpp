#include "Window.h"

namespace Coil {

/* ============================================================================
 * --------------------------- Is_FullScreen
 * Checks if the window is currently in fullscreen mode.
 * A window is considered fullscreen if it is associated with a monitor.
 * 
 * ------ Returns ------
 * true: If the window is fullscreen.
 * false: If the window is not fullscreen.
 * ============================================================================
 */
bool Window::Is_FullScreen() const {
    return glfwGetWindowMonitor(window) != nullptr;
}

/* ============================================================================
 * --------------------------- Does_Exist
 * Checks if the window object is valid.
 * A window is considered to exist if its GLFWwindow pointer is not null.
 * 
 * ------ Returns ------
 * true: If the window exists.
 * false: If the window does not exist.
 * ============================================================================
 */
bool Window::Does_Exist() const {
    return window != nullptr;
}

/* ============================================================================
 * --------------------------- Is_Visible
 * Checks if the window is currently visible.
 * A window is visible if it is not hidden or minimized.
 * 
 * ------ Returns ------
 * true: If the window is visible.
 * false: If the window is not visible.
 * ============================================================================
 */
bool Window::Is_Visible() const {
    return glfwGetWindowAttrib(window, GLFW_VISIBLE) == GLFW_TRUE;
}

/* ============================================================================
 * --------------------------- Is_Iconified
 * Checks if the window is currently iconified (minimized).
 * An iconified window is minimized and typically displayed as an icon.
 * 
 * ------ Returns ------
 * true: If the window is iconified.
 * false: If the window is not iconified.
 * ============================================================================
 */
bool Window::Is_Iconified() const {
    return glfwGetWindowAttrib(window, GLFW_ICONIFIED) == GLFW_TRUE;
}

/* ============================================================================
 * --------------------------- Is_Maximised
 * Checks if the window is currently maximised.
 * A maximised window is enlarged to fill the entire screen or a substantial
 * portion of it.
 *
 * ------ Returns ------
 * true: If the window is maximised.
 * false: If the window is not maximised.
 * ============================================================================
 */
bool Window::Is_Maximised() const{
    return glfwGetWindowAttrib(window, GLFW_MAXIMIZED) == GLFW_TRUE;
}

/* ============================================================================
 * --------------------------- Is_Focused
 * Checks if the window is currently focused.
 * A focused window is the active window that is receiving user input.
 * 
 * ------ Returns ------
 * true: If the window is focused.
 * false: If the window is not focused.
 * ============================================================================
 */
bool Window::Is_Focused() const {
    return glfwGetWindowAttrib(window, GLFW_FOCUSED) == GLFW_TRUE;
}

/* ============================================================================
 * --------------------------- Is_Resizable
 * Checks if the window is resizable.
 * A resizable window allows its dimensions to be changed by the user.
 * 
 * ------ Returns ------
 * true: If the window is resizable.
 * false: If the window is not resizable.
 * ============================================================================
 */
bool Window::Is_Resizable() const {
    return glfwGetWindowAttrib(window, GLFW_RESIZABLE) == GLFW_TRUE;
}

/* ============================================================================
 * --------------------------- Is_Decorated
 * Checks if the window has decorations such as a title bar and borders.
 * A decorated window has standard window chrome provided by the windowing system.
 * 
 * ------ Returns ------
 * true: If the window is decorated.
 * false: If the window is not decorated.
 * ============================================================================
 */
bool Window::Is_Decorated() const {
    return glfwGetWindowAttrib(window, GLFW_DECORATED) == GLFW_TRUE;
}


/* ============================================================================
 * --------------------------- Is_Closed
 * Checks if the window is closed
 *
 * ------ Returns ------
 * true: If the window is closed.
 * false: If the window is not closed.
 * ============================================================================
 */
bool Window::Is_Closed() const {
    return glfwWindowShouldClose(window);
}
}

#include "Input_Handler.h"
namespace Coil {

Input_Handler::Input_Handler(Window& window): window(&window){

}
/* ============================================================================
 * ---------------------------- Current_Instance
 * Returns a reference to the singleton instance of the Input_Handler class.
 *
 * ------ Returns ------
 * A reference to the singleton instance of the Input_Handler class.
 * ============================================================================
 */
Input_Handler*& Input_Handler::Current_Instance() {
    static Input_Handler* instance = nullptr;
    return instance;
}


void Input_Handler::Focus_Handler(Window win){
    if (window->Is_Focused()) {
        Current_Instance() = this;
    }
}
/* ============================================================================
 * ---------------------------- Constructor
 * Initializes all member variables to default values.
 * This sets up the mesh with no allocated resources.
 * ============================================================================
 */
void InputManager::Poll_MouseClicks() {
    // Get the current mouse position
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    mouseState.x = xpos;
    mouseState.y = ypos;

    // Get mouse button states
    mouseState.leftButton   = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT    )   == GLFW_PRESS) ? MouseButtonState::Pressed : MouseButtonState::Released;
    mouseState.rightButton  = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT   )  == GLFW_PRESS) ? MouseButtonState::Pressed : MouseButtonState::Released;
    mouseState.middleButton = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE  ) == GLFW_PRESS) ? MouseButtonState::Pressed : MouseButtonState::Released;

    // Get scroll offset (reset manually since glfw only reports it on scroll event)
    double scrollX, scrollY;
    glfwGetScrollOffset(window, &scrollX, &scrollY);
    mouseState.scrollX = scrollX;
    mouseState.scrollY = scrollY;

    // Detect changes and trigger callbacks if needed
    detectMouseChanges();

    // Update the previous mouse state
    prevMouseState = mouseState;
}
void InputManager::detectMouseChanges() {
    // Trigger mouse click callback if any button state has changed
    if (mouseClickCallback && (mouseState.leftButton != prevMouseState.leftButton)) {
        mouseClickCallback(mouseState.leftButton);
    }

    // Trigger mouse move callback if the position has changed
    if (mouseMoveCallback && (mouseState.x != prevMouseState.x || mouseState.y != prevMouseState.y)) {
        mouseMoveCallback(mouseState.x, mouseState.y);
    }

    // Trigger scroll callback if scroll has changed
    if (mouseScrollCallback && (mouseState.scrollX != prevMouseState.scrollX || mouseState.scrollY != prevMouseState.scrollY)) {
        mouseScrollCallback(mouseState.scrollX, mouseState.scrollY);
    }
}

}
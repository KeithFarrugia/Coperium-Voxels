#include "Fly_Camera.h"

namespace Coil {

/* ============================================================================
 * ---------------------------- Constructor
 * Default constructor for the Fly_Camera class.
 * Inherits from the base Camera class.
 * ============================================================================
 */
Fly_Camera::Fly_Camera(Window& window) 
    : Fly_Camera(window, 0.0f, 0.0f, 0.0f) {}

/* ============================================================================
 * ---------------------------- Constructor
 * Overloaded constructor for Fly_Camera class.
 * 
 * ------ Parameters ------
 * Pos_x:      The x-coordinate of the camera position.
 * Pos_y:      The y-coordinate of the camera position.
 * Pos_z:      The z-coordinate of the camera position.
 * ============================================================================
 */
Fly_Camera::Fly_Camera(
    Window& window, GLfloat Pos_x, GLfloat Pos_y, GLfloat Pos_z)
    : Camera(window, Pos_x, Pos_y, Pos_z
){
    toggle_mouse = true;
    last_frame   = 0.0f;
}

/* ============================================================================
 * ---------------------------- Process Keyboard
 * Handles keyboard input to move the camera based on user input.
 * The camera moves forward, backward, left, right, up, or down based on
 * the keys pressed. Movement is scaled by the delta time to ensure 
 * consistent movement speed regardless of frame rate.
 * 
 * ------ Parameters ------
 * deltaTime:  Time elapsed between the current and previous frame.
 * ============================================================================
 */
void Fly_Camera::Process_Keyboard(float deltaTime) {
    float velocity = Coil::Camera::movement_speed * deltaTime;

    std::vector<int> keys_to_erase;

    for (auto it = key_map.begin(); it != key_map.end(); ) {
        Key_Handler(it->first, it->second, velocity);

        if (it->second == io_states::UNPRESSED) {
            it = key_map.erase(it);

        } else { ++it; }
    }
}

/* ============================================================================
 * ---------------------------- Process Mouse Movement
 * Handles mouse movement input to change the camera's orientation.
 * Modifies the yaw and pitch of the camera based on mouse input.
 * Ensures the pitch stays within bounds to avoid flipping the camera.
 * 
 * ------ Parameters ------
 * xoffset:    The change in the x-coordinate of the mouse position.
 * yoffset:    The change in the y-coordinate of the mouse position.
 * ============================================================================
 */
void Fly_Camera::Process_Mouse_Movement(float xoffset, float yoffset) {
    xoffset *= mouse_sensitivity;
    yoffset *= mouse_sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) {
        pitch = 89.0f;

    } else if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    Update_Camera_Vectors();
}

/* ============================================================================
 * ---------------------------- Process Mouse Scroll
 * Handles mouse scroll input to zoom in or out by adjusting the field of view (FOV).
 * The FOV is clamped to a minimum and maximum value to prevent extreme zoom levels.
 * 
 * ------ Parameters ------
 * yoffset:    The change in the y-coordinate of the mouse scroll input.
 * ============================================================================
 */
void Fly_Camera::Process_Mouse_Scroll(float yoffset) {
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

/* ============================================================================
 * ---------------------------- Process Mouse Button
 * Handles a mouse button press, does nothing right now cause not important
 * ============================================================================
 */
void Coil::Fly_Camera::Process_Mouse_Button(
    int button, int action, int mods){}

/* ============================================================================
 * ---------------------------- Update
 * Updates the camera state (e.g., position, orientation) based on delta time.
 * Currently empty, but can be expanded for more complex camera updates.
 * 
 * ------ Parameters ------
 * deltatime:  Time elapsed between the current and previous frame.
 * ============================================================================
 */
void Fly_Camera::Update() {
    float current_frame = static_cast<float>(glfwGetTime());
    float delta_time = current_frame - last_frame;
    last_frame = current_frame;
    Process_Keyboard(delta_time);
}

/* ============================================================================
 * ---------------------------- Take Over All Input
 * Registers the camera to handle all input callbacks from the GLFW window.
 * Disables the cursor and captures mouse movement for camera control.
 *
 * ------ Behavior ------
 * - Registers the mouse position, scroll, mouse button, and keyboard callbacks.
 * - Disables the cursor and captures it for mouse movement control.
 * ============================================================================
 */
void Fly_Camera::Take_Over_All_Input() {
    first_mouse = true;
    Get_CurrentInstance() = this;
    GLFWwindow* window_ref = window->Get_Window();

    // Register all relevant input callbacks
    glfwSetCursorPosCallback    (window_ref, Mouse_Callback);
    glfwSetScrollCallback       (window_ref, Scroll_Callback);
    glfwSetMouseButtonCallback  (window_ref, Button_Callback);
    glfwSetKeyCallback          (window_ref, Keyboard_Callback);

    // Disable the cursor and capture it
    glfwSetInputMode(window_ref, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    key_map.clear();
}

/* ============================================================================
 * ---------------------------- Take Over Mouse
 * Registers the camera to handle mouse input callbacks from the GLFW window.
 * Disables the cursor and captures mouse movement for camera control.
 *
 * ------ Behavior ------
 * - Registers mouse position, scroll, and mouse button callbacks.
 * - Disables the cursor and captures it for mouse movement control.
 * ============================================================================
 */
void Fly_Camera::Take_Over_Mouse() {
    first_mouse = true;
    Get_CurrentInstance() = this;
    GLFWwindow* window_ref = window->Get_Window();

    // Register mouse-related input callbacks
    glfwSetCursorPosCallback    (window_ref, Mouse_Callback);
    glfwSetScrollCallback       (window_ref, Scroll_Callback);
    glfwSetMouseButtonCallback  (window_ref, Button_Callback);

    // Disable the cursor and capture it
    glfwSetInputMode(window_ref, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

/* ============================================================================
 * ---------------------------- Take Over Keyboard
 * Registers the camera to handle keyboard input callbacks from the GLFW window.
 *
 * ------ Behavior ------
 * - Registers the keyboard callback.
 * ============================================================================
 */
void Fly_Camera::Take_Over_Keyboard() {
    Get_CurrentInstance() = this;
    GLFWwindow* window_ref = window->Get_Window();

    // Register the keyboard input callback
    glfwSetKeyCallback      (window_ref, Keyboard_Callback);

    key_map.clear();
}

/* ============================================================================
 * ---------------------------- Release All Input
 * Releases the camera from handling all input callbacks.
 * Re-enables the cursor and stops capturing mouse movement.
 *
 * ------ Behavior ------
 * - Unregisters mouse position, scroll, mouse button, and keyboard callbacks.
 * - Re-enables the cursor, stopping mouse movement capture.
 * ============================================================================
 */
void Fly_Camera::Release_All_Input() {
    Get_CurrentInstance() = NULL;
    GLFWwindow* window_ref = window->Get_Window();

    // Unregister all input callbacks
    glfwSetCursorPosCallback    (window_ref, NULL);
    glfwSetScrollCallback       (window_ref, NULL);
    glfwSetMouseButtonCallback  (window_ref, NULL);
    glfwSetKeyCallback          (window_ref, NULL);

    // Re-enable the cursor
    glfwSetInputMode(window_ref, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    key_map.clear();
}

/* ============================================================================
 * ---------------------------- Release Mouse
 * Releases the camera from handling mouse input callbacks.
 * Re-enables the cursor and stops capturing mouse movement.
 *
 * ------ Behavior ------
 * - Unregisters mouse position, scroll, and mouse button callbacks.
 * - Re-enables the cursor, stopping mouse movement capture.
 * ============================================================================
 */
void Fly_Camera::Release_Mouse() {
    GLFWwindow* window_ref = window->Get_Window();

    // Unregister mouse-related input callbacks
    glfwSetCursorPosCallback    (window_ref, NULL);
    glfwSetScrollCallback       (window_ref, NULL);
    glfwSetMouseButtonCallback  (window_ref, NULL);

    // Re-enable the cursor
    glfwSetInputMode(window_ref, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

/* ============================================================================
 * ---------------------------- Release Keyboard
 * Releases the camera from handling keyboard input callbacks.
 *
 * ------ Behavior ------
 * - Unregisters the keyboard callback.
 * ============================================================================
 */
void Fly_Camera::Release_Keyboard() {
    GLFWwindow* window_ref = window->Get_Window();

    // Unregister the keyboard input callback
    glfwSetKeyCallback          (window_ref, NULL);

    key_map.clear();
}

}

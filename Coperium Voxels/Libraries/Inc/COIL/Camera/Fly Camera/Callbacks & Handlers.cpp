#include "Fly_Camera.h"

namespace Coil {

/* ============================================================================
 * ---------------------------- Key Handler
 * Processes individual key events to update the camera's position based on
 * user input. The function adjusts the camera's position in the 3D space
 * depending on the key pressed and the state of the key (PRESSED or REPEAT).
 * Movement is scaled by the provided velocity to ensure consistent speed.
 *
 * ------ Parameters ------
 * key_event: A structure containing the key and its state (PRESSED, REPEAT).
 * velocity:  The speed at which the camera moves, scaled by deltaTime.
 *
 * ------ Behavior ------
 * Depending on the key pressed:
 * - W:      Move forward along the camera's front vector.
 * - S:      Move backward along the camera's front vector.
 * - A:      Move left along the camera's right vector.
 * - D:      Move right along the camera's right vector.
 * - SPACE:  Move up along the world up vector.
 * - SHIFT:  Move down along the world up vector.
 *
 * The function modifies the camera's position in the corresponding direction
 * by adding or subtracting the right, front, or up vectors multiplied by
 * the velocity.
 * ============================================================================
 */
void Fly_Camera::Key_Handler(int key, io_states event, float velocity) {
    if (event == io_states::PRESSED ||
        event == io_states::REPEAT) {

        switch (key) {
        case GLFW_KEY_W:            position += front * velocity; break;
        case GLFW_KEY_S:            position -= front * velocity; break;
        case GLFW_KEY_A:            position -= right * velocity; break;
        case GLFW_KEY_D:            position += right * velocity; break;
        case GLFW_KEY_SPACE:        position += up    * velocity; break;
        case GLFW_KEY_LEFT_SHIFT:   position -= up    * velocity; break;

        case GLFW_KEY_TAB:          toggle_mouse ? Release_Mouse() : Take_Over_Mouse();   toggle_mouse = !toggle_mouse;           break;
        }
    
    
    }else {
    }
}


void Fly_Camera::Window_Focus_Callback(Window& window) {
    if (window.Is_Focused()) {
        first_mouse = true;
        Take_Over_All_Input();
    }else {
        Release_All_Input();
    }
}

void Fly_Camera::Window_Size_Callback(Window& window) {
    window.Get_Size(window_width, window_height);
}

};
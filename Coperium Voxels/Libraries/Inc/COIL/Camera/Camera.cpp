#include "Camera.h"

namespace Coil {

/* ============================================================================
 * ---------------------------- Default Constructor
 * Initializes a Camera object with a default position at (0.0f, 0.0f, 0.0f).
 * ============================================================================
 */
Camera::Camera(Window& window)
    : Camera(window, 0.0f, 0.0f, 0.0f) {}

/* ============================================================================
 * ---------------------------- Parameterized Constructor
 * Initializes a Camera object at the given position (Pos_x, Pos_y, Pos_z).
 *
 * ------ Parameters ------
 * Pos_x:       The x-coordinate of the camera's initial position.
 * Pos_y:       The y-coordinate of the camera's initial position.
 * Pos_z:       The z-coordinate of the camera's initial position.
 * ============================================================================
 */
Camera::Camera(
    Window& window, GLfloat Pos_x, GLfloat Pos_y, GLfloat Pos_z) 
    : window(window)
{
    position            = glm::vec3(Pos_x, Pos_y, Pos_z);
    world_up            = WORLD_UP;
    yaw                 = YAW;
    pitch               = PITCH;
    fov                 = FOV;
    mouse_sensitivity   = SENSITIVITY;
    movement_speed      = SPEED;
    front               = glm::vec3(0.0f, 0.0f, -1.0f);
    first_mouse         = true;
    near_plane          = NEAR_PLANE;
    far_plane           = FAR_PLANE;

    window.Get_Size(window_width, window_height);

    window.Add_Focus_Callback([this](Window& win) {
        this->Window_Focus_Callback(win);
    });

    window.Add_Size_Callback([this](Window& win) {
        this->Window_Size_Callback(win);
    });

    Update_Camera_Vectors();
}

/* ============================================================================
 * ---------------------------- Destructor
 * Cleans up any resources held by the Camera object when it is destroyed.
 * ============================================================================
 */
Camera::~Camera() {}

/* ============================================================================
 * ---------------------------- Update_Camera_Vectors
 * Recalculates the camera's front, right, and up vectors based on 
 * its current yaw and pitch. This method is called whenever the 
 * camera's orientation changes (e.g., when the mouse moves).
 * ============================================================================
 */
void Camera::Update_Camera_Vectors() {

    front.x = cos(glm::radians(yaw  )) * 
              cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw  )) * 
              cos(glm::radians(pitch));

    front   = glm::normalize(front);

    right   = glm::normalize(glm::cross(front, world_up));
    up      = glm::normalize(glm::cross(right, front));
}


/* ============================================================================
 * ---------------------------- Mouse_Callback
 * Handles mouse movement events to adjust the camera's orientation.
 *
 * ------ Parameters ------
 * window:      The GLFW window receiving the event.
 * xposIn:      The new x-coordinate of the mouse cursor.
 * yposIn:      The new y-coordinate of the mouse cursor.
 * ============================================================================
 */
void Camera::Mouse_Callback(GLFWwindow* window, double xposIn, double yposIn) {
    Camera* cam = Get_CurrentInstance();

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (cam->first_mouse) {
        cam->last_x = xpos;
        cam->last_y = ypos;
        cam->first_mouse = false;
    }

    float xoffset = xpos - cam->last_x;
    float yoffset = cam->last_y - ypos;

    cam->last_x = xpos;
    cam->last_y = ypos;

    cam->Process_Mouse_Movement(xoffset, yoffset);
}

/* ============================================================================
 * ---------------------------- Keyboard_Callback
 * Handles keyboard events to enqueue key presses and releases.
 *
 * ------ Parameters ------
 * window:      The GLFW window receiving the event.
 * key:         The keyboard key that was pressed or released.
 * scancode:    The system-specific scancode of the key.
 * action:      The action type (press, release, or repeat).
 * mods:        Bit field describing which modifier keys were held down.
 * ============================================================================
 */
void Camera::Keyboard_Callback(
    GLFWwindow* window, int key, int scancode, int action, int mods
){
    Camera* cam = Get_CurrentInstance();
    
    switch (action) {
    case GLFW_PRESS:
        cam->key_map[key] = key_states_t::PRESSED;
        break;

    case GLFW_REPEAT:
        cam->key_map[key] = key_states_t::REPEAT;
        break;

    case GLFW_RELEASE:
        cam->key_map[key] = key_states_t::UNPRESSED;
        break;
    }
}

/* ============================================================================
 * ---------------------------- Scroll_Callback
 * Handles scroll events to zoom the camera in or out 
 * by adjusting the field of view (FOV).
 *
 * ------ Parameters ------
 * window:      The GLFW window receiving the event.
 * xoffset:     The scroll offset along the x-axis (usually unused).
 * yoffset:     The scroll offset along the y-axis (used for zooming).
 * ============================================================================
 */
void Camera::Scroll_Callback(
    GLFWwindow* window, double xoffset, double yoffset
){
    Camera* cam = Get_CurrentInstance();
    cam->Process_Mouse_Scroll(static_cast<float>(yoffset));
}

/* ============================================================================
 * ---------------------------- Mouse Button Callback
 * Static callback function for handling mouse button events.
 * This function is registered with GLFW to handle any mouse button presses
 * or releases in the application window.
 *
 * The function retrieves the current Fly_Camera instance using the GLFW window
 * user pointer and then calls the Handle_Mouse_Button() method on that instance.
 *
 * ------ Parameters ------
 * window:  The GLFW window that received the event.
 * button:  The mouse button that was pressed or released 
            (e.g., GLFW_MOUSE_BUTTON_LEFT).
 * action:  The action performed (e.g., GLFW_PRESS or GLFW_RELEASE).
 * mods:    Modifier keys held during the event (e.g., Shift or Ctrl).
 * ============================================================================
 */
void Camera::Button_Callback(
    GLFWwindow* window, int button, int action, int mods
) {
    Camera* cam = Get_CurrentInstance();
    cam->Process_Mouse_Button(button, action, mods);

}

/* ============================================================================
 * ---------------------------- Get_CurrentInstance
 * Returns a reference to the singleton instance of the Camera class.
 *
 * ------ Returns ------
 * A reference to the singleton instance of the Camera class.
 * ============================================================================
 */
Camera*& Camera::Get_CurrentInstance() {
    static Camera* instance = nullptr;
    return instance;
}


} // namespace Coil
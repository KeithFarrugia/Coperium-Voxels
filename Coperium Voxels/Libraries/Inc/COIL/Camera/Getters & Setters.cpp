#include "Camera.h"

namespace Coil {

/* ============================================================================
 * ---------------------------- Get_Window
 * Returns the reference to the associated window.
 *
 * ------ Returns ------
 * A reference to a `Window` object.
 * ============================================================================
 */
Window& Camera::Get_Window() const {
    return window;
}

/* ============================================================================
 * ---------------------------- Get_Position
 * Returns the current position of the camera in 3D space.
 *
 * ------ Returns ------
 * A glm::vec3 representing the camera's position.
 * ============================================================================
 */
glm::vec3 Camera::Get_Position() const {
    return position;
}

/* ============================================================================
 * ---------------------------- Get_Front
 * Returns the front vector of the camera, representing the direction it is facing.
 *
 * ------ Returns ------
 * A glm::vec3 representing the camera's front direction.
 * ============================================================================
 */
glm::vec3 Camera::Get_Front() const {
    return front;
}

/* ============================================================================
 * ---------------------------- Get_FOV
 * Returns the current field of view (FOV) of the camera.
 *
 * ------ Returns ------
 * A float representing the camera's field of view in degrees.
 * ============================================================================
 */
float Camera::Get_FOV() const {
    return fov;
}

/* ============================================================================
 * ---------------------------- Get_Yaw
 * Returns the yaw angle of the camera, representing its rotation around the y-axis.
 *
 * ------ Returns ------
 * A float representing the camera's yaw angle in degrees.
 * ============================================================================
 */
float Camera::Get_Yaw() const {
    return yaw;
}

/* ============================================================================
 * ---------------------------- Get_Pitch
 * Returns the pitch angle of the camera, representing its rotation around the x-axis.
 *
 * ------ Returns ------
 * A float representing the camera's pitch angle in degrees.
 * ============================================================================
 */
float Camera::Get_Pitch() const {
    return pitch;
}

/* ============================================================================
 * ---------------------------- Get_Movement_Speed
 * Returns the movement speed of the camera.
 *
 * ------ Returns ------
 * A float representing the camera's movement speed.
 * ============================================================================
 */
float Camera::Get_Movement_Speed() const {
    return movement_speed;
}

/* ============================================================================
 * ---------------------------- Get_Mouse_Sensitivity
 * Returns the mouse sensitivity for the camera.
 *
 * ------ Returns ------
 * A float representing the camera's mouse sensitivity.
 * ============================================================================
 */
float Camera::Get_Mouse_Sensitivity() const {
    return mouse_sensitivity;
}

/* ============================================================================
 * ---------------------------- Set_Window
 * Sets the associated window for the camera.
 *
 * ------ Parameters ------
 * window: A constant reference to a `Window` object.
 * ============================================================================
 */
void Camera::Set_Window(const Window& window) {
    this->window = window;
}

/* ============================================================================
 * ---------------------------- Set_Position
 * Sets the position of the camera in 3D space.
 *
 * ------ Parameters ------
 * position: A glm::vec3 representing the new camera position.
 * ============================================================================
 */
void Camera::Set_Position(const glm::vec3& position) {
    this->position = position;
}

/* ============================================================================
 * ---------------------------- Set_Front
 * Sets the front vector of the camera, representing the direction it is facing.
 *
 * ------ Parameters ------
 * front: A glm::vec3 representing the new camera front direction.
 * ============================================================================
 */
void Camera::Set_Front(const glm::vec3& front) {
    this->front = front;
    Update_Camera_Vectors(); // Ensure that the right and up vectors are updated.
}

/* ============================================================================
 * ---------------------------- Set_FOV
 * Sets the field of view (FOV) of the camera.
 *
 * ------ Parameters ------
 * fov: A float representing the new field of view in degrees.
 * ============================================================================
 */
void Camera::Set_FOV(float fov) {
    this->fov = fov;
}

/* ============================================================================
 * ---------------------------- Set_Yaw
 * Sets the yaw angle of the camera, representing its rotation around the y-axis.
 *
 * ------ Parameters ------
 * yaw: A float representing the new yaw angle in degrees.
 * ============================================================================
 */
void Camera::Set_Yaw(float yaw) {
    this->yaw = yaw;
    Update_Camera_Vectors(); // Ensure that the front, right, and up vectors are updated.
}

/* ============================================================================
 * ---------------------------- Set_Pitch
 * Sets the pitch angle of the camera, representing its rotation around the x-axis.
 *
 * ------ Parameters ------
 * pitch: A float representing the new pitch angle in degrees.
 * ============================================================================
 */
void Camera::Set_Pitch(float pitch) {
    this->pitch = pitch;
    Update_Camera_Vectors(); // Ensure that the front, right, and up vectors are updated.
}

/* ============================================================================
 * ---------------------------- Set_Movement_Speed
 * Sets the movement speed of the camera.
 *
 * ------ Parameters ------
 * movement_speed: A float representing the new movement speed.
 * ============================================================================
 */
void Camera::Set_Movement_Speed(float movement_speed) {
    this->movement_speed = movement_speed;
}

/* ============================================================================
 * ---------------------------- Set_Mouse_Sensitivity
 * Sets the mouse sensitivity for the camera.
 *
 * ------ Parameters ------
 * sensitivity: A float representing the new mouse sensitivity.
 * ============================================================================
 */
void Camera::Set_Mouse_Sensitivity(float sensitivity) {
    this->mouse_sensitivity = sensitivity;
}

/* ============================================================================
 * ---------------------------- Set_Farplane
 * Sets the far clipping plane distance for the camera.
 *
 * ------ Parameters ------
 * far_plane: A float representing the new far clipping plane distance.
 * ============================================================================
 */
void Camera::Set_Farplane(const float far_plane) {
    this->far_plane = far_plane;
}

/* ============================================================================
 * ---------------------------- Set_Nearplane
 * Sets the near clipping plane distance for the camera.
 *
 * ------ Parameters ------
 * near_plane: A float representing the new near clipping plane distance.
 * ============================================================================
 */
void Camera::Set_Nearplane(const float near_plane) {
    this->near_plane = near_plane;
}

/* ============================================================================
 * ---------------------------- Set_WindowWidth
 * Sets the width of the associated window.
 *
 * ------ Parameters ------
 * window_width: An integer representing the new window width.
 * ============================================================================
 */
void Camera::Set_WindowWidth(const int window_width) {
    this->window_width = window_width;
}

/* ============================================================================
 * ---------------------------- Set_WindowHeight
 * Sets the height of the associated window.
 *
 * ------ Parameters ------
 * window_height: An integer representing the new window height.
 * ============================================================================
 */
void Camera::Set_WindowHeight(const int window_height) {
    this->window_height = window_height;
}

} // namespace Coil

#include "Fly_Camera.h"

namespace Coil {

/* ============================================================================
 * ---------------------------- Get_View_Matrix
 * Returns the view matrix calculated using the camera's position, front,
 * and up vectors.
 * This matrix is used to transform world coordinates to camera coordinates.
 *
 * ------ Returns ------
 * A glm::mat4 representing the view matrix.
 * ============================================================================
 */
glm::mat4 Fly_Camera::Calc_View_Matrix() {
    return glm::lookAt(position, position + front, up);
}

/* ============================================================================
 * ---------------------------- Calc_Projection_Matrix
 * Returns the projection matrix calculated using the camera's field of view
 * (FOV), the aspect ratio of the window, and the near and far clipping planes.
 * This matrix is used to project 3D coordinates onto a 2D screen.
 *
 * ------ Returns ------
 * A glm::mat4 representing the projection matrix.
 *
 * ------ Behavior ------
 * - Uses `glm::perspective` to calculate a perspective projection matrix.
 * - The field of view (FOV) is converted to radians.
 * - The aspect ratio is calculated using the current window dimensions.
 * - Near and far planes define the depth range of the view.
 * ============================================================================
 */
glm::mat4 Fly_Camera::Calc_Projection_Matrix() {
    if (window_width <= 0 || window_width <= 0) {
        return glm::mat4(1.0f);
    }

    return glm::perspective(
        glm::radians(fov),
        (float)window_width / (float)window_height,
        near_plane, far_plane
    );
}
}
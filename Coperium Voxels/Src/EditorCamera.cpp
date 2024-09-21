#include "EditorCamera.h"

std::tuple<bool, glm::vec3, glm::vec3> EditorCamera::Raycast(glm::vec3 origin, glm::vec3 direction, float maxLength) {
    direction = glm::normalize(direction);
    glm::ivec3 currentVoxel = glm::floor(origin);

    glm::ivec3 step(
        (direction.x > 0) ? 1 : -1,
        (direction.y > 0) ? 1 : -1,
        (direction.z > 0) ? 1 : -1
    );

    glm::vec3 tMax(
        (direction.x != 0.0f) ? ((direction.x > 0 ? (currentVoxel.x + 0.5f) : (currentVoxel.x - 0.5f)) - origin.x) / direction.x : std::numeric_limits<float>::infinity(),
        (direction.y != 0.0f) ? ((direction.y > 0 ? (currentVoxel.y + 0.5f) : (currentVoxel.y - 0.5f)) - origin.y) / direction.y : std::numeric_limits<float>::infinity(),
        (direction.z != 0.0f) ? ((direction.z > 0 ? (currentVoxel.z + 0.5f) : (currentVoxel.z - 0.5f)) - origin.z) / direction.z : std::numeric_limits<float>::infinity()
    );

    glm::vec3 tDelta(
        (direction.x != 0.0f) ? std::abs(1.0f / direction.x) : std::numeric_limits<float>::infinity(),
        (direction.y != 0.0f) ? std::abs(1.0f / direction.y) : std::numeric_limits<float>::infinity(),
        (direction.z != 0.0f) ? std::abs(1.0f / direction.z) : std::numeric_limits<float>::infinity()
    );

    float distanceTravelled = 0.0f;

    while (distanceTravelled < maxLength) {
        Voxel voxel = world.Get_Voxel(currentVoxel.x, currentVoxel.y, currentVoxel.z);
        if (voxel.Get_Type() == voxel_type_t::NORMAL) {
            // Calculate normal based on the axis that was hit first
            glm::vec3 normal(0.0f);

            if (tMax.x < tMax.y && tMax.x < tMax.z) {
                normal.x = (direction.x > 0) ? -1.0f : 1.0f;  // Hit the x face
            }
            else if (tMax.y < tMax.z) {
                normal.y = (direction.y > 0) ? -1.0f : 1.0f;  // Hit the y face
            }
            else {
                normal.z = (direction.z > 0) ? -1.0f : 1.0f;  // Hit the z face
            }

            return std::make_tuple(true, currentVoxel, glm::normalize(normal));
        }

        // Move to the next voxel based on which axis tMax is smallest
        if (tMax.x < tMax.y && tMax.x < tMax.z) {
            currentVoxel.x += step.x;
            distanceTravelled = tMax.x;
            tMax.x += tDelta.x;
        }
        else if (tMax.y < tMax.z) {
            currentVoxel.y += step.y;
            distanceTravelled = tMax.y;
            tMax.y += tDelta.y;
        }
        else {
            currentVoxel.z += step.z;
            distanceTravelled = tMax.z;
            tMax.z += tDelta.z;
        }
    }

    return std::make_tuple(false, glm::vec3(0.0f), glm::vec3(0.0f));
}

/* ============================================================================
*------------------------ - Process_Mouse_Button(Override)
* Handles block placement and removal in the voxel world.
*
*------Parameters------
* button:      The mouse button that was pressed(e.g., GLFW_MOUSE_BUTTON_LEFT).
* action : The action performed(GLFW_PRESS or GLFW_RELEASE).
* mods : Modifier keys held down(e.g., Shift or Ctrl).
* ============================================================================
*/
void EditorCamera::Process_Mouse_Button(int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        std::tuple<bool, glm::vec3, glm::vec3> result = Raycast(position, front, 10);  // Raycasting into the world

        bool hit = std::get<0>(result);
        glm::vec3 hitPosition = std::get<1>(result);
        glm::vec3 normal = std::get<2>(result);

        printf("Result %s [%f, %f, %f] Normal [%f, %f, %f]\n", hit ? "true" : "false", hitPosition.x, hitPosition.y, hitPosition.z, normal.x, normal.y, normal.z);

        if (true) {
            glm::ivec3 hit_vox = glm::floor(hitPosition);

            if (button == GLFW_MOUSE_BUTTON_LEFT) {
                // Remove the voxel
                world.Remove_Voxel(hit_vox);
                Re_Generate_Chunk_Mesh(world, hit_vox);

            }
            else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
                // Place a voxel at the adjacent position in the normal direction
                glm::ivec3 place_position = hit_vox + glm::ivec3(static_cast<int>(normal.x), static_cast<int>(normal.y), static_cast<int>(normal.z));

                // Add a voxel at the adjacent position
                world.Add_Voxel(place_position, glm::ivec3(255, 255, 255), 0, voxel_type_t::NORMAL);  // Example: Add white block
                Re_Generate_Chunk_Mesh(world, place_position);
            }
        }
    }
}
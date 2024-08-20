#pragma once
#ifndef COIL_CONSTANTS_H
#define COIL_CONSTANTS_H

// --------------------------------- External Includes
#include <string.h>
#include <GLM/glm.hpp>

namespace Coil {

    constexpr   int             LOG_CALLER_LENGTH       = 20;                       // number of characters for logging the caller

    const       std::string     DEFAULT_SHADER_PATH     = "Resources/Shaders/";

    constexpr   float           YAW                     = -90.0f;
    constexpr   float           PITCH                   = 0.0f;
    constexpr   float           SPEED                   = 2.5f;
    constexpr   float           SENSITIVITY             = 0.1f;
    constexpr   float           FOV                     = 70.0f;
    constexpr   float           NEAR_PLANE              = 0.1f;
    constexpr   float           FAR_PLANE               = 100.0f;
    constexpr   glm::vec3       WORLD_UP                = glm::vec3(0.0f, 1.0f, 0.0f);
}
#endif // !COIL_CONSTANTS_H

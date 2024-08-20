#pragma once
#ifndef COIL_TYPES_H
#define COIL_TYPES_H

// --------------------------------- External Includes
#include <unordered_map>
#include <vector>

namespace Coil {


typedef enum {
    SUCCESS,    // It Worked
    FAILURE,    // It didn't work but not error causing (e.g. duplicate insert in map)
    ERROR,      // Error
}status_t;



/* ---------------------------------
 * Defines the logging style
 */
typedef enum {
    LOG_TO_FILE,
    LOG_TO_CONSOLE,
    DISABLE_LOG,
}log_style_t;



/* ---------------------------------
 * Shader Type
 */
typedef enum {
    VERTEX_SHADER,
    COMPUTE_SHADER,
    FRAGMENT_SHADER,
    GEOMETRY_SHADER,
    TESSELATION_CONTROL_SHADER,
    TESSELATION_EVALUATION_SHADER,
}shader_type_t;



/* ---------------------------------
 * Shader pair
 */
typedef struct {
    std::string shader_name;
    Coil::shader_type_t type;
}shader_info_t;

typedef std::pair
        <Coil::shader_type_t,std::string> 
        shader_pair_t;

typedef std::unordered_map
        <Coil::shader_type_t, std::string>
        shader_map_t;

typedef std::vector<shader_info_t> shader_list_t;




/* ---------------------------------
 * Camera
 */
typedef enum{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    Up,
    Down,
}camera_movement_t;

typedef enum{
    UNPRESSED,
    PRESSED,
    REPEAT
}key_states_t;


typedef struct {
    int          key;
    key_states_t state;
}key_event_t;


}
#endif // !COIL_TYPES_H
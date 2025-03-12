#pragma once
#ifndef COIL_CONVERSION
#define COIL_CONVERSION

// --------------------------------- Internal Includes
#include "Types.h"
#include <string>


namespace Coil{

/* ============================================================================
 * --------------------------------- Read Shaders
 * ============================================================================
 */
inline int To_GL(Coil::shader_type_t type) {
    switch (type) {
        case Coil::shader_type_t::VERTEX_SHADER:                 return 0x8B31;  // GL_VERTEX_SHADER
        case Coil::shader_type_t::COMPUTE_SHADER:                return 0x91B9;  // GL_COMPUTE_SHADER
        case Coil::shader_type_t::FRAGMENT_SHADER:               return 0x8B30;  // GL_FRAGMENT_SHADER
        case Coil::shader_type_t::GEOMETRY_SHADER:               return 0x8DD9;  // GL_GEOMETRY_SHADER
        case Coil::shader_type_t::TESSELATION_CONTROL_SHADER:    return 0x8E88;  // GL_TESS_CONTROL_SHADER
        case Coil::shader_type_t::TESSELATION_EVALUATION_SHADER: return 0x8E87;  // GL_TESS_EVALUATION_SHADER
        default:                                                 return 0;
    }
}

inline std::string To_String(Coil::shader_type_t type) {
    switch (type){
        case Coil::shader_type_t::VERTEX_SHADER                 :return "VERTEX";
        case Coil::shader_type_t::COMPUTE_SHADER                :return "COMPUTE";
        case Coil::shader_type_t::FRAGMENT_SHADER               :return "FRAGMENT";
        case Coil::shader_type_t::GEOMETRY_SHADER               :return "GEOMETRY";
        case Coil::shader_type_t::TESSELATION_CONTROL_SHADER    :return "TESS CONTROL";
        case Coil::shader_type_t::TESSELATION_EVALUATION_SHADER :return "TESS EVELUATION";
        default                                                 :return "UNKOWN";
    }
}

}
#endif // !COIL_CONVERSION

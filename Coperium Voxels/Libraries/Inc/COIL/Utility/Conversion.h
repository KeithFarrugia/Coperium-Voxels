#pragma once
#ifndef COIL_CONVERSION
#define COIL_CONVERSION

// --------------------------------- External Includes
#include <GLAD/glad.h>

// --------------------------------- Internal Includes
#include "Types.h"


namespace Coil{

/* ============================================================================
 * --------------------------------- Read Shaders
 * ============================================================================
 */
inline GLenum To_GL(Coil::shader_type_t type) {
    switch (type){
        case Coil::shader_type_t::VERTEX_SHADER                 :return GL_VERTEX_SHADER;
        case Coil::shader_type_t::COMPUTE_SHADER                :return GL_COMPUTE_SHADER;
        case Coil::shader_type_t::FRAGMENT_SHADER               :return GL_FRAGMENT_SHADER;
        case Coil::shader_type_t::GEOMETRY_SHADER               :return GL_GEOMETRY_SHADER;
        case Coil::shader_type_t::TESSELATION_CONTROL_SHADER    :return GL_TESS_CONTROL_SHADER;
        case Coil::shader_type_t::TESSELATION_EVALUATION_SHADER :return GL_TESS_EVALUATION_SHADER;
        default                                                 :return 0;
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

#pragma once
#ifndef COIL_SHADER_H
#define COIL_SHADER_H

// --------------------------------- External Includes
#include <GLM/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <mutex>

// --------------------------------- Internal Includes
#include "../Utility.h"

namespace Coil {

class Shader {
public: 
    Shader( std::string shader_name, 
            std::string shader_path = DEFAULT_SHADER_PATH);

    ~Shader();

    // --------------------------------- General Functions
    status_t Add_Shaders(   const Coil::shader_list_t   shader_list,
                            const bool                  use_def_path = true );
    status_t Add_Shaders(   const Coil::shader_info_t   shader_pair,
                            const bool                  use_def_path = true );
    status_t Compile_And_Link();

    status_t Use()  const;
    status_t Del()  const;

    unsigned int Get_ID() const;

    // --------------------------------- Uniform Handlers
    int  Get_Uniform (const char* uniform_name                              ) const;
    void Set_Bool    (const char* uniform_name, const bool           value  ) const;
    void Set_Int     (const char* uniform_name, const GLint          value  ) const;
    void Set_Float   (const char* uniform_name, const GLfloat        value  ) const;
    void Set_Vec3    (const char* uniform_name, const glm::vec3      value  ) const;
    void Set_Vec4    (const char* uniform_name, const glm::vec4      value  ) const;
    void Set_Matrix4 (const char* uniform_name, const glm::mat4      value  ) const;
private:


    // --------------------------------- Compilation Handlers
    status_t Read_Shaders           (const  std::string         shader_path, 
                                            std::string&        shader_code         )const;

    status_t Compile_Shader         (const Coil::shader_type_t  shader_type,
                                     const char*                shader_code,
                                     GLuint&                    comp_shader         ) const;

    status_t Attach_Shader          (const Coil::shader_type_t  shader_type, 
                                     const GLuint               comp_shader         )const;

    status_t Check_Compile_Errors   (const GLuint               compile_shader,
                                     const std::string          type                )const;


    // --------------------------------- Variables
    std::string         shader_name;
    std::string         defualt_shader_file_path;
    unsigned int        shader_id;
    shader_map_t        shaders_sources;
    static std::mutex   shader_mutex_lock;
};
}
#endif // !COIL_SHADER_H

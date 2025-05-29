#pragma once
#ifndef COIL_SHADER_H
#define COIL_SHADER_H

#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <mutex>

#include "../Utility.h"
// NO #include <GLAD/glad.h>

namespace Coil {

class Shader {
public: 
    Shader(std::string shader_name, std::string shader_path = DEFAULT_SHADER_PATH);
    ~Shader();

    status_t Add_Shaders(const Coil::shader_list_t shader_list, bool use_def_path = true);
    status_t Add_Shaders(const Coil::shader_info_t shader_pair, bool use_def_path = true);
    status_t Compile_And_Link();

    status_t Use()  const;
    status_t Del()  const;

    unsigned int Get_ID() const;

    int  Get_Uniform (const char* uniform_name) const;
    void Set_Bool    (const char* uniform_name, bool value)         const;
    void Set_Int     (const char* uniform_name, int  value)         const;
    void Set_Float   (const char* uniform_name, float value)        const;
    void Set_Vec3    (const char* uniform_name, const glm::vec3 val) const;
    void Set_Vec4    (const char* uniform_name, const glm::vec4 val) const;
    void Set_Matrix4 (const char* uniform_name, const glm::mat4 val) const;

    void Set_Bool    (unsigned int location, bool value)           const;
    void Set_Int     (unsigned int location, int value)            const;
    void Set_Float   (unsigned int location, float value)          const;
    void Set_Vec3    (unsigned int location, const glm::vec3 vec)  const;
    void Set_Vec4    (unsigned int location, const glm::vec4 vec)  const;
    void Set_Matrix4 (unsigned int location, const glm::mat4 mat)  const;

private:
    status_t Read_Shaders   (const std::string shader_path, std::string& shader_code) const;
    status_t Compile_Shader (Coil::shader_type_t shader_type, const char* shader_code, unsigned int& comp_shader) const;
    status_t Attach_Shader  (Coil::shader_type_t shader_type, const unsigned int comp_shader) const;
    status_t Check_Compile_Errors(const unsigned int shader, const std::string type) const;

    std::string shader_name;
    std::string defualt_shader_file_path;
    unsigned int shader_id;
    shader_map_t shaders_sources;
    static std::mutex shader_mutex_lock;
};
}
#endif // !COIL_SHADER_H

#include "Shader.h"
namespace Coil{
/* ============================================================================
 * --------------------------------- Static Variables
 * ============================================================================
 */
std::mutex Shader::shader_mutex_lock;


/* ============================================================================
 * --------------------------------- Constructor
 * ============================================================================
 */
Shader::Shader(
    // ================================= Parameters
    std::string shader_name,
    std::string shader_path ){

    // ================================= Code

    this->shader_name               = shader_name;
    this->defualt_shader_file_path  = shader_path;
    shader_id                       = 0;
}

/* ============================================================================
 * --------------------------------- De-Structor
 * ============================================================================
 */
Shader::~Shader() { Del(); }


/* ============================================================================
 * --------------------------------- Add Shader List
 * Check if the user wants to use the defualt path
 * Then add the Shader locations are then passed
 * to a map so that no Shader type is used more then
 * once
 * ============================================================================
 */

status_t Shader::Add_Shaders(
    // ================================= Parameters
    const shader_list_t shader_list,
    const bool          use_default_path){

    // ================================= Code

    if (use_default_path == true) {
        for (const shader_info_t shader_info : shader_list) {
            shaders_sources[shader_info.type] =
                defualt_shader_file_path + shader_info.shader_name;
        }

    }else {
        for (const shader_info_t shader_info : shader_list) {
            shaders_sources[shader_info.type] =
                shader_info.shader_name;
        }
    }

    return status_t::SUCCESS;
}

/* ============================================================================
 * --------------------------------- Add Shader
 * Check if the user wants to use the defualt path
 * Then add the Shader locations are then passed
 * to a map so that no Shader type is used more then
 * once
 * ============================================================================
 */
status_t Shader::Add_Shaders(
    // ================================= Parameters
    const shader_info_t shader_info,
    const bool          use_default_path ) {

    // ================================= Code

    if (use_default_path == true) {
        shaders_sources[shader_info.type] =
            defualt_shader_file_path + shader_info.shader_name;

    }else {
        shaders_sources[shader_info.type] =
            shader_info.shader_name;
    }

    return status_t::SUCCESS;
}



/* ============================================================================
 * --------------------------------- Use
 * ============================================================================
 */
status_t Shader::Use() const {
    if (shader_id != 0) {
        glUseProgram(shader_id);
        return status_t::SUCCESS;

    } else {
        Logger::log("Shader [" +shader_name+ "]",
                    "Error: Tried to use an unassigned Shader");

        return status_t::ERROR;
    }
}

status_t Shader::Del() const {

    if (shader_id != 0) {
        glDeleteProgram(shader_id);
        return status_t::SUCCESS;

    } else {
        Logger::log("Shader [" +shader_name+ "]",
                    "Nothing to delete: Tried to delete an unassigned Shader");

        return status_t::FAILURE;
    }
}

// ========================== Getters ==========================
unsigned int Shader::Get_ID() const { 
    return this->shader_id;
}

}
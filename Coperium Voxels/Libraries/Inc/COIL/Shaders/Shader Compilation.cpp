#include "Shader.h"
namespace Coil{
/* ============================================================================
 * --------------------------------- Compile & Link
 * reads the Shader code for each Shader in the 
 * "shaders_sources" list and compiles each one and
 * linking them
 * ============================================================================
 */
status_t Shader::Compile_And_Link(){
    status_t result;
    
    if (Del() == status_t::ERROR) { return status_t::ERROR; }

    // --------------------------------- Thread Safety
    shader_mutex_lock.lock();
    this->shader_id = glCreateProgram();
    shader_mutex_lock.unlock();


    for (const shader_pair_t shader_pair : shaders_sources) {
        std::string shader_source_code;
        GLuint comp_shader;

        // --------------------------------- Read Shader
        result = Read_Shaders(
            shader_pair.second,
            shader_source_code);
        if (result == status_t::ERROR) { break; }

        // --------------------------------- Compile Shader
        result = Compile_Shader(
            shader_pair.first,
            shader_source_code.c_str(),
            comp_shader);
        if (result == status_t::ERROR) { break; }

        // --------------------------------- Link Shader
        result = Attach_Shader(
            shader_pair.first,
            comp_shader);
        if (result == status_t::ERROR) { break; }
    }
    glLinkProgram(shader_id);
    result = Check_Compile_Errors(shader_id, "PROGRAM");
    return result;
}



/* ============================================================================
 * --------------------------------- Read Shaders
 * Read the shader code from the located text file
 * ============================================================================
 */
status_t Shader::Read_Shaders   (
    // ================================= Parameters
        const   std::string   shader_path,
                std::string&  shader_code   ) const {


    // ================================= Code

    try {
        std::ifstream shader_file(shader_path);
        shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
        std::stringstream shader_stream;
        shader_stream   << shader_file.rdbuf();
        shader_code     = shader_stream.str();

        return status_t::SUCCESS;


    }catch (const std::ifstream::failure& e) {
        Logger::log(  "Shader [" + shader_name + "]",
                            "Error File I/O: " + std::string(e.what()));

    }catch (const std::exception& e) {
        Logger::log(  "Shader [" + shader_name + "]",
                            "Error: " + std::string(e.what()));
    }

    return status_t::ERROR;
}

/* ============================================================================
 * --------------------------------- Compile Shaders
 * Compile the shader code
 * ============================================================================
 */
status_t Shader::Compile_Shader(
    // ================================= Parameters
    const shader_type_t   shader_type,
    const char*                 shader_code,
    GLuint&                     comp_shader ) const {

    // ================================= Code

    comp_shader =   glCreateShader  (To_GL(shader_type));
                    glShaderSource  (comp_shader, 1, &shader_code, NULL);
                    glCompileShader (comp_shader);

    return Check_Compile_Errors(comp_shader, To_String(shader_type));  
}


/* ============================================================================
 * --------------------------------- Link Shaders
 * Link the compiled shader
 * ============================================================================
 */
status_t Shader::Attach_Shader( const shader_type_t   shader_type,
                                    const GLuint                comp_shader 
                                  ) const {

    glAttachShader(shader_id, comp_shader);
    glDeleteShader(comp_shader);

    return status_t::SUCCESS;
};

/* ============================================================================
 * --------------------------------- Check Compile Errors
 * Check for compilation Errors
 * ============================================================================
 */
status_t Shader::Check_Compile_Errors( const GLuint      compile_shader,
                                             const std::string type
                                           ) const {
    GLint success;
    GLchar infoLog[1024];


    if (type != "PROGRAM") {
        glGetShaderiv(compile_shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(compile_shader, 1024, NULL, infoLog);
            Logger::log(
                "Shader [" + shader_name + "]",
                "Error: Compilation of " + type +
                "\n -------------------------------------------------------\n"
                                        + infoLog +
                "\n -------------------------------------------------------");
            return status_t::ERROR;
        }

    } else {
        glGetProgramiv(compile_shader, GL_LINK_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(compile_shader, 1024, NULL, infoLog);
            Logger::log(
                "Shader [" + shader_name + "]",
                "Error: Linking of " + type +
                "\n -------------------------------------------------------\n"
                                        + infoLog +
                "\n -------------------------------------------------------");
            return status_t::ERROR;
        }
    }

    return status_t::SUCCESS;
}
}

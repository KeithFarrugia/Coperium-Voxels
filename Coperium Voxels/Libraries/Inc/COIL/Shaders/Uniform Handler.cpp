#include "Shader.h"
#include <GLAD/glad.h>

namespace Coil {

/* ============================================================================
 * --------------------------------- Get Uniform									
 * ============================================================================
 */
int Shader::Get_Uniform(const char* uniform_name) const {
	int location = glGetUniformLocation(shader_id, uniform_name);
	if (location == -1) {
		Logger::log(
			"Shader [" + shader_name + "]",
			"Error : Uniform [" + std::string(uniform_name) + "] - Not Found ");
	}
	return location;
}

/* ============================================================================
 * --------------------------------- Set Boolean
 * ============================================================================
 */
void Shader::Set_Bool(const char* uniform_name, bool value) const {
	int location = Get_Uniform(uniform_name);
	if (location != -1) {
		glUniform1i(location, static_cast<int>(value));
	}
}

void Shader::Set_Bool(unsigned int location, bool value) const {
	if (static_cast<int>(location) != -1) {
		glUniform1i(location, static_cast<int>(value));
	}
}

/* ============================================================================
 * --------------------------------- Set Integer
 * ============================================================================
 */
void Shader::Set_Int(const char* uniform_name, int value) const {
	int location = Get_Uniform(uniform_name);
	if (location != -1) {
		glUniform1i(location, value);
	}
}

void Shader::Set_Int(unsigned int location, int value) const {
	if (static_cast<int>(location) != -1) {
		glUniform1i(location, value);
	}
}

/* ============================================================================
 * --------------------------------- Set Float
 * ============================================================================
 */
void Shader::Set_Float(const char* uniform_name, float value) const {
	int location = Get_Uniform(uniform_name);
	if (location != -1) {
		glUniform1f(location, value);
	}
}

void Shader::Set_Float(unsigned int location, float value) const {
	if (static_cast<int>(location) != -1) {
		glUniform1f(location, value);
	}
}

/* ============================================================================
 * --------------------------------- Set Vector (size 3)
 * ============================================================================
 */
void Shader::Set_Vec3(const char* uniform_name, const glm::vec3 vector) const {
	int location = Get_Uniform(uniform_name);
	if (location != -1) {
		glUniform3f(location, vector.x, vector.y, vector.z);
	}
}

void Shader::Set_Vec3(unsigned int location, const glm::vec3 vector) const {
	if (static_cast<int>(location) != -1) {
		glUniform3f(location, vector.x, vector.y, vector.z);
	}
}

/* ============================================================================
 * --------------------------------- Set Vector (size 4)
 * ============================================================================
 */
void Shader::Set_Vec4(const char* uniform_name, const glm::vec4 value) const {
	int location = Get_Uniform(uniform_name);
	if (location != -1) {
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
}

void Shader::Set_Vec4(unsigned int location, const glm::vec4 value) const {
	if (static_cast<int>(location) != -1) {
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
}

/* ============================================================================
 * --------------------------------- Set Matrix 4x4
 * ============================================================================
 */
void Shader::Set_Matrix4(const char* uniform_name, const glm::mat4 value) const {
	int location = Get_Uniform(uniform_name);
	if (location != -1) {
		glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
	}
}

void Shader::Set_Matrix4(unsigned int location, const glm::mat4 value) const {
	if (static_cast<int>(location) != -1) {
		glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
	}
}

}


#include <GLAD/glad.h>
#include "Buffers.h"

namespace Coil {

/* ============================================================================
 * --------------------------------- Unbind VBO
 * Unbinds the current VBO by setting the current VBO to 0
 * ============================================================================
 */
void Unbind_VBO() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/* ============================================================================
 * --------------------------------- Bind VBO
 * Binds the VBO to the passed VBO
 * ============================================================================
 */
void Bind_VBO(GLuint vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

/* ============================================================================
 * --------------------------------- Delete VBO
 * Deletes the VBO by releasing the resources associated with it
 * ============================================================================
 */
void Delete_VBO(const GLuint& vbo) {
    glDeleteBuffers(1, &vbo);
}

/* ============================================================================
 * --------------------------------- Create VBO
 * Creates a VBO, binds it, and initializes it with the provided vertex data
 * 
 * ------ Parameters ------
 * vbo          Reference to the VBO identifier
 * vertices     Pointer to the vertex data
 * type_size    Size of one element in bytes
 * num_elements Number of elements in the vertex data
 * ============================================================================
 */
void Create_VBO(
    GLuint&         vbo,        const void*     vertices,
    const GLsizei   type_size,  const GLsizei   num_elements
){

    glGenBuffers(1, &vbo);
    Bind_VBO(vbo);

    glBufferData(
        GL_ARRAY_BUFFER, 
        type_size * num_elements, 
        vertices, 
        GL_STATIC_DRAW
    );

    Unbind_VBO();
}


};

#include <GLAD/glad.h>
#include "Buffers.h"



namespace Coil {

/* ============================================================================
 * --------------------------------- Unbind VAO
 * Unbinds the current VAO by setting the current VAO to 0 
 * ============================================================================
 */
void Unbind_VAO() {
    glBindVertexArray(0);
}

/* ============================================================================
 * --------------------------------- Bind VAO
 * Binds the VAO to the passed VAO 
 * ============================================================================
 */
void Bind_VAO(const GLuint vao) {
    glBindVertexArray(vao);
}

/* ============================================================================
 * --------------------------------- Create VAO
 * Generates a VAO
 * ============================================================================
 */
void Create_VAO(GLuint& vao) {
    glGenVertexArrays(1, &vao);
}

/* ============================================================================
 * --------------------------------- Delete VAO
 * Deletes the VAO by releasing the resources associated with it
 * ============================================================================
 */
void Delete_VAO(const GLuint& vao) {
    glDeleteVertexArrays(1, &vao);
}

/* ============================================================================
 * --------------------------------- Link VBO
 * Links a VBO to a vertex attribute
 * 
 * ------ Parameters ------
 * vbo          The ID of the Vertex Buffer Object to link.
 * index        The index of the generic vertex attribute to be modified.
 * vec_size     The number of components per generic vertex attribute.
 * type         The data type of each component in the array.
 * stride       The byte offset between consecutive vertex attributes.
 * offset       The offset of the first component of the first attribute.
 * type         The datatype used for the vertex buffer
 * type_size    The size in bytes of the data type.
 * ============================================================================
 */
void Link_VBO(
    const GLuint    vbo,        const GLuint    index,
    const GLint     vec_size,   const GLsizei   stride,
    const GLuint    offset,     const GLenum    type,
    const GLsizei   type_size
){

    Bind_VBO(vbo);
    glVertexAttribPointer(
        index,
        vec_size,
        type,
        GL_FALSE,
        stride                   * type_size,
        (void*)(GLintptr)(offset * type_size)
    );
    glEnableVertexAttribArray(index);
    Unbind_VBO();
}
};
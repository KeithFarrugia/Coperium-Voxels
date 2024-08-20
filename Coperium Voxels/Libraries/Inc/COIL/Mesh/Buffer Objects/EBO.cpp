#include "Buffers.h"

namespace Coil {

/* ============================================================================
 * --------------------------------- Unbind EBO
 * Unbinds the current EBO by setting the current EBO to 0
 * ============================================================================
 */
void Unbind_EBO() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/* ============================================================================
 * --------------------------------- Bind EBO
 * Binds the EBO to the passed EBO
 * ============================================================================
 */
void Bind_EBO(GLuint ebo) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

/* ============================================================================
 * --------------------------------- Delete EBO
 * Deletes the EBO by releasing the resources associated with it
 * ============================================================================
 */
void Delete_EBO(const GLuint& ebo) {
    glDeleteBuffers(1, &ebo);
}

/* ============================================================================
 * --------------------------------- Create EBO
 * Creates an EBO, binds it, and initializes it with the provided index data
 * 
 * ------ Parameters ------
 * ebo          Reference to the EBO identifier
 * indices      Pointer to the index data
 * type_size    Size of one index element in bytes
 * num_elements Number of indices in the index data
 * ============================================================================
 */
void Create_EBO(
    GLuint&         ebo,        const void*     indices,
    const GLsizei   type_size,  const GLsizei   num_elements
){
    glGenBuffers(1, &ebo);
    Bind_EBO(ebo);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        type_size * num_elements,
        indices,
        GL_STATIC_DRAW
    );

    Unbind_EBO();
}
};

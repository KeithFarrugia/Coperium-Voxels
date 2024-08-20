#include "Basic_Mesh.h"

namespace Coil {

/* ============================================================================
 * ---------------------------- Constructor
 * Initializes all member variables to default values.
 * This sets up the mesh with no allocated resources.
 * ============================================================================
 */
Basic_Mesh::Basic_Mesh() {
    vao = 0;
    vbo = 0;
    ebo = 0;

    vertex_buffer_stride    = 0;

    vertex_buffer_size      = 0;
    vertex_buffer_length    = 0;
    vertex_buffer_type      = 0;

    index_buffer_size       = 0;
    index_buffer_length     = 0;
    index_buffer_type       = 0;
}

/* ============================================================================
 * ---------------------------- Configure Mesh (with indices)
 * Configures the mesh with the provided vertex and index data.
 * This method initializes the VAO, VBO, and EBO and stores the configuration
 * for later rendering.
 *
 * ------ Parameters ------
 * v            Pointer to the vertex data.
 * v_size       Size of one vertex element in bytes.
 * v_len        Number of vertex elements.
 * v_type       Data type of the vertex data (e.g., GL_FLOAT).
 * v_stride     Stride between consecutive vertex elements in bytes. 
 *              (e.g., xyzrgb => 6)
 * i            Pointer to the index data.
 * i_size       Size of one index element in bytes.
 * i_len        Number of index elements.
 * i_type       Data type of the index data (e.g., GL_UNSIGNED_INT).
 * ============================================================================
 */
void Basic_Mesh::Configure_Mesh(
    const void* v, const GLsizei   v_size,
    const GLsizei   v_len, const GLenum    v_type,
    const GLsizei   v_stride,
    const void*     i,      const GLsizei   i_size,   
    const GLsizei   i_len,  const GLenum    i_type
){
    Clear_Mesh();

    Create_VAO(vao);
    Create_VBO(vbo, v, v_size, v_len);
    Create_EBO(ebo, i, i_size, i_len);

    vertex_buffer_stride    = v_stride;

    vertex_buffer_size      = v_size;
    vertex_buffer_length    = v_len;
    vertex_buffer_type      = v_type;

    index_buffer_size       = i_size;
    index_buffer_length     = i_len;
    index_buffer_type       = i_type;
}

/* ============================================================================
 * ---------------------------- Configure Mesh (without indices)
 * Configures the mesh with the provided vertex data, but without indices.
 * This method initializes the VAO and VBO and stores the configuration
 * for later rendering.
 *
 * ------ Parameters ------
 * v         Pointer to the vertex data.
 * v_size    Size of one vertex element in bytes.
 * v_len     Number of vertex elements.
 * v_type    Data type of the vertex data (e.g., GL_FLOAT).
 * v_stride  Stride between consecutive vertex elements in bytes.
 * ============================================================================
 */
void Basic_Mesh::Configure_Mesh(
    const void*     v,      const GLsizei   v_size,
    const GLsizei   v_len,  const GLenum    v_type,
    const GLsizei   v_stride
){
    Clear_Mesh();

    Create_VAO(vao);
    Create_VBO(vbo, v, v_size, v_len);

    vertex_buffer_stride    = v_stride;
    
    vertex_buffer_size      = v_size;
    vertex_buffer_length    = v_len;
    vertex_buffer_type      = v_type;

}

/* ============================================================================
 * ---------------------------- Add Vertex Set
 * Adds a vertex attribute set to the current 
 * VAO using the provided configuration.
 * This method links a specific vertex buffer object 
 * (VBO) to a vertex attribute index in the VAO.
 *
 * ------ Parameters ------
 * index       Index of the vertex attribute in the VAO.
 * vec_size    Number of components per vertex attribute (e.g., 3 for vec3).
 * offset      Offset in bytes of where the attribute data starts in the VBO.
 * ============================================================================
 */
void Basic_Mesh::Add_Vertex_Set(
    const GLuint   index,
    const GLint    vec_size,
    const GLuint   offset
)const{
    Bind_VAO(vao);
    Link_VBO(
        vbo,
        index,
        vec_size,
        vertex_buffer_stride,
        offset,
        vertex_buffer_type,
        vertex_buffer_size
    );
    Unbind_VAO();
}

/* ============================================================================
* ---------------------------- Generate Mesh
* Generates the mesh by binding the VAO and issuing the draw call.
* If an EBO (Element Buffer Object) is present, it uses indexed drawing;
* otherwise, it uses array drawing.
* ============================================================================
*/
void Basic_Mesh::Draw_Mesh(bool wireframe) const {
    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Enable wireframe mode
    }

    Bind_VAO(vao);
    if (ebo != 0) {
        Bind_EBO(ebo);
        glDrawElements(
            GL_TRIANGLES,
            index_buffer_length,
            GL_UNSIGNED_INT,
            0
        );
        Unbind_EBO();

    }
    else {
        glDrawArrays(
            GL_TRIANGLES,
            0,
            vertex_buffer_length / vertex_buffer_stride
        );
    }
    Unbind_VAO();

    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Restore fill mode
    }
}
/* ============================================================================
 * ---------------------------- Clear Mesh
 * Clears the mesh by deleting the VAO, VBO, and EBO, if they exist.
 * This releases the resources associated with the mesh.
 * ============================================================================
 */
void Basic_Mesh::Clear_Mesh() {
    if (vao != 0) { Delete_VAO(vao);    }
    if (vbo != 0) { Delete_VBO(vbo);    }
    if (ebo != 0) { Delete_EBO(ebo);    }

    vertex_buffer_size      = 0;
    vertex_buffer_length    = 0;
    vertex_buffer_type      = 0;

    index_buffer_size       = 0;
    index_buffer_length     = 0;
    index_buffer_type       = 0;
}

/* ============================================================================
 * ---------------------------- Destructor
 * Ensures that all resources associated with the mesh are released when the
 * object is destroyed.
 * ============================================================================
 */
Basic_Mesh::~Basic_Mesh() {
    Clear_Mesh();
}

}
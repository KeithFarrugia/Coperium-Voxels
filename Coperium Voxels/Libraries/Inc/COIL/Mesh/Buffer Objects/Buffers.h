#pragma once
#ifndef COIL_BUFFERS_H
#define COIL_BUFFERS_H
#include <GLFW/glfw3.h>
#include <cstddef>

namespace Coil {

// --------------------------------- Vertex Array Object
void Unbind_VAO     ();
void Bind_VAO       (const GLuint   vao         );
void Create_VAO     (GLuint&        vao         );
void Delete_VAO     (const GLuint&  vao         );
void Link_VBO       (const GLuint   vbo,
                     const GLuint   index,
                     const GLint    vec_size,
                     const GLsizei  stride,
                     const GLuint   offset,
                     const GLenum   type,
                     const GLsizei  type_size       );

// --------------------------------- Vertex Buffer Object
void Unbind_VBO     ();
void Bind_VBO       (const GLuint   vbo             );
void Delete_VBO     (const GLuint&  vbo             );
void Create_VBO     (GLuint&        vbo, 
                     const void*    vertices,
                     const GLsizei  type_size, 
                     const GLsizei  num_elements   );

// --------------------------------- Element Buffer Object
void Unbind_EBO     ();
void Bind_EBO       (const GLuint   ebo             );
void Delete_EBO     (const GLuint&  ebo             );
void Create_EBO     (GLuint&        ebo, 
                     const void*    indices, 
                     const GLsizei  type_size,
                     const GLsizei  num_elements   );

}

#endif // !COIL_BUFFERS_H

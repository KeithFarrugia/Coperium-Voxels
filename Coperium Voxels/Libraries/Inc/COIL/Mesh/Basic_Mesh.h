#pragma once
#ifndef COIL_BASIC_MESH_H
#define COIL_BASIC_MESH_H

// --------------------------------- External Includes
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <memory> 

// --------------------------------- Internal Includes
#include "Buffer Objects/Buffers.h"


namespace Coil {

class Basic_Mesh{
public:
    Basic_Mesh();

    void Configure_Mesh (
        const void*     v,      const GLsizei   v_size, 
        const GLsizei   v_len,  const GLenum    v_type,
        const GLsizei   v_stride,
        const void*     i,      const GLsizei   i_size, 
        const GLsizei   i_len
    ); 
    void Configure_Mesh (
        const void*     v,      const GLsizei   v_size, 
        const GLsizei   v_len,  const GLenum    v_type, 
        const GLsizei   v_stride
    );

    void Configure_Index_Buffer(
        const void*     i,      const GLsizei   i_size,
        const GLsizei   i_len
    );

    void Add_Vertex_Set (
        const GLuint    index,  const GLint     vec_size,
        const GLuint    offset
    )const;

    void Add_Vertex_Set(
        const GLuint    index,  const GLint     v_size,
        const void*     v,      const GLsizei   type_size,
        const GLsizei   v_len,  const GLenum    v_type
    )const;

    void Draw_Mesh      (bool   wireframe = false) const;


    void Clear_Mesh     ();
    void Clean_Mesh     ();

    ~Basic_Mesh         ();
private:
    GLuint  vao;
    GLuint  vbo;
    GLuint  ebo;

    GLsizei vertex_buffer_stride;

    GLsizei vertex_buffer_size;
    GLsizei vertex_buffer_length;
    GLenum  vertex_buffer_type;

    GLsizei index_buffer_size;
    GLsizei index_buffer_length;

};

}
#endif // !COIL_BASIC_MESH_H
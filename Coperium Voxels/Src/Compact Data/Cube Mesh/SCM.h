#pragma once
#ifndef SIMPLE_CUBE_MESH_H
#define SIMPLE_CUBE_MESH_H

#include <GLFW/glfw3.h>

constexpr int SIMPLE_CUBE_SIZE     = 216;
constexpr int SIMPLE_CUBE_ELEMENTS = 6;

const GLfloat SIMPLE_CUBE[] = {
//    X      Y      Z            R     G    B
    // ------------------------------------------ Front face
    -0.5f,  0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,        1.0f, 1.0f, 1.0f,

    // ------------------------------------------ Back face
     0.5f,  0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,        1.0f, 1.0f, 1.0f,

    // ------------------------------------------ Left face
    -0.5f,  0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,        1.0f, 1.0f, 1.0f,

    // ------------------------------------------ Right face
     0.5f,  0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,        1.0f, 1.0f, 1.0f,

     // ------------------------------------------ Top face
    -0.5f,  0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,        1.0f, 1.0f, 1.0f,

    // ------------------------------------------ Bottom face
    -0.5f, -0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,        1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,        1.0f, 1.0f, 1.0f,
};

#endif // !SIMPLE_CUBE_MESH_H
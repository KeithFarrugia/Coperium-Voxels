#pragma once
#include <GLFW/glfw3.h>
constexpr GLfloat block_vertices[] = {
    // Positions           // Colors
    // Front face (Clockwise)
    -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,    // Top-left     
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,    // Top-right    
     0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,    // Bottom-right 
    -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,    // Top-left     
     0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,    // Bottom-right 
    -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,    // Bottom-left  

    // Back face (Clockwise)
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    // Top-left     (Yellow)
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    // Top-right    (Blue)
    -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    // Bottom-right (Green)
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    // Top-left     (Yellow)
    -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    // Bottom-right (Green)
     0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    // Bottom-left  (Red)

    // Left face (Clockwise)
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    // Top-left     
    -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,    // Top-right    (Blue)
    -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,    // Bottom-right (Green)
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    // Top-left     (Yellow)
    -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,    // Bottom-right (Green)
    -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    // Bottom-left  (Red)

    // Right face (Clockwise)
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,    // Top-left     (Yellow)
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    // Top-right    (Blue)
     0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    // Bottom-right (Green)
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,    // Top-left     (Yellow)
     0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    // Bottom-right (Green)
     0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,    // Bottom-left  (Red)

        // Top face (Clockwise)
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    // Top-left     (Yellow)
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    // Top-right    (Blue)
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,    // Bottom-right (Green)
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,    // Top-left     (Yellow)
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,    // Bottom-right (Green)
    -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,    // Bottom-left  (Red)

        // Bottom face (Clockwise)
    -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   // Top-left     (Yellow)
     0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   // Top-right    (Blue)
     0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   // Bottom-right (Green)
    -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   // Top-left     (Yellow)
     0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   // Bottom-right (Green)
    -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   // Bottom-left  (Red)
};



constexpr GLfloat default_block_vertices[] = {
    // Positions           // Colors
    // Front face (Clockwise)
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    // Top-left     (Yellow)
     0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    // Top-right    (Blue)
     0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    // Bottom-right (Green)
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    // Top-left     (Yellow)
     0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    // Bottom-right (Green)
    -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    // Bottom-left  (Red)

    // Back face (Clockwise)
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,    // Top-left     (Yellow)
    -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,    // Top-right    (Blue)
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    // Bottom-right (Green)
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,    // Top-left     (Yellow)
    -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    // Bottom-right (Green)
     0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,    // Bottom-left  (Red)

    // Left face (Clockwise)
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,    // Top-left     (Yellow)
    -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,    // Top-right    (Blue)
    -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,    // Bottom-right (Green)
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,    // Top-left     (Yellow)
    -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,    // Bottom-right (Green)
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,    // Bottom-left  (Red)

    // Right face (Clockwise)
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,    // Top-left     (Yellow)
     0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,    // Top-right    (Blue)
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    // Bottom-right (Green)
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,    // Top-left     (Yellow)
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,    // Bottom-right (Green)
     0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    // Bottom-left  (Red)

        // Top face (Clockwise)
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,    // Top-left     (Yellow)
     0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f,    // Top-right    (Blue)
     0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,    // Bottom-right (Green)
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,    // Top-left     (Yellow)
     0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,    // Bottom-right (Green)
    -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    // Bottom-left  (Red)

        // Bottom face (Clockwise)
    -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   // Top-left     (Yellow)
     0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   // Top-right    (Blue)
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   // Bottom-right (Green)
    -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   // Top-left     (Yellow)
     0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   // Bottom-right (Green)
    -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   // Bottom-left  (Red)
};
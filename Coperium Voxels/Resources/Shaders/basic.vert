#version 330 core

layout(location = 0) in vec3 aPos; // Vertex position attribute
layout(location = 1) in vec3 aColor; // Vertex color attribute

out vec3 vertexColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0); // Apply matrices
    vertexColor = aColor; // Pass color to fragment shader
}
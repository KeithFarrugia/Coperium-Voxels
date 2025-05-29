#version 330 core
layout (location = 0) in vec3 aPos;  // Quad vertex position
layout (location = 1) in vec2 aTexCoords;  // Unused but still here for compatibility

out vec3 frag_colour;  // Pass color to fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0);  // Directly pass position to clip space

    // Generate RGB colors based on position
    frag_colour = vec3(1.0,0.0,0.0);
}

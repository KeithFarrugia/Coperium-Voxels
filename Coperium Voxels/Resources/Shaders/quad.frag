#version 330 core
out vec4 FragColor;

in vec3 frag_colour;  // Receive color from vertex shader

void main()
{
    FragColor = vec4(frag_colour, 1.0);  // Output final color
}

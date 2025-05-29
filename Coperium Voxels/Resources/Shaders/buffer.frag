#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gColour;

in vec3 FragPos;
in vec3 Normal;
in vec4 VertexColor;

void main(){
    gPosition = FragPos;
    gNormal = normalize(Normal);
    gColour.rgb = VertexColor.rgb;
}


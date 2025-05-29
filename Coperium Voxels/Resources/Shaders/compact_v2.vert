#version 330 core

layout(location = 0) in float aPos;
layout(location = 1) in float aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 vertex_offset;

// Output vertex color
out vec4 vertexColor;

const float FRACTION_DIVISOR    = 32.0;
const float COLOUR_DIVISOR      = 255.0;

vec3 decodeValue(float encoded) {
    uint data = floatBitsToUint(encoded);

    // Decode X component
    bool  x_sign     = ((data >> 31) & 0x1u) != 0u;
    uint  x_mantissa =  (data >> 27) & 0x0Fu;
    uint  x_fraction =  (data >> 22) & 0x1Fu;
    float x_value    =   float(x_mantissa) + 
                        (float(x_fraction) / 
                         FRACTION_DIVISOR);

    if (x_sign) x_value = -x_value;

    // Decode Y component
    bool  y_sign     = ((data >> 21) & 0x1u) != 0u;
    uint  y_mantissa =  (data >> 15) & 0x3Fu;
    uint  y_fraction =  (data >> 10) & 0x1Fu;
    float y_value    =   float(y_mantissa) + 
                        (float(y_fraction) / 
                         FRACTION_DIVISOR);

    if (y_sign) y_value = -y_value;

    // Decode Z component
    bool  z_sign     = ((data >> 9) & 0x1u) != 0u;
    uint  z_mantissa =  (data >> 5) & 0x0Fu;
    uint  z_fraction =  (data >> 0) & 0x1Fu;
    float z_value    =   float(z_mantissa) + 
                        (float(z_fraction) / 
                         FRACTION_DIVISOR);

    if (z_sign) z_value = -z_value;

    // Return the decoded vec3 value
    return vec3(x_value, y_value, z_value);
}

vec4 decodeColor(float encoded) {
    uint data = floatBitsToUint(encoded);

    float r_value = float((data >> 24) & 0xFFu) / COLOUR_DIVISOR;
    float g_value = float((data >> 16) & 0xFFu) / COLOUR_DIVISOR;
    float b_value = float((data >> 8 ) & 0xFFu) / COLOUR_DIVISOR;
    float a_value = float((data >> 0 ) & 0xFFu) / COLOUR_DIVISOR;

    return vec4(r_value, g_value, b_value, a_value);
}

void main() {
    vec3 vert = decodeValue(aPos);
    vert = vec3(    vert.x + vertex_offset.x, 
                    vert.y + vertex_offset.y,
                    vert.z + vertex_offset.z);

    gl_Position = projection * view * model * vec4(vert, 1.0);
    vertexColor = decodeColor(aColor);
}

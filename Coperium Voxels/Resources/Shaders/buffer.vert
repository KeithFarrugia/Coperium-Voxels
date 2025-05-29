#version 330 core

/* ============================================================================
 * --------------------------- Inputs
 * Vertex attributes: packed position, colour, and normal.
 * ============================================================================
 */
layout (location = 0) in float aPosPacked;
layout (location = 1) in float aColorPacked;
layout (location = 2) in float aNormalPacked;

/* ============================================================================
 * --------------------------- Outputs
 * Passing data to the fragment shader.
 * ============================================================================
 */
out vec3 FragPos;
out vec3 Normal;
out vec4 VertexColor;

/* ============================================================================
 * --------------------------- Uniforms
 * Transformation matrices and vertex offset.
 * ============================================================================
 */
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 vertex_offset;

/* ============================================================================
 * --------------------------- Constants
 * Scaling factors for decoding.
 * ============================================================================
 */
const float MAG_SCALE          = 511.0;
const float FRACTION_DIVISOR   = 32.0;
const float COLOUR_DIVISOR     = 255.0;


/* ============================================================================
 * --------------------------- DecodeNormal
 * Decodes a single float (CND-packed) back into a normalized vec3.
 *
 * ------ Parameters ------
 * encoded : The float containing packed normal data.
 *
 * Returns a unit-length normal vector.
 * ============================================================================
 */
vec3 DecodeNormal(float encoded) {
    uint data = floatBitsToUint(encoded);

    // Decode X
    bool x_sign = ((data >> 31) & 0x1u) != 0u;
    uint x_mag = (data >> 22) & 0x1FFu; // 9 bits
    float x = float(x_mag) / MAG_SCALE;
    if (x_sign) x = -x;

    // Decode Y
    bool y_sign = ((data >> 21) & 0x1u) != 0u;
    uint y_mag = (data >> 12) & 0x1FFu; // 9 bits
    float y = float(y_mag) / MAG_SCALE;
    if (y_sign) y = -y;

    // Decode Z
    bool z_sign = ((data >> 11) & 0x1u) != 0u;
    uint z_mag = (data >> 2) & 0x1FFu; // 9 bits
    float z = float(z_mag) / MAG_SCALE;
    if (z_sign) z = -z;

    // Return normalized normal
    return normalize(vec3(x, y, z));
}
/* ============================================================================
 * --------------------------- DecodeValue
 * Decodes a packed position float (CLD-packed) into vec3.
 *
 * ------ Parameters ------
 * encoded : The float containing packed position data.
 *
 * Returns the decoded position in object space.
 * ============================================================================
 */
vec3 DecodeValue(float encoded) {
    uint data = floatBitsToUint(encoded);

    // Decode X
    bool  x_sign     = ((data >> 31) & 0x1u) != 0u;
    uint  x_mantissa = (data >> 27) & 0x0Fu;
    uint  x_fraction = (data >> 22) & 0x1Fu;
    float x = float(x_mantissa) + (float(x_fraction) / FRACTION_DIVISOR);
    if (x_sign) x = -x;

    // Decode Y
    bool  y_sign     = ((data >> 21) & 0x1u) != 0u;
    uint  y_mantissa = (data >> 15) & 0x3Fu;
    uint  y_fraction = (data >> 10) & 0x1Fu;
    float y = float(y_mantissa) + (float(y_fraction) / FRACTION_DIVISOR);
    if (y_sign) y = -y;

    // Decode Z
    bool  z_sign     = ((data >>  9) & 0x1u) != 0u;
    uint  z_mantissa = (data >>  5) & 0x0Fu;
    uint  z_fraction = (data >>  0) & 0x1Fu;
    float z = float(z_mantissa) + (float(z_fraction) / FRACTION_DIVISOR);
    if (z_sign) z = -z;

    return vec3(x, y, z);
}

/* ============================================================================
 * --------------------------- DecodeColor
 * Decodes a packed colour float (CCD-packed) into vec4.
 *
 * ------ Parameters ------
 * encoded : The float containing packed RGBA colour data.
 *
 * Returns the decoded colour with components in [0,1].
 * ============================================================================
 */
vec4 DecodeColor(float encoded) {
    uint data = floatBitsToUint(encoded);
    float r = float((data >> 24) & 0xFFu) / COLOUR_DIVISOR;
    float g = float((data >> 16) & 0xFFu) / COLOUR_DIVISOR;
    float b = float((data >>  8) & 0xFFu) / COLOUR_DIVISOR;
    float a = float((data >>  0) & 0xFFu) / COLOUR_DIVISOR;
    return vec4(r, g, b, a);
}

/* ============================================================================
 * --------------------------- main
 * Entry point: decode attributes, apply transformations, and emit gl_Position.
 * ============================================================================
 */
void main() {
    // Decode and offset position
    vec3 pos = DecodeValue(aPosPacked) + vertex_offset;

    // Decode and pass colour
    VertexColor = DecodeColor(aColorPacked);

    // Decode and pass normal
    Normal = DecodeNormal(aNormalPacked);

    // Compute world-space position
    vec4 worldPos = model * vec4(pos, 1.0);
    FragPos = worldPos.xyz;

    // Final clip-space position
    gl_Position = projection * view * worldPos;
}

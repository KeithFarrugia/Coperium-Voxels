#include "Block.h"
// Getters
uint8_t get_x(block_data_t xyz_rgb) {
    return (xyz_rgb.data >> 28) & MASK_4_BITS;
}

uint8_t get_y(block_data_t xyz_rgb) {
    return (xyz_rgb.data >> 24) & MASK_4_BITS;
}

uint8_t get_z(block_data_t xyz_rgb) {
    return (xyz_rgb.data >> 20) & MASK_4_BITS;
}

uint8_t get_r(block_data_t xyz_rgb) {
    return (xyz_rgb.data >> 16) & MASK_4_BITS;
}

uint8_t get_g(block_data_t xyz_rgb) {
    return (xyz_rgb.data >> 12) & MASK_4_BITS;
}

uint8_t get_b(block_data_t xyz_rgb) {
    return (xyz_rgb.data >> 8) & MASK_4_BITS;
}

// Setters
void set_x(block_data_t& xyz_rgb, uint8_t x) {
    xyz_rgb.data =
        (xyz_rgb.data & ~(MASK_4_BITS << 28)) |
        ((x & MASK_4_BITS) << 28);
}

void set_y(block_data_t& xyz_rgb, uint8_t y) {
    xyz_rgb.data =
        (xyz_rgb.data & ~(MASK_4_BITS << 24)) |
        ((y & MASK_4_BITS) << 24);
}

void set_z(block_data_t& xyz_rgb, uint8_t z) {
    xyz_rgb.data =
        (xyz_rgb.data & ~(MASK_4_BITS << 20)) |
        ((z & MASK_4_BITS) << 20);
}

void set_r(block_data_t& xyz_rgb, uint8_t r) {
    xyz_rgb.data =
        (xyz_rgb.data & ~(MASK_4_BITS << 16)) |
        ((r & MASK_4_BITS) << 16);
}

void set_g(block_data_t& xyz_rgb, uint8_t g) {
    xyz_rgb.data =
        (xyz_rgb.data & ~(MASK_4_BITS << 12)) |
        ((g & MASK_4_BITS) << 12);
}

void set_b(block_data_t& xyz_rgb, uint8_t b) {
    xyz_rgb.data =
        (xyz_rgb.data & ~(MASK_4_BITS << 8)) |
        ((b & MASK_4_BITS) << 8);
}

// Set all values at once
void set_all(
    block_data_t& xyz_rgb,
    uint8_t x,
    uint8_t y,
    uint8_t z,
    uint8_t r,
    uint8_t g,
    uint8_t b
) {
    xyz_rgb.data =
        ((x & MASK_4_BITS) << 28) |
        ((y & MASK_4_BITS) << 24) |
        ((z & MASK_4_BITS) << 20) |
        ((r & MASK_4_BITS) << 16) |
        ((g & MASK_4_BITS) << 12) |
        ((b & MASK_4_BITS) << 8);
}

void copyGLfloatArray(const GLfloat* source, GLfloat* destination, size_t size) {
    std::copy(source, source + size, destination);
}

std::unique_ptr<GLfloat[]> generate_cube_vertices(block_data_t xyz_rgb) {
    float x = get_x(xyz_rgb);
    float y = get_y(xyz_rgb);
    float z = get_z(xyz_rgb);

    float r = (float)get_r(xyz_rgb)/16;
    float g = (float)get_g(xyz_rgb)/16;
    float b = (float)get_b(xyz_rgb)/16;

    auto cube_mesh = std::make_unique<GLfloat[]>(216);

    copyGLfloatArray(block_vertices, cube_mesh.get(), 216);

    for (int i = 0; i < 216; i += 6) {
        cube_mesh[i + 0] += x;
        cube_mesh[i + 1] += y;
        cube_mesh[i + 2] += z;

        cube_mesh[i + 3] *= r;
        cube_mesh[i + 4] *= g;
        cube_mesh[i + 5] *= b;
    }

    return cube_mesh;
}
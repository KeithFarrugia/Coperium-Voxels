#pragma once
#ifndef BLOCK_H
#define BLOCK_H
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <algorithm>
#include <memory> 

#include "Block Mesh.h"

typedef struct {
    uint32_t data;
} block_data_t;

// Helper macros to extract and set values
constexpr int MASK_4_BITS = 0xF;

// Getters (no pointers or references)
uint8_t get_x(block_data_t xyz_rgb);
uint8_t get_y(block_data_t xyz_rgb);
uint8_t get_z(block_data_t xyz_rgb);
uint8_t get_r(block_data_t xyz_rgb);
uint8_t get_g(block_data_t xyz_rgb);
uint8_t get_b(block_data_t xyz_rgb);

// Setters (use references)
void set_x(block_data_t& xyz_rgb, uint8_t x);
void set_y(block_data_t& xyz_rgb, uint8_t y);
void set_z(block_data_t& xyz_rgb, uint8_t z);
void set_r(block_data_t& xyz_rgb, uint8_t r);
void set_g(block_data_t& xyz_rgb, uint8_t g);
void set_b(block_data_t& xyz_rgb, uint8_t b);


// Set all values at once
void set_all    (block_data_t& xyz_rgb,
                 uint8_t  x, 
                 uint8_t  y, 
                 uint8_t  z, 
                 uint8_t  r, 
                 uint8_t  g, 
                 uint8_t  b);

std::unique_ptr<GLfloat[]> generate_cube_vertices(block_data_t xyz_rgb);



#endif // !BLOCK_H

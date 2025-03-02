#pragma once

#ifndef COMPACT_CUBE_MESH_SEPERABLE_H
#define COMPACT_CUBE_MESH_SEPERABLE_H


#include <memory>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <vector>

#include "../Compact Location Data/CLD.h"
#include "../Compact Colour Data/CCD.h"

constexpr int FACE_INDEX_SIZE   = 6;    // number of indices per face
constexpr int FACE_VERT_SIZE    = 20;   // Length of face vertex array in floats
constexpr int FACE_NUM_ELEMENTS = 5;    // Length of number of floats in a vertex

typedef enum  {
    FRONT_FACE  =   0x1 << 0,  // 1st bit
    BACK_FACE   =   0x1 << 1,  // 2nd bit
    LEFT_FACE   =   0x1 << 2,  // 3rd bit
    RIGHT_FACE  =   0x1 << 3,  // 4th bit
    TOP_FACE    =   0x1 << 4,  // 5th bit
    BOTTOM_FACE =   0x1 << 5,  // 6th bit
    ALL_FACES   =   FRONT_FACE  | 
                    BACK_FACE   | 
                    LEFT_FACE   | 
                    RIGHT_FACE  | 
                    TOP_FACE    | 
                    BOTTOM_FACE
}cube_faces_t;

const GLfloat FRONT_FACE_MESH   [] = {
    CLD::Compact(-0.5f,  0.5f,  0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),        0.0f,  0.0f,  1.0f,
    CLD::Compact( 0.5f,  0.5f,  0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),        0.0f,  0.0f,  1.0f,
    CLD::Compact( 0.5f, -0.5f,  0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),        0.0f,  0.0f,  1.0f,
    CLD::Compact(-0.5f, -0.5f,  0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),        0.0f,  0.0f,  1.0f,
};

const GLfloat BACK_FACE_MESH    [] = {
    CLD::Compact( 0.5f,  0.5f, -0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),         0.0f,  0.0f, -1.0f,
    CLD::Compact(-0.5f,  0.5f, -0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),         0.0f,  0.0f, -1.0f,
    CLD::Compact(-0.5f, -0.5f, -0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),         0.0f,  0.0f, -1.0f,
    CLD::Compact( 0.5f, -0.5f, -0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),         0.0f,  0.0f, -1.0f,
};

const GLfloat LEFT_FACE_MESH    [] = {
    CLD::Compact(-0.5f,  0.5f, -0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),        -1.0f,  0.0f,  0.0f,
    CLD::Compact(-0.5f,  0.5f,  0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),        -1.0f,  0.0f,  0.0f,
    CLD::Compact(-0.5f, -0.5f,  0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),        -1.0f,  0.0f,  0.0f,
    CLD::Compact(-0.5f, -0.5f, -0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),        -1.0f,  0.0f,  0.0f,
};

const GLfloat RIGHT_FACE_MESH   [] = {
    CLD::Compact( 0.5f,  0.5f,  0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),         1.0f,  0.0f,  0.0f,
    CLD::Compact( 0.5f,  0.5f, -0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),         1.0f,  0.0f,  0.0f,
    CLD::Compact( 0.5f, -0.5f, -0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),         1.0f,  0.0f,  0.0f,
    CLD::Compact( 0.5f, -0.5f,  0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),         1.0f,  0.0f,  0.0f,
};

const GLfloat TOP_FACE_MESH     [] = {
    CLD::Compact(-0.5f,  0.5f, -0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),          0.0f,  1.0f,  0.0f,
    CLD::Compact( 0.5f,  0.5f, -0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),          0.0f,  1.0f,  0.0f,
    CLD::Compact( 0.5f,  0.5f,  0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),          0.0f,  1.0f,  0.0f,
    CLD::Compact(-0.5f,  0.5f,  0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),          0.0f,  1.0f,  0.0f,
};

const GLfloat BOTTOM_FACE_MESH  [] = {
    CLD::Compact(-0.5f, -0.5f,  0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),          0.0f, -1.0f,  0.0f,
    CLD::Compact( 0.5f, -0.5f,  0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),          0.0f, -1.0f,  0.0f,
    CLD::Compact( 0.5f, -0.5f, -0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),          0.0f, -1.0f,  0.0f,
    CLD::Compact(-0.5f, -0.5f, -0.5f), CCD::Compact(1.0f, 1.0f, 1.0f),          0.0f, -1.0f,  0.0f,
};

const GLuint FACE_INDEX_MESH    [] = { 0, 1, 2, 0, 2, 3 };


void Add_Face(
    glm::vec3               vert_pos_offset ,   glm::vec3               vert_colour ,
    std::vector<GLfloat>&   vertex_mesh     ,   std::vector<GLuint>&    index_mesh  ,
    const GLfloat*          vertices        ,   const GLuint*           indexes     ,
    int&                    v_offset        ,   int&                    i_offset    ,
    int                     v_element_count ,
    int                     v_array_size    ,   int                     i_array_size
);


void Add_Cube_Mesh(
    glm::vec3               vert_pos_offset ,   glm::vec3               vert_colour,
    std::vector<GLfloat>&   vertex_mesh     ,   std::vector<GLuint>&    index_mesh,
    int&                    vertex_offset   ,   int&                    index_offset,
    uint8_t                 face_flags
);

#endif // !COMPACT_CUBE_MESH_SEPERABLE_H
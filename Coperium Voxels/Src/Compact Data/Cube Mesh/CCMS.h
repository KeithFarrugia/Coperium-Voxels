#pragma once

#ifndef COMPACT_CUBE_MESH_SEPARABLE_H
#define COMPACT_CUBE_MESH_SEPARABLE_H

#include <memory>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <vector>

#include "../Compact Location Data/CLD.h"
#include "../Compact Colour Data/CCD.h"
#include "../Compact Normal Data/CND.h"

constexpr int FACE_INDEX_SIZE   = 6;    // number of indices per face
constexpr int FACE_VERT_SIZE    = 12;   // x,y location + colour + normal (1 float each) => 1+1+1+1 = 4 floats per vertex; 4*3 vertices =12
constexpr int FACE_NUM_ELEMENTS = 3;    // floats per vertex (pos, col, normal)

typedef enum cube_faces_t : uint8_t {
    FRONT_SHIFT  = 0,    BACK_SHIFT   = 1,
    LEFT_SHIFT   = 2,    RIGHT_SHIFT  = 3,
    TOP_SHIFT    = 4,    BOTTOM_SHIFT = 5,

    FRONT_FACE   = 0x1 << FRONT_SHIFT,   BACK_FACE   = 0x1 << BACK_SHIFT  ,
    LEFT_FACE    = 0x1 << LEFT_SHIFT ,   RIGHT_FACE  = 0x1 << RIGHT_SHIFT ,
    TOP_FACE     = 0x1 << TOP_SHIFT  ,   BOTTOM_FACE = 0x1 << BOTTOM_SHIFT,

    ALL_FACES    = FRONT_FACE | BACK_FACE  | 
                   LEFT_FACE  | RIGHT_FACE | 
                   TOP_FACE   | BOTTOM_FACE
} cube_faces_t;

inline cube_faces_t operator|(cube_faces_t lhs, cube_faces_t rhs) {
    return static_cast<cube_faces_t>(
        static_cast<std::underlying_type_t<cube_faces_t>>(lhs) |
        static_cast<std::underlying_type_t<cube_faces_t>>(rhs)
    );
}

inline cube_faces_t& operator|=(cube_faces_t& lhs, cube_faces_t rhs) {
    lhs = lhs | rhs;
    return lhs;
}

// Vertex layout per face: 4 vertices, each has:
//    - 1 float: position packed via CLD::Compact
//    - 1 float: colour   packed via CCD::Compact
//    - 1 float: normal   packed via CND::Compact

const GLfloat FRONT_FACE_MESH[] = {
    CLD::Compact(-0.5f,  0.5f,  0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 0,  0,  1),
    CLD::Compact( 0.5f,  0.5f,  0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 0,  0,  1),
    CLD::Compact( 0.5f, -0.5f,  0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 0,  0,  1),
    CLD::Compact(-0.5f, -0.5f,  0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 0,  0,  1)
};

const GLfloat BACK_FACE_MESH[] = {
    CLD::Compact( 0.5f,  0.5f, -0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 0,  0, -1),
    CLD::Compact(-0.5f,  0.5f, -0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 0,  0, -1),
    CLD::Compact(-0.5f, -0.5f, -0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 0,  0, -1),
    CLD::Compact( 0.5f, -0.5f, -0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 0,  0, -1)
};

const GLfloat LEFT_FACE_MESH[] = {
    CLD::Compact(-0.5f,  0.5f, -0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact(-1,  0,  0),
    CLD::Compact(-0.5f,  0.5f,  0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact(-1,  0,  0),
    CLD::Compact(-0.5f, -0.5f,  0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact(-1,  0,  0),
    CLD::Compact(-0.5f, -0.5f, -0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact(-1,  0,  0)
};

const GLfloat RIGHT_FACE_MESH[] = {
    CLD::Compact( 0.5f,  0.5f,  0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 1,  0,  0),
    CLD::Compact( 0.5f,  0.5f, -0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 1,  0,  0),
    CLD::Compact( 0.5f, -0.5f, -0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 1,  0,  0),
    CLD::Compact( 0.5f, -0.5f,  0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 1,  0,  0)
};

const GLfloat TOP_FACE_MESH[] = {
    CLD::Compact(-0.5f,  0.5f, -0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 0,  1,  0),
    CLD::Compact( 0.5f,  0.5f, -0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 0,  1,  0),
    CLD::Compact( 0.5f,  0.5f,  0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 0,  1,  0),
    CLD::Compact(-0.5f,  0.5f,  0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 0,  1,  0)
};

const GLfloat BOTTOM_FACE_MESH[] = {
    CLD::Compact(-0.5f, -0.5f,  0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 0, -1,  0),
    CLD::Compact( 0.5f, -0.5f,  0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 0, -1,  0),
    CLD::Compact( 0.5f, -0.5f, -0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 0, -1,  0),
    CLD::Compact(-0.5f, -0.5f, -0.5f), CCD::Compact(1.0f,  1.0f,  1.0f), CND::Compact( 0, -1,  0)
};

const GLuint FACE_INDEX_MESH[] = { 0, 1, 2, 0, 2, 3 };




void Add_Cube_Mesh(
    const glm::vec3&        vert_pos_offset ,   const glm::vec3&        vert_colour ,
    std::vector<GLfloat>&   vertex_mesh     ,   std::vector<GLuint>&    index_mesh  ,
    int&                    vertex_offset   ,   int&                    index_offset,
    cube_faces_t            face_flags      ,   int                     scale = 1
);

#endif // COMPACT_CUBE_MESH_SEPARABLE_H

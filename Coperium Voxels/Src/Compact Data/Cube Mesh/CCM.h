#pragma once
#ifndef COMPACT_CUBE_MESH_H
#define COMPACT_CUBE_MESH_H

#include "../Compact Location Data/CLD.h"
#include "../Compact Colour Data/CCD.h"

constexpr int COMPACT_CUBE_INDEX_SIZE   = 36;
constexpr int COMPACT_CUBE_SIZE         = 48;
constexpr int COMPACT_CUBE_ELEMENTS     = 2;

const GLfloat COMPACT_CUBE[] = {
    // Front Face
    CLD::Compact( -0.5f,  0.5f,  0.5f ),    CCD::Compact( 1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f,  0.5f,  0.5f ),    CCD::Compact( 1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f, -0.5f,  0.5f ),    CCD::Compact( 1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f, -0.5f,  0.5f ),    CCD::Compact( 1.0f, 1.0f, 1.0f),
         
    // Back face
    CLD::Compact(  0.5f,  0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f,  0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f, -0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f, -0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),

    // Left face
    CLD::Compact( -0.5f,  0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f,  0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f, -0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f, -0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),

    // Right face
    CLD::Compact(  0.5f,  0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f,  0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f, -0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f, -0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),

    // Top face
    CLD::Compact( -0.5f,  0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f,  0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f,  0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f,  0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),

    // Bottom face
    CLD::Compact( -0.5f, -0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f, -0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f, -0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f, -0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f)
};

const GLuint COMPACT_CUBE_INDICES[] = {
    // Front face
     0,  1,  2,      0,  2,  3,
    // Back face
     4,  5,  6,      4,  6,  7,
    // Left face
     8,  9, 10,      8, 10, 11,
    // Right face
    12, 13, 14,     12, 14, 15,
    // Top face
    16, 17, 18,     16, 18, 19,
    // Bottom face
    20, 21, 22,     20, 22, 23
};

#endif // !COMPACT_CUBE_MESH_H

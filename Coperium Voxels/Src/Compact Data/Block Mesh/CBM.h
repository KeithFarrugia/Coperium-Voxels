#pragma once
#ifndef CBM_H
#define CBM_H

#include "../Compact Location Data/CLD.h"
#include "../Compact Colour Data/CCD.h"

constexpr int COMPACT_CUBE_SIZE     = 72;
constexpr int COMPACT_CUBE_ELEMENTS = 2;

const GLfloat COMPACT_CUBE[] = {
    CLD::Compact( -0.5f,  0.5f,  0.5f ),    CCD::Compact( 1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f,  0.5f,  0.5f ),    CCD::Compact( 1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f, -0.5f,  0.5f ),    CCD::Compact( 1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f,  0.5f,  0.5f ),    CCD::Compact( 1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f, -0.5f,  0.5f ),    CCD::Compact( 1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f, -0.5f,  0.5f ),    CCD::Compact( 1.0f, 1.0f, 1.0f),
         
    // Back face
    CLD::Compact(  0.5f,  0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f,  0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f, -0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f,  0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f, -0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f, -0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),

    // Left face
    CLD::Compact( -0.5f,  0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f,  0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f, -0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f,  0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f, -0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f, -0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),

    // Right face
    CLD::Compact(  0.5f,  0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f,  0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f, -0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f,  0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f, -0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f, -0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),

    // Top face
    CLD::Compact( -0.5f,  0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f,  0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f,  0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f,  0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f,  0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f,  0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),

    // Bottom face
    CLD::Compact( -0.5f, -0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f, -0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f, -0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f, -0.5f,  0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact(  0.5f, -0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f),
    CLD::Compact( -0.5f, -0.5f, -0.5f ),    CCD::Compact(1.0f, 1.0f, 1.0f)
};



#endif // !CBM_H

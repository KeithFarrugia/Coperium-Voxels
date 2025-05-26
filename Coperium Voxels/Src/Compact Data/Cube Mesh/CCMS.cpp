// CompactCubeMeshSeparable.cpp
#include "CCMS.h"
/* ============================================================================
 * --------------------------- Add_Face
 * Handles insertion and transformation of a single face into mesh arrays.
 *
 * ------ Parameters ------
 * pos_offset    : Position offset to apply (including scale centering).
 * colour_factor : Colour multiplier.
 * verts         : Reference to vertex float buffer.
 * inds          : Reference to index buffer.
 * face_data     : Pointer to 4 packed vertices (12 floats).
 * index_data    : Pointer to 6 indices for two triangles.
 * v_offset      : Current vertex offset (in/out).
 * i_offset      : Current index offset (in/out).
 * scale         : Face enlargement factor.
 * ============================================================================ */
void Add_Face(
    const glm::vec3&        pos_offset  ,   const glm::vec3&        colour_factor,
    std::vector<GLfloat>&   verts       ,   std::vector<GLuint>&    inds         ,
    const GLfloat*          face_data   ,   const GLuint*           index_data   ,
    int&                    v_offset    ,   int&                    i_offset     ,   
    int                     scale
) {
    float centre = (scale - 1.0f) * 0.5f;
    verts.insert(verts.end(), face_data, face_data + FACE_VERT_SIZE);

    for (size_t i = verts.size() - FACE_VERT_SIZE; i < verts.size(); i += FACE_NUM_ELEMENTS) {
        CLD loc(verts[i]);
        CCD col(verts[i + 1]);
        
        loc.Scale(scale);
        loc.Shift(centre + pos_offset.x,
                  centre + pos_offset.y,
                  centre + pos_offset.z
        );
        col.Scale(colour_factor.r / 16, colour_factor.g / 16, colour_factor.b / 16);

        verts[i]        = loc.To_Float();
        verts[i + 1]    = col.To_Float();
    }

    for (int j = 0; j < FACE_INDEX_SIZE; ++j) {
        inds.push_back(index_data[j] + v_offset);
    }
    v_offset += FACE_VERT_SIZE / FACE_NUM_ELEMENTS;
    i_offset += FACE_INDEX_SIZE;
}



/* ============================================================================
 * --------------------------- Add_Cube_Mesh
 * Appends cube faces into the mesh buffers, with optional scaling.
 *
 * ------ Parameters ------
 * vert_pos_offset : Position offset to apply to all vertices.
 * vert_colour     : Colour multiplier (0.0–1.0).
 * vertex_mesh     : Destination vector of packed vertex floats.
 * index_mesh      : Destination vector of indices.
 * vertex_offset   : Reference to current vertex offset (updated).
 * index_offset    : Reference to current index offset (updated).
 * face_flags      : Bitmask selecting which faces to add.
 * scale           : Uniform scale factor (default = 1).
 *
 * ------ Notes ------
 * Internally calls a private Add_Face to handle each face.
 * ============================================================================ */

void Add_Cube_Mesh(
    const glm::vec3&        vert_pos_offset ,   const glm::vec3&        vert_colour,
    std::vector<GLfloat>&   vertex_mesh     ,   std::vector<GLuint>&    index_mesh,
    int&                    vertex_offset   ,   int&                    index_offset,
    cube_faces_t            face_flags      ,   int                     scale
) {
    if (face_flags & FRONT_FACE)
        Add_Face(
            vert_pos_offset , vert_colour       ,
            vertex_mesh     , index_mesh        ,
            FRONT_FACE_MESH , FACE_INDEX_MESH   ,
            vertex_offset   , index_offset      , scale
        );

    if (face_flags & BACK_FACE)
        Add_Face(
            vert_pos_offset , vert_colour       ,
            vertex_mesh     , index_mesh        ,
            BACK_FACE_MESH  , FACE_INDEX_MESH   ,
            vertex_offset   , index_offset      , scale
        );

    if (face_flags & LEFT_FACE)
        Add_Face(
            vert_pos_offset , vert_colour       ,
            vertex_mesh     , index_mesh        ,
            LEFT_FACE_MESH  , FACE_INDEX_MESH   ,
            vertex_offset   , index_offset      , scale
        );

    if (face_flags & RIGHT_FACE)
        Add_Face(
            vert_pos_offset , vert_colour       ,
            vertex_mesh     , index_mesh        ,
            RIGHT_FACE_MESH , FACE_INDEX_MESH   ,
            vertex_offset   , index_offset      , scale
        );

    if (face_flags & TOP_FACE)
        Add_Face(
            vert_pos_offset , vert_colour       ,
            vertex_mesh     , index_mesh        ,
            TOP_FACE_MESH   , FACE_INDEX_MESH   ,
            vertex_offset   , index_offset      , scale
        );

    if (face_flags & BOTTOM_FACE)
        Add_Face(
            vert_pos_offset , vert_colour       ,
            vertex_mesh     , index_mesh        ,
            BOTTOM_FACE_MESH, FACE_INDEX_MESH   ,
            vertex_offset   , index_offset      , scale
        );
}


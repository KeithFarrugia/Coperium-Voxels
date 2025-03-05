#include "CCMS.h"

void Add_Face(
    glm::vec3               vert_pos_offset ,   glm::vec3               vert_colour ,
    std::vector<GLfloat>&   vertex_mesh     ,   std::vector<GLuint>&    index_mesh  ,
    const GLfloat*          vertices        ,   const GLuint*           indexes     ,
    int&                    v_offset        ,   int&                    i_offset    ,
    int                     v_element_count ,
    int                     v_array_size    ,   int                     i_array_size
){

    vertex_mesh.insert(vertex_mesh.end(), vertices, vertices + v_array_size);

    for (size_t i = vertex_mesh.size() - v_array_size; i < vertex_mesh.size(); i += v_element_count) {
        CLD loc(vertex_mesh[i]);
        CCD col(vertex_mesh[i + 1]);

        loc.Shift(vert_pos_offset.x, vert_pos_offset.y, vert_pos_offset.z);
        col.Scale(vert_colour.r/16, vert_colour.g/16, vert_colour.b/16);

        vertex_mesh[i]      = loc.To_Float();
        vertex_mesh[i + 1]  = col.To_Float(); 
        vertex_mesh[i + 2]  = vertex_mesh[i + 2];  // Normal x
        vertex_mesh[i + 3]  = vertex_mesh[i + 3];  // Normal y
        vertex_mesh[i + 4]  = vertex_mesh[i + 4];  // Normal z
    }

    for (int i = 0; i < i_array_size; i++) {
        index_mesh.push_back(indexes[i] + v_offset);
    }

    v_offset    += v_array_size/v_element_count;
    i_offset    += i_array_size;
}
void Add_Face(
    glm::vec3               vert_pos_offset ,   glm::vec3               vert_colour ,
    std::vector<GLfloat>&   vertex_mesh     ,   std::vector<GLuint>&    index_mesh  ,
    const GLfloat*          vertices        ,   const GLuint*           indexes     ,
    int&                    v_offset        ,   int&                    i_offset    ,
    int                     v_element_count ,
    int                     v_array_size    ,   int                     i_array_size,
    int                     scale
){

    float centre_offset = (scale - 1.0f) / 2.0f;
    vertex_mesh.insert(vertex_mesh.end(), vertices, vertices + v_array_size);
    for (size_t i = vertex_mesh.size() - v_array_size; i < vertex_mesh.size(); i += v_element_count) {
        CLD loc(vertex_mesh[i]);
        CCD col(vertex_mesh[i + 1]);

        loc.Scale(scale);
        loc.Shift(centre_offset, centre_offset, centre_offset);
        loc.Shift(vert_pos_offset.x, vert_pos_offset.y, vert_pos_offset.z);

        col.Scale(vert_colour.r/16, vert_colour.g/16, vert_colour.b/16);

        vertex_mesh[i]      = loc.To_Float();
        vertex_mesh[i + 1]  = col.To_Float(); 
        vertex_mesh[i + 2]  = vertex_mesh[i + 2];  // Normal x
        vertex_mesh[i + 3]  = vertex_mesh[i + 3];  // Normal y
        vertex_mesh[i + 4]  = vertex_mesh[i + 4];  // Normal z
    }

    for (int i = 0; i < i_array_size; i++) {
        index_mesh.push_back(indexes[i] + v_offset);
    }

    v_offset    += v_array_size/v_element_count;
    i_offset    += i_array_size;
}


void Add_Cube_Mesh(
    glm::vec3               vert_pos_offset ,   glm::vec3               vert_colour,
    std::vector<GLfloat>&   vertex_mesh     ,   std::vector<GLuint>&    index_mesh,
    int&                    vertex_offset   ,   int&                    index_offset,
    uint8_t                 face_flags
){
    // Front face
    if (face_flags & FRONT_FACE) {
        Add_Face(   vert_pos_offset     ,   vert_colour     ,    
                    vertex_mesh         ,   index_mesh      ,
                    FRONT_FACE_MESH     ,   FACE_INDEX_MESH ,
                    vertex_offset       ,   index_offset    ,
                    FACE_NUM_ELEMENTS   ,
                    FACE_VERT_SIZE      ,   FACE_INDEX_SIZE );
    }

    // Back face
    if (face_flags & BACK_FACE) {
        Add_Face(   vert_pos_offset     ,   vert_colour     ,    
                    vertex_mesh         ,   index_mesh      ,
                    BACK_FACE_MESH      ,   FACE_INDEX_MESH ,
                    vertex_offset       ,   index_offset    ,
                    FACE_NUM_ELEMENTS   ,
                    FACE_VERT_SIZE      ,   FACE_INDEX_SIZE );
    }

    // Left face
    if (face_flags & LEFT_FACE) {
        Add_Face(   vert_pos_offset     ,   vert_colour     ,    
                    vertex_mesh         ,   index_mesh      ,
                    LEFT_FACE_MESH      ,   FACE_INDEX_MESH ,
                    vertex_offset       ,   index_offset    ,
                    FACE_NUM_ELEMENTS   ,
                    FACE_VERT_SIZE      ,   FACE_INDEX_SIZE );
    }

    // Right face
    if (face_flags & RIGHT_FACE) {
        Add_Face(   vert_pos_offset     ,   vert_colour     ,    
                    vertex_mesh         ,   index_mesh      ,
                    RIGHT_FACE_MESH     ,   FACE_INDEX_MESH ,
                    vertex_offset       ,   index_offset    ,
                    FACE_NUM_ELEMENTS   ,
                    FACE_VERT_SIZE      ,   FACE_INDEX_SIZE );
    }

    // Top face
    if (face_flags & TOP_FACE) {
        Add_Face(   vert_pos_offset     ,   vert_colour     ,    
                    vertex_mesh         ,   index_mesh      ,
                    TOP_FACE_MESH       , FACE_INDEX_MESH,
                    vertex_offset       ,   index_offset    ,
                    FACE_NUM_ELEMENTS   ,
                    FACE_VERT_SIZE      ,   FACE_INDEX_SIZE );
    }

    // Bottom face
    if (face_flags & BOTTOM_FACE) {
        Add_Face(   vert_pos_offset     ,   vert_colour     ,    
                    vertex_mesh         ,   index_mesh      ,
                    BOTTOM_FACE_MESH    ,   FACE_INDEX_MESH ,
                    vertex_offset       ,   index_offset    ,
                    FACE_NUM_ELEMENTS   ,
                    FACE_VERT_SIZE      ,   FACE_INDEX_SIZE );
    }
}

void Add_Cube_Mesh(
    glm::vec3               vert_pos_offset ,   glm::vec3               vert_colour,
    std::vector<GLfloat>&   vertex_mesh     ,   std::vector<GLuint>&    index_mesh,
    int&                    vertex_offset   ,   int&                    index_offset,
    uint8_t                 face_flags      ,
    int                     scale           
){
    // Front face
    if (face_flags & FRONT_FACE) {
        Add_Face(   vert_pos_offset     ,   vert_colour     ,    
                    vertex_mesh         ,   index_mesh      ,
                    FRONT_FACE_MESH     ,   FACE_INDEX_MESH ,
                    vertex_offset       ,   index_offset    ,
                    FACE_NUM_ELEMENTS   ,
                    FACE_VERT_SIZE      ,   FACE_INDEX_SIZE , 
                    scale
        );
    }

    // Back face
    if (face_flags & BACK_FACE) {
        Add_Face(   vert_pos_offset     ,   vert_colour     ,    
                    vertex_mesh         ,   index_mesh      ,
                    BACK_FACE_MESH      ,   FACE_INDEX_MESH ,
                    vertex_offset       ,   index_offset    ,
                    FACE_NUM_ELEMENTS   ,
                    FACE_VERT_SIZE      ,   FACE_INDEX_SIZE , 
                    scale
        );
    }

    // Left face
    if (face_flags & LEFT_FACE) {
        Add_Face(   vert_pos_offset     ,   vert_colour     ,    
                    vertex_mesh         ,   index_mesh      ,
                    LEFT_FACE_MESH      ,   FACE_INDEX_MESH ,
                    vertex_offset       ,   index_offset    ,
                    FACE_NUM_ELEMENTS   ,
                    FACE_VERT_SIZE      ,   FACE_INDEX_SIZE , 
                    scale
        );
    }

    // Right face
    if (face_flags & RIGHT_FACE) {
        Add_Face(   vert_pos_offset     ,   vert_colour     ,    
                    vertex_mesh         ,   index_mesh      ,
                    RIGHT_FACE_MESH     ,   FACE_INDEX_MESH ,
                    vertex_offset       ,   index_offset    ,
                    FACE_NUM_ELEMENTS   ,
                    FACE_VERT_SIZE      ,   FACE_INDEX_SIZE , 
                    scale
        );
    }

    // Top face
    if (face_flags & TOP_FACE) {
        Add_Face(   vert_pos_offset     ,   vert_colour     ,    
                    vertex_mesh         ,   index_mesh      ,
                    TOP_FACE_MESH       , FACE_INDEX_MESH,
                    vertex_offset       ,   index_offset    ,
                    FACE_NUM_ELEMENTS   ,
                    FACE_VERT_SIZE      ,   FACE_INDEX_SIZE , 
                    scale
        );
    }

    // Bottom face
    if (face_flags & BOTTOM_FACE) {
        Add_Face(   vert_pos_offset     ,   vert_colour     ,    
                    vertex_mesh         ,   index_mesh      ,
                    BOTTOM_FACE_MESH    ,   FACE_INDEX_MESH ,
                    vertex_offset       ,   index_offset    ,
                    FACE_NUM_ELEMENTS   ,
                    FACE_VERT_SIZE      ,   FACE_INDEX_SIZE , 
                    scale
        );
    }
}



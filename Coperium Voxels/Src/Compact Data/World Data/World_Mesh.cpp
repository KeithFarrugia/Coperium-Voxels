#include "World_Mesh.h"

void Generate_Chunk_Meshes(World& w){
    for (auto& sector_entry : *w.Get_Sectors()) {
        for (auto& chunk_entry : *sector_entry.second.Get_Chunks()) {

            std::vector<GLfloat> vertex_mesh;
            std::vector<GLuint>  index_mesh;
            int vertex_offset = 0; int index_offset = 0;

            for (auto& voxel_entry : *chunk_entry.second.Get_Voxels()) {
                glm::ivec3 relative_position = glm::vec3(
                    voxel_entry.first.Get_X(),
                    voxel_entry.first.Get_Y(),
                    voxel_entry.first.Get_Z()
                );
                glm::ivec3 position = glm::vec3(
                    voxel_entry.first.Get_X() + chunk_entry.second.Get_Offset_X() * CHUNK_X_MAX + sector_entry.second.Get_Offset_X() * SECTOR_X_MAX,
                    voxel_entry.first.Get_Y() + chunk_entry.second.Get_Offset_Y() * CHUNK_Y_MAX,
                    voxel_entry.first.Get_Z() + chunk_entry.second.Get_Offset_Z() * CHUNK_Z_MAX + sector_entry.second.Get_Offset_Z() * SECTOR_Z_MAX
                );
                glm::ivec3 colour = glm::vec3(
                    voxel_entry.second.Get_R(),
                    voxel_entry.second.Get_G(),
                    voxel_entry.second.Get_B()
                );

                cube_faces_t flags = static_cast<cube_faces_t>(0);

                if (w.Get_Voxel(position.x + 1, position.y, position.z).Get_Type() != voxel_type_t::NORMAL) {
                    flags = (cube_faces_t)(flags | cube_faces_t::RIGHT_FACE);

                }if (w.Get_Voxel(position.x - 1, position.y, position.z).Get_Type() != voxel_type_t::NORMAL) {
                    flags = (cube_faces_t)(flags | cube_faces_t::LEFT_FACE);

                }if (w.Get_Voxel(position.x, position.y + 1, position.z).Get_Type() != voxel_type_t::NORMAL) {
                    flags = (cube_faces_t)(flags | cube_faces_t::TOP_FACE);

                }if (w.Get_Voxel(position.x, position.y - 1, position.z).Get_Type() != voxel_type_t::NORMAL) {
                    flags = (cube_faces_t)(flags | cube_faces_t::BOTTOM_FACE);

                }if (w.Get_Voxel(position.x, position.y, position.z + 1).Get_Type() != voxel_type_t::NORMAL) {
                    flags = (cube_faces_t)(flags | cube_faces_t::FRONT_FACE);

                }if (w.Get_Voxel(position.x, position.y, position.z - 1).Get_Type() != voxel_type_t::NORMAL) {
                    flags = (cube_faces_t)(flags | cube_faces_t::BACK_FACE);

                }

                Add_Cube_Mesh(
                    relative_position   ,   colour          ,
                    vertex_mesh         ,   index_mesh      ,
                    vertex_offset       ,   index_offset    ,
                    flags
                );

            }
            chunk_entry.second.Generate_Mesh(vertex_mesh, index_mesh);
        }
    }
}

void Render_Chunk_Meshes(World& w, Coil::Shader& s){

    for (auto& sector_entry : *w.Get_Sectors()) {
        for (auto& chunk_entry : *sector_entry.second.Get_Chunks()) {
            glm::ivec3 offset = glm::vec3(
                chunk_entry.second.Get_Offset_X() * CHUNK_X_MAX + sector_entry.second.Get_Offset_X() * SECTOR_X_MAX,
                chunk_entry.second.Get_Offset_Y() * CHUNK_Y_MAX,
                chunk_entry.second.Get_Offset_Z() * CHUNK_Z_MAX + sector_entry.second.Get_Offset_Z() * SECTOR_Z_MAX
            );

            s.Set_Vec3("vertex_offset",offset);

            chunk_entry.second.Draw_Mesh();
        }
    }



}

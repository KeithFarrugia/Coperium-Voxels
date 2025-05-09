#include "World.h"
#include <unordered_map>

/* ============================================================================
 * --------------------------- Chunk Constructor
 * ============================================================================
 */
Chunk::Chunk() : chunk_data({ lod_Level_t::UNSET, true }) {
    mesh = Coil::Basic_Mesh();
}

/* ============================================================================
 * --------------------------- Chunk Copy Constructor
 * ============================================================================
 */
Chunk::Chunk(const Chunk& other) {
    voxels = other.voxels;
    mesh = other.mesh;
    chunk_data = other.chunk_data;
}

/* ============================================================================
 * --------------------------- Chunk Destructor
 * ============================================================================
 */
Chunk::~Chunk() {
    voxels.clear();
    mesh.Clear_Mesh();
}

// Static AIR voxel used as fallback return value
static Voxel default_air_voxel(vox_data_t{
    .position = glm::ivec3(0),
    .type = voxel_type_t::AIR,
    .rel = rel_loc_t::CHUNK_LOC
});

/* ============================================================================
 * --------------------------- Get_Voxel with relative position
 * ============================================================================
 */
Voxel* Chunk::Get_Voxel(glm::ivec3 pos, rel_loc_t rel) {
    glm::ivec3 final_pos = Convert_Loc_2_Offset(pos, rel, rel_loc_t::CHUNK_LOC);
    auto it = voxels.find(final_pos);
    return it != voxels.end() ? &it->second : &default_air_voxel;
}

const Voxel* Chunk::Get_Voxel(glm::ivec3 pos, rel_loc_t rel) const {
    glm::ivec3 final_pos = Convert_Loc_2_Offset(pos, rel, rel_loc_t::CHUNK_LOC);
    auto it = voxels.find(final_pos);
    return it != voxels.end() ? &it->second : &default_air_voxel;
}

/* ============================================================================
 * --------------------------- Get_Voxel with absolute position
 * ============================================================================
 */
Voxel* Chunk::Get_Voxel(glm::ivec3 pos) {
    auto it = voxels.find(pos);
    return it != voxels.end() ? &it->second : &default_air_voxel;
}

const Voxel* Chunk::Get_Voxel(glm::ivec3 pos) const {
    auto it = voxels.find(pos);
    return it != voxels.end() ? &it->second : &default_air_voxel;
}

/* ============================================================================
 * --------------------------- Create_Voxel
 * ============================================================================
 */
void Chunk::Create_Voxel(vox_data_t data) {
    glm::ivec3 final_pos = Convert_Loc_2_Offset(data.position, data.rel, rel_loc_t::CHUNK_LOC);
    voxels[final_pos] = Voxel(data);
}

/* ============================================================================
 * --------------------------- Remove_Voxel
 * ============================================================================
 */
void Chunk::Remove_Voxel(glm::ivec3 pos, rel_loc_t rel) {
    glm::ivec3 final_pos = Convert_Loc_2_Offset(pos, rel, rel_loc_t::CHUNK_LOC);
    voxels[final_pos].SetType(voxel_type_t::AIR);
}

/* ============================================================================
 * --------------------------- Get_All_Voxels
 * ============================================================================
 */
voxels_t* Chunk::Get_All_Voxels() {
    return &voxels;
}

/* ============================================================================
 * --------------------------- Mesh Get/Set
 * ============================================================================
 */
Coil::Basic_Mesh& Chunk::Get_Mesh() {
    return mesh;
}

void Chunk::Set_Mesh(const Coil::Basic_Mesh& newMesh) {
    mesh = newMesh;
}

void Chunk::Draw_Mesh() {
    mesh.Draw_Mesh(false);
}

/* ============================================================================
 * --------------------------- Set_Cube
 * ============================================================================
 */
void Chunk::Set_Cube(glm::ivec3 pos, vox_data_t data) {
    voxels[pos] = Voxel(data);
    chunk_data.updated = true;
}

/* ============================================================================
 * --------------------------- Chunk Data Access
 * ============================================================================
 */
chunk_data_t& Chunk::Get_Chunk_Data() {
    return chunk_data;
}

const chunk_data_t& Chunk::Get_Chunk_Data() const {
    return chunk_data;
}

void Chunk::Set_Chunk_Data(const chunk_data_t& new_data) {
    chunk_data = new_data;
}

/* ============================================================================
 * --------------------------- Serialization
 * ============================================================================
 */
void Chunk::serialize(std::ostream& out) {
    size_t size = voxels.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const auto& pair : voxels) {
        out.write(reinterpret_cast<const char*>(&pair.first), sizeof(glm::ivec3));
        out.write(reinterpret_cast<const char*>(&pair.second), sizeof(Voxel));
    }
}

void Chunk::deserialize(std::istream& in) {
    size_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    voxels.clear();
    for (size_t i = 0; i < size; ++i) {
        glm::ivec3 pos;
        Voxel voxel;
        in.read(reinterpret_cast<char*>(&pos), sizeof(glm::ivec3));
        in.read(reinterpret_cast<char*>(&voxel), sizeof(Voxel));
        voxels[pos] = voxel;
    }
}

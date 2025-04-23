#include "World.h"

/* ============================================================================
 * --------------------------- Chunk
 * Constructor for Chunk class, initializing a new chunk
 * ============================================================================
 */
Chunk::Chunk() : chunk_data({ lod_Level_t::UNSET, true}) {  // Default LOD to 1.0
    voxels.resize(MAX_VOX_LOC);
    mesh = Coil::Basic_Mesh();
}

/* ============================================================================
 * --------------------------- Chunk (Copy Constructor)
 * Copy Constructor
 * ============================================================================
 */
Chunk::Chunk(const Chunk& other) {
    voxels = other.voxels;
    mesh = other.mesh;
    chunk_data= other.chunk_data;
}

/* ============================================================================
 * --------------------------- ~Chunk
 * Destructor for Chunk class, responsible for cleanup
 * ============================================================================
 */
Chunk::~Chunk() {
    voxels.clear();
    //mesh.Clear_Mesh();
}

/* ============================================================================
 * --------------------------- Get_Voxel
 * Retrieves a voxel from the chunk based on the position and relative location
 *
 * ------ Parameters ------
 * pos:    The position (ivec3) of the voxel
 * rel:    The relative location type (rel_loc_t)
 *
 * ------ Returns ------
 * Voxel pointer if the voxel exists, nullptr otherwise
 * ============================================================================
 */
Voxel* Chunk::Get_Voxel(glm::ivec3 pos, rel_loc_t rel) {
    return &voxels[
        voxel_loc_t::Compact(
            Convert_Loc_2_Offset(pos, rel, rel_loc_t::CHUNK_LOC)
        ).location
    ];
}

const Voxel* Chunk::Get_Voxel(glm::ivec3 pos, rel_loc_t rel) const {
    return &voxels[
        voxel_loc_t::Compact(
            Convert_Loc_2_Offset(pos, rel, rel_loc_t::CHUNK_LOC)
        ).location
    ];
}
/* ============================================================================
 * --------------------------- Get_Voxel
 * Retrieves a voxel from the chunk based on the position
 *
 * ------ Parameters ------
 * pos:    The position (ivec3) of the voxel
 *
 * ------ Returns ------
 * Voxel pointer if the voxel exists, nullptr otherwise
 * ============================================================================
 */
Voxel* Chunk::Get_Voxel(glm::ivec3 pos){
    return &voxels[voxel_loc_t::Compact(pos).location];
}
const Voxel* Chunk::Get_Voxel(glm::ivec3 pos) const {
    return &voxels[voxel_loc_t::Compact(pos).location];
}
/* ============================================================================
 * --------------------------- Create_Voxel
 * Creates a voxel in the chunk with the given voxel data
 *
 * ------ Parameters ------
 * data:    The data (vox_data_t) used to create the voxel
 * ============================================================================
 */
void Chunk::Create_Voxel(vox_data_t data) {
    Voxel vox(data);
    voxels[
        voxel_loc_t::Compact(
            Convert_Loc_2_Offset(data.position, data.rel, rel_loc_t::CHUNK_LOC)
        ).location
    ] = vox;
}

/* ============================================================================
 * --------------------------- Remove_Voxel
 * Removes a voxel from the chunk based on the position and relative location
 *
 * ------ Parameters ------
 * pos:    The position (ivec3) of the voxel to remove
 * rel:    The relative location type (rel_loc_t)
 * ============================================================================
 */
void Chunk::Remove_Voxel(glm::ivec3 pos, rel_loc_t rel) {
    voxels[
        voxel_loc_t::Compact(
            Convert_Loc_2_Offset(pos, rel, rel_loc_t::CHUNK_LOC)
        ).location
    ].SetType(voxel_type_t::AIR);
}

/* ============================================================================
 * --------------------------- Get_All_Voxels
 * Retrieves all the voxels contained within the chunk
 *
 * ------ Returns ------
 * A container (voxels_t) with all the voxels in the chunk
 * ============================================================================
 */
voxels_t* Chunk::Get_All_Voxels() {
    return &voxels;
}


/* ============================================================================
 * --------------------------- Get_Mesh
 * Returns a reference to the mesh
 * ============================================================================
 */
Coil::Basic_Mesh& Chunk::Get_Mesh() {
    return mesh;
}

/* ============================================================================
 * --------------------------- Set_Mesh
 * Sets a new mesh for the chunk
 * ============================================================================
 */
void Chunk::Set_Mesh(const Coil::Basic_Mesh& newMesh) {
    mesh = newMesh;
}



/* ============================================================================
 * --------------------------- Draw_Mesh
 * Draws the Mesh
 * ============================================================================
 */

void Chunk::Draw_Mesh(){
    mesh.Draw_Mesh(false);
}

void Chunk::Set_Cube(glm::ivec3 pos, vox_data_t data){
    voxels[voxel_loc_t::Compact(pos).location] = Voxel(data);
    chunk_data.updated = true;
}


/* ============================================================================
 * --------------------------- Get_Chunk_Data (Reference)
 * Returns a reference to the chunk data so it can be modified directly.
 * ============================================================================
 */
chunk_data_t& Chunk::Get_Chunk_Data() {
    return chunk_data;
}

const chunk_data_t& Chunk::Get_Chunk_Data() const {
    return chunk_data;
}


/* ============================================================================
 * --------------------------- Set_Chunk_Data
 * Sets a new chunk data structure.
 * ============================================================================
 */
void Chunk::Set_Chunk_Data(const chunk_data_t& new_data) {
    chunk_data = new_data;
}

void Chunk::serialize(std::ostream& out) {
    size_t size = voxels.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size)); // write vector size
    out.write(reinterpret_cast<const char*>(voxels.data()), size * sizeof(Voxel)); // write voxel data
}

// Deserialize the chunk
void Chunk::deserialize(std::istream& in) {
    size_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size)); // read vector size
    voxels.resize(size);
    in.read(reinterpret_cast<char*>(voxels.data()), size * sizeof(Voxel)); // read voxel data
}
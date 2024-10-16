#include <GLAD/glad.h>
#include "Chunk.h"

/* ============================================================================
 * --------------------------- Voxel
 * Default constructor initializing data to default LRGB (0, 0, 0, 0) and type 0.
 * ============================================================================
 */
Chunk::Chunk() : chunk_offset(0){
    // voxels = Voxel[VOX_LOC_MAX];
}

/* ============================================================================
 * --------------------------- Voxel
 * Constructor initializing data to a given value.
 * ============================================================================
 */
Chunk::Chunk(const uint16_t data) : chunk_offset(data){}

/* ============================================================================
 * --------------------------- Add_Voxel
 * Adds a voxel to the chunk at the specified (x, y, z) position with the
 * given light (l), red (r), green (g), and blue (b) values, and the voxel type.
 *
 * ------ Parameters ------
 * x: The x-coordinate of the voxel (0-15).
 * y: The y-coordinate of the voxel (0-63).
 * z: The z-coordinate of the voxel (0-15).
 * l: The light intensity value (0-15).
 * r: The red color component (0-15).
 * g: The green color component (0-15).
 * b: The blue color component (0-15).
 * type: The voxel type (air, solid, etc.).
 * ============================================================================
 */

void Chunk::Add_Voxel(
	const glm::ivec3	position,	const glm::ivec3	colour, 
	const int			l,			const int			type
){

	Voxel v;
    v.Set_L(l);				
    v.Set_R(colour.r);
	v.Set_G(colour.g);		
    v.Set_B(colour.b);
	v.Set_Type(type);

	//printf("Voxel: %d %d %d\n", position.x, position.y, position.z);

	voxels[Voxel_Loc::Compact(position.x, position.y, position.z)] = v;
}

/* ============================================================================
 * --------------------------- Remove_Voxel
 * Removes a voxel from the chunk at the specified (x, y, z) location.
 *
 * ------ Parameters ------
 * x: The x-coordinate of the voxel (0-15).
 * y: The y-coordinate of the voxel (0-63).
 * z: The z-coordinate of the voxel (0-15).
 * ============================================================================
 */
void Chunk::Remove_Voxel(const int x, const int y, const int z) {
    Add_Voxel(glm::vec3(x, y, z), glm::vec3(0, 0, 0), 0, voxel_type_t::INVALID);
}

/* ============================================================================
 * --------------------------- Clear
 * Clears the map from values
 * ============================================================================
 */
void Chunk::Clear(){
    for (int i = 0; i < VOX_LOC_MAX; i++) {
        voxels[i].Set_Type(voxel_type_t::INVALID);
    }
}

/* ============================================================================
 * --------------------------- Get_Voxel
 * Retrieves a voxel from the chunk at the specified (x, y, z) location.
 * If the coordinates are out of bounds, returns an invalid voxel.
 * If the voxel is not found, returns an air voxel.
 *
 * ------ Parameters ------
 * x: The x-coordinate of the voxel (0-15).
 * y: The y-coordinate of the voxel (0-63).
 * z: The z-coordinate of the voxel (0-15).
 *
 * ------ Returns ------
 * A Voxel object containing the stored values or defaults if not found.
 * ============================================================================
 */
Voxel Chunk::Get_Voxel(const int x, const int y, const int z) const{

	// --------------------------------- Check if out of bounds
	if (x >= 16 || x < 0 ||
		y >= 64 || y < 0 ||
		z >= 16 || z < 0
	){

		Voxel v;
		v.Set_L(0);		v.Set_R(0);
		v.Set_G(0);		v.Set_B(0);
		v.Set_Type(voxel_type_t::INVALID);
		return v;
	}


    return voxels[Voxel_Loc::Compact(x, y, z)];
}

/* ============================================================================
 * --------------------------- Set_Offset
 * Compacts and sets the chunk offset using X, Y, and Z coordinates.
 *
 * ------ Parameters ------
 * x: The x-coordinate of the chunk (0-31).
 * y: The y-coordinate of the chunk (0-31).
 * z: The z-coordinate of the chunk (0-31).
 * ============================================================================
 */
void Chunk::Set_Offset(const int x, const int y, const int z) {
	chunk_offset = 0;

	chunk_offset |= (x & MASK_5_BITS) << X_SHIFT;
	chunk_offset |= (z & MASK_5_BITS) << Z_SHIFT;

	if (y < 0) {
		chunk_offset |= MASK_1_BITS << Y_S_SHIFT;  
	}

	chunk_offset |= (abs(y) & MASK_5_BITS) << Y_SHIFT;
}

/* ============================================================================
 * --------------------------- Get_Offset
 * Returns the compacted offset
 * ============================================================================
 */
uint16_t Chunk::Get_Offset() {
	return chunk_offset;
}

/* ============================================================================
 * --------------------------- Get_Offset_X
 * Returns the X component of the chunk's offset.
 *
 * ------ Returns ------
 * The x-coordinate of the chunk (0-31).
 * ============================================================================
 */
int Chunk::Get_Offset_X() const {
	return (chunk_offset >> X_SHIFT) & MASK_5_BITS;
}

/* ============================================================================
 * --------------------------- Get_Offset_Y
 * Returns the Y component of the chunk's offset.
 *
 * ------ Returns ------
 * The y-coordinate of the chunk (-31 - 31).
 * ============================================================================
 */
int Chunk::Get_Offset_Y() const {

	int y_value = (chunk_offset >> Y_SHIFT) & MASK_6_BITS;


	if (chunk_offset & MASK_1_BITS >> Y_S_SHIFT) {
		return -((y_value & MASK_5_BITS) + 1);

	}else{
		return y_value & MASK_5_BITS;
	}
}

/* ============================================================================
 * --------------------------- Get_Offset_Z
 * Returns the Z component of the chunk's offset.
 *
 * ------ Returns ------
 * The z-coordinate of the chunk (0-31).
 * ============================================================================
 */
int Chunk::Get_Offset_Z() const {
	return (chunk_offset >> Z_SHIFT) & MASK_5_BITS;
}

/* ============================================================================
 * --------------------------- Get Voxels
 * Returns the list of voxels
 *
 * ------ Returns ------
 * The list of voxels
 * ============================================================================
 */
Voxel* Chunk::Get_Voxels(){
	return voxels;
}

/* ============================================================================
 * --------------------------- Generate_Mesh
 * Generates a Mesh by running through each voxel
 * ============================================================================
 */
void Chunk::Generate_Mesh(std::vector<GLfloat>& vertex_mesh, std::vector<GLuint>& index_mesh) {
	mesh.Clear_Mesh();
	mesh.Configure_Mesh(
		vertex_mesh.data(),
		sizeof(GLfloat),
		(GLsizei)vertex_mesh.size(),
		GL_FLOAT,
		FACE_NUM_ELEMENTS
	);
	mesh.Configure_Index_Buffer(
		index_mesh.data(),
		sizeof(GLuint),
		(GLsizei)index_mesh.size()
	);

	mesh.Add_Vertex_Set(0, 1, 0);
	mesh.Add_Vertex_Set(1, 1, 1);
	//mesh.Clean_Mesh();
}

/* ============================================================================
 * --------------------------- Draw_Mesh
 * Draws the chunk mesh
 * ============================================================================
 */
void Chunk::Draw_Mesh() {
	mesh.Draw_Mesh(false);
}

/* ============================================================================
 * --------------------------- Display
 * Displays the chunk and voxel data
 * ============================================================================
 */
void Chunk::Display(){
	std::cout << "Chunk ["
		<< Get_Offset_X() << "] ["
		<< Get_Offset_Y() << "] ["
		<< Get_Offset_Z() << "]"
		<< std::endl << std::endl << std::flush;

    for (uint16_t i = 0; i < CHUNK_X_MAX + CHUNK_Y_MAX + CHUNK_Z_MAX; i++) {
        Voxel_Loc v_loc(i);
		std::cout << "\tVoxel ["
			<< v_loc.Get_X() << "] ["
			<< v_loc.Get_Y() << "] ["
			<< v_loc.Get_Z() << "]"
			<< std::endl << std::flush;
        Voxel v = voxels[i];
		std::cout << "\t\tVoxel R["
			<< v.Get_R() << "] G["
			<< v.Get_G() << "] B["
			<< v.Get_B() << "] L["
			<< v.Get_L() << "]"
			<< std::endl << std::flush;

		std::cout << "\t\tVoxel Type ["
			<< Voxel_Type_To_String(v.Get_Type()) << "]"
			<< std::endl << std::endl << std::flush;
	}
}

/* ============================================================================
 * --------------------------- Compact
 * Returns the Z component of the chunk's offset.
 *
 * ------ Parameters ------
 * x: The x-coordinate of the chunk (0-31).
 * y: The y-coordinate of the chunk (0-31).
 * z: The z-coordinate of the chunk (0-31).
 * 
 * ------ Returns ------
 * Compacted offset value
 * ============================================================================
 */
uint16_t Chunk::Compact(int x, int y, int z){
	uint16_t chunk_offset = 0;

	chunk_offset |= (x & MASK_5_BITS) << X_SHIFT;
	chunk_offset |= (z & MASK_5_BITS) << Z_SHIFT;

	if (y < 0) {
		chunk_offset |= MASK_1_BITS << Y_S_SHIFT;
	}

	chunk_offset |= (abs(y) & MASK_5_BITS) << Y_SHIFT;
	return chunk_offset;
}

#include <GLAD/glad.h>
#include "Chunk.h"

/* ============================================================================
 * --------------------------- Voxel
 * Default constructor initializing data to default LRGB (0, 0, 0, 0) and type 0.
 * ============================================================================
 */
Chunk::Chunk() : chunk_offset(0), first_draw(true){}

/* ============================================================================
 * --------------------------- Voxel
 * Constructor initializing data to a given value.
 * ============================================================================
 */
Chunk::Chunk(const uint16_t data) : chunk_offset(data), first_draw(true) {}

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
	v.Set_L(l);				v.Set_R(colour.r);
	v.Set_G(colour.g);		v.Set_B(colour.b);
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

	auto it = voxels.find(Voxel_Loc::Compact(x, y, z));

	if (it != voxels.end()) {
		voxels.erase(it);
	}
}

/* ============================================================================
 * --------------------------- Clear
 * Clears the map from values
 * ============================================================================
 */
void Chunk::Clear(){
	voxels.clear();
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

	auto it = voxels.find(Voxel_Loc::Compact(x, y, z));

	// --------------------------------- Found -> Return
	if (it != voxels.end()) {
		return (it->second);

	// --------------------------------- Not Found -> Air Voxel
	}else {
		Voxel v;
		v.Set_L(0);		v.Set_R(0);
		v.Set_G(0);		v.Set_B(0);
		v.Set_Type(voxel_type_t::AIR);
		return v;
	}
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
voxel_set_t* Chunk::Get_Voxels(){
	return &voxels;
}

/* ============================================================================
 * --------------------------- Generate_Mesh
 * Generates a Mesh by running through each voxel
 * ============================================================================
 */
void Chunk::Generate_Mesh(std::vector<GLfloat>& vertex_mesh, std::vector<GLuint>&  index_mesh){
	if (first_draw == false) {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO
	glBindVertexArray(VAO);

	// Bind VBO and EBO and set their data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertex_mesh.size() * sizeof(GLfloat), vertex_mesh.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_mesh.size() * sizeof(GLuint), index_mesh.data(), GL_STATIC_DRAW);

	// Set vertex attribute pointers
	// Position attribute
	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)(1 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	ebo_size = index_mesh.size();
	first_draw = false;
}

/* ============================================================================
 * --------------------------- Draw_Mesh
 * Draws the chunk mesh
 * ============================================================================
 */
void Chunk::Draw_Mesh(){
	glDrawElements(GL_TRIANGLES, ebo_size, GL_UNSIGNED_INT, 0);

	// Clean up by deleting VAO, VBO, EBO every frame
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

	for (auto& voxel_entry : voxels) {
		std::cout << "\tVoxel ["
			<< voxel_entry.first.Get_X() << "] ["
			<< voxel_entry.first.Get_Y() << "] ["
			<< voxel_entry.first.Get_Z() << "]"
			<< std::endl << std::flush;

		std::cout << "\t\tVoxel R["
			<< voxel_entry.second.Get_R() << "] G["
			<< voxel_entry.second.Get_G() << "] B["
			<< voxel_entry.second.Get_B() << "] L["
			<< voxel_entry.second.Get_L() << "]"
			<< std::endl << std::flush;

		std::cout << "\t\tVoxel Type ["
			<< Voxel_Type_To_String(voxel_entry.second.Get_Type()) << "]"
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
	Chunk c;
	c.Set_Offset(x, y, z);
	return c.chunk_offset;
}

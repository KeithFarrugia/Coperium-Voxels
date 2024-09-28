#pragma once
#ifndef CHUNK_H
#define CHUNK_H

#include <unordered_map>

#include "../Voxel/Voxel.h"
#include "../Operations.h"
#include "../../Cube Mesh/CCMS.h"

#include <COIL/Mesh/Basic_Mesh.h>
#include <GLFW/glfw3.h>

typedef std::unordered_map<Voxel_Loc, Voxel> voxel_set_t;


constexpr auto CHUNK_X_MAX = 16;
constexpr auto CHUNK_Y_MAX = 64;
constexpr auto CHUNK_Z_MAX = 16;

class Chunk {
public:
	Chunk();
	Chunk(const uint16_t chunk_offset);

	// --------------------------------- GENERIC
	void		Add_Voxel	(const glm::ivec3   position,
                             const glm::ivec3   colour  ,
                             const int          l       ,
                             const int          type    );

	void Remove_Voxel(
		const int x, const int y, const int z);

	void Clear();
	// --------------------------------- SETTERS
	void Set_Offset(int x, int y, int z);


	// --------------------------------- GETTERS
	uint16_t Get_Offset		();

	Voxel	Get_Voxel		(const int x, 
							 const int y, 
							 const int z ) const;

	int		Get_Offset_X	() const;
	int		Get_Offset_Y	() const;
	int		Get_Offset_Z	() const;

	voxel_set_t* Get_Voxels();

	void Generate_Mesh(std::vector<GLfloat>& vertex_mesh, std::vector<GLuint>& index_mesh);
	void Draw_Mesh();


	void Display();

	static uint16_t Compact(int x, int y, int z);

private:
	// --------------------------------- MASK VALUES
	static constexpr int    MASK_1_BITS = 0x1;
	static constexpr int    MASK_5_BITS = 0x1F;
	static constexpr int    MASK_6_BITS = 0x3F;

	// --------------------------------- SHIFT VALUES
	static constexpr int    X_SHIFT		= 11;
	static constexpr int    Y_SHIFT		= 5;
	static constexpr int    Z_SHIFT		= 0;

	static constexpr int    Y_S_SHIFT	= 10;

	// --------------------------------- VARIABLES
	uint16_t chunk_offset;

	// Map to store the voxels
	voxel_set_t voxels;

	Coil::Basic_Mesh mesh;
};

#endif // !CHUNK_H

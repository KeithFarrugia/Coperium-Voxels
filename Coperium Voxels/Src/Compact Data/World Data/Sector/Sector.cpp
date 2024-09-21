#include "Sector.h"

/* ============================================================================
 * --------------------------- Sector
 * Default constructor for the Sector class. Initializes the sector without any
 * chunks or offset.
 * ============================================================================
 */
Sector::Sector() :sector_offset(0){}

/* ============================================================================
 * --------------------------- Sector
 * Initializes the Sector using a given offset
 * ============================================================================
 */
Sector::Sector(uint32_t offset) : sector_offset(offset){}

/* ============================================================================
 * --------------------------- Add_Voxel
 * Adds a voxel to the given sector position
 *
 * ------ Parameters ------
 * position: the world position
 * colour: the colour of the voxel
 * l: the light level of the voxel
 * type: the type of the voxel
 * ============================================================================
 */
void Sector::Add_Voxel(
    const glm::ivec3    position,   const glm::ivec3    colour, 
    const int           l,          const int           type    
){
    Chunk* chunk;

    glm::ivec3 chunk_pos =
        Convert_Sector_To_Chunk(position);

    chunk = Get_Chunk_S(position.x, position.y, position.z);


    if (chunk != nullptr) {

        chunk->Add_Voxel(chunk_pos, colour, l, type);

    }else{
        glm::ivec3 local_pos =
            Convert_Sector_To_Local(position);

        //printf("Chunk: %d %d %d\n", local_pos.x, local_pos.y, local_pos.z);

        Create_Chunk(local_pos.x, local_pos.y, local_pos.z);

        chunk = Get_Chunk_L(local_pos.x, local_pos.y, local_pos.z);

        if (chunk != nullptr) {
            chunk->Add_Voxel(chunk_pos, colour, l, type);
        }

    }

}
/* ============================================================================
 * --------------------------- Remove_Voxel
 * removes a voxel to the given sector position
 *
 * ------ Parameters ------
 * position: the world position
 * ============================================================================
 */
void Sector::Remove_Voxel(const glm::ivec3 position){
    Chunk* chunk;

    glm::ivec3 chunk_pos =
        Convert_Sector_To_Chunk(position);

    chunk = Get_Chunk_S(position.x, position.y, position.z);


    if (chunk != nullptr) {

        chunk->Remove_Voxel(chunk_pos.x, chunk_pos.y, chunk_pos.z);

    }else{
        return;
    }
}

/* ============================================================================
 * --------------------------- Sector
 * Default constructor for the Sector class. Initializes the sector without any
 * chunks or offset.
 * ============================================================================
 */
void Sector::Create_Chunk(const int x, const int y, const int z){
    Chunk c;
    c.Set_Offset(x, y, z);
    chunks[Chunk::Compact(
        c.Get_Offset_X(),
        c.Get_Offset_Y(),
        c.Get_Offset_Z()
    )] = c;
}

/* ============================================================================
 * --------------------------- Add_Chunk
 * Adds a given Chunk to the map/list
 * 
 * ------ Parameters ------
 * chunk: The chunk being added
 * ============================================================================
 */
void Sector::Add_Chunk(const Chunk& chunk){
    chunks[Chunk::Compact(
        chunk.Get_Offset_X(),
        chunk.Get_Offset_Y(),
        chunk.Get_Offset_Z()
    )] = chunk;
}

/* ============================================================================
 * --------------------------- Remove_Chunk
 * Removes a chunk from the sector at the specified chunk (x, y, z) location.
 * The function checks if the chunk exists in the sector's chunk map and erases
 * it if found.
 *
 * ------ Parameters ------
 * x: The x-coordinate of the chunk within the sector.
 * y: The y-coordinate of the chunk within the sector.
 * z: The z-coordinate of the chunk within the sector.
 * ============================================================================
 */
void Sector::Remove_Chunk(int x, int y, int z) {
    auto it = chunks.find(Chunk::Compact(x, y, z));
    if (it != chunks.end()) {
        chunks.erase(it);
    }
}

/* ============================================================================
 * --------------------------- Get_Voxel
 * Retrieves a voxel from the sector by determining the appropriate chunk based
 * on the provided (x, y, z) world coordinates. It calculates the chunk indices
 * within the sector, retrieves the chunk, and returns the voxel from within
 * that chunk. If the chunk or voxel does not exist, an invalid voxel is returned.
 *
 * ------ Parameters ------
 * x: The x-coordinate of the voxel within the sector.
 * y: The y-coordinate of the voxel within the sector.
 * z: The z-coordinate of the voxel within the sector.
 *
 * ------ Returns ------
 * A Voxel object, or an invalid voxel if not found.
 * ============================================================================
 */
Voxel Sector::Get_Voxel(int x, int y, int z) {
    Chunk* chunk = Get_Chunk_S(x, y, z);

    if (chunk != nullptr) {
        glm::ivec3 sector_pos =
            Convert_Sector_To_Chunk(glm::ivec3(x, y, z));
        
        return chunk->Get_Voxel(sector_pos.x, sector_pos.y, sector_pos.z);
    }

    Voxel invalid_voxel;
    invalid_voxel.Set_Type(voxel_type_t::INVALID);
    return invalid_voxel;
}

/* ============================================================================
 * --------------------------- Get_Chunks
 * Returns a pointer to the chunk map/set.
 * 
 * 
 * ------ Returns ------
 * 
 * ============================================================================
 */
chunk_set_t* Sector::Get_Chunks(){
    return &chunks;
}

/* ============================================================================
 * --------------------------- Get_Sector_W
 * Retrieves a given chunk using the local based position
 *
 * ------ Parameters ------
 * x: The x-coordinate of the sector (local).
 * y: The y-coordinate of the sector (local).
 * z: The z-coordinate of the sector (local).
 * chunk: The chunk to be returned.
 *
 * ------ Returns ------
 * true: success
 * false: failure
 * ============================================================================
 */
Chunk* Sector::Get_Chunk_L(const int x, const int y, const int z) {
    uint32_t location = Chunk::Compact(x, y, z);

    auto it = chunks.find(location);
    if (it != chunks.end()) {
        return &it->second;

    }else {
        return nullptr;
    }
}
/* ============================================================================
 * --------------------------- Get_Sector_W
 * Retrieves a given chunk using the Sector based position
 *
 * ------ Parameters ------
 * x: The x-coordinate of the sector (Sector).
 * y: The y-coordinate of the sector (Sector).
 * z: The z-coordinate of the sector (Sector).
 * chunk: The chunk to be returned.
 *
 * ------ Returns ------
 * true: success
 * false: failure
 * ============================================================================
 */
Chunk* Sector::Get_Chunk_S(const int x, const int y, const int z) {

    glm::ivec3 local_co = Convert_Sector_To_Local(glm::ivec3(x, y, z));

    return Get_Chunk_L(local_co.x, local_co.y, local_co.z);
}



/* ============================================================================
 * --------------------------- Set_Offset
 * Compacts and sets the sector's offset based on the provided X and Z
 * coordinates. The compacted offset is a 32-bit value where the signs and
 * magnitudes of both X and Z coordinates are stored.
 *
 * ------ Parameters ------
 * x: The x-coordinate of the sector.
 * z: The z-coordinate of the sector.
 * ============================================================================
 */
void Sector::Set_Offset(int x, int z) {
    sector_offset = 0;

    if (x < 0) {
        sector_offset |= (MASK_1_BITS << X_S_SHIFT);
        x = -x;
    }
    sector_offset |= (x & MASK_15_BITS) << X_M_SHIFT;

    if (z < 0) {
        sector_offset |= (MASK_1_BITS << Z_S_SHIFT);
        z = -z;
    }
    sector_offset |= (z & MASK_15_BITS) << Z_M_SHIFT;
}

/* ============================================================================
 * --------------------------- Get_Offset
 * Returns the compacted sector offset, which is a 32-bit value containing both
 * the X and Z coordinates of the sector.
 *
 * ------ Returns ------
 * A 32-bit unsigned integer representing the sector's offset.
 * ============================================================================
 */
uint32_t Sector::Get_Offset() {
    return sector_offset;
}

/* ============================================================================
 * --------------------------- Display
 * Displays the Sector Data
 * ============================================================================
 */
void Sector::Display(){
    std::cout << "\n---------------- Sector ["
        << Get_Offset_X() << "] ["
        << Get_Offset_Z() << "] ----------------"
        << std::endl << std::flush;

    for (auto& chunk_entry : chunks) {
        chunk_entry.second.Display();
    }
}

/* ============================================================================
 * --------------------------- Get_Offset_X
 * Retrieves the X component of the sector's offset, taking into account the
 * sign bit. The function extracts the X coordinate and adjusts for the sign
 * (positive or negative).
 *
 * ------ Returns ------
 * The signed x-coordinate of the sector.
 * ============================================================================
 */
int Sector::Get_Offset_X() const {
    int x = (sector_offset >> X_M_SHIFT) & MASK_15_BITS;
    bool sign = (sector_offset >> X_S_SHIFT) & MASK_1_BITS;

    return sign ? -x : x;
}

/* ============================================================================
 * --------------------------- Get_Offset_Z
 * Retrieves the Z component of the sector's offset, taking into account the
 * sign bit. The function extracts the Z coordinate and adjusts for the sign
 * (positive or negative).
 *
 * ------ Returns ------
 * The signed z-coordinate of the sector.
 * ============================================================================
 */
int Sector::Get_Offset_Z() const {
    int z = (sector_offset >> Z_M_SHIFT) & MASK_15_BITS;
    bool sign = (sector_offset >> Z_S_SHIFT) & MASK_1_BITS;

    return sign ? -z : z;
}

/* ============================================================================
 * --------------------------- Compact
 * Compacts the given X and Z coordinates into a single 32-bit unsigned integer
 * that can be used as a key for identifying a sector in the world.
 *
 * ------ Parameters ------
 * x: The x-coordinate of the sector.
 * z: The z-coordinate of the sector.
 *
 * ------ Returns ------
 * A 32-bit unsigned integer representing the compacted sector coordinates.
 * ============================================================================
 */
uint32_t Sector::Compact(const int x, const int z) {
    Sector s;
    s.Set_Offset(x, z);
    return s.sector_offset;
}

/* ============================================================================
 * --------------------------- Convert_Sector_To_Local
 * Converts a given Sector relative position and deduces the chunk at
 * which it belongs to example 498,498 would be located in the Sector
 * 31,31
 *
 *  ------ Parameters ------
 * sector_pos: The Sector relevant position
 *
 * ------ Returns ------
 * The relative chunk position so the id of the sector
 * in which that world location falls into
 * ============================================================================
 */
glm::ivec3 Sector::Convert_Sector_To_Local(const glm::ivec3 sector_pos) {
    glm::ivec3 local_pos;
    local_pos.x = WD_Div(sector_pos.x, CHUNK_X_MAX);
    local_pos.y = WD_Div(sector_pos.y, CHUNK_Y_MAX);
    local_pos.z = WD_Div(sector_pos.z, CHUNK_Z_MAX);

    return local_pos;
}

/* ============================================================================
 * --------------------------- Convert_Sector_To_Chunk
 * Converts a given world position into that recognised by a sector
 * meaning that if the sector location for example 498,498 would be
 * located in the Sector 1,1, then the total number of voxels which
 * would fall under the previous sectors is removed so that the sector
 * is given the location 498,498 which is relative to the sector
 *
 *  ------ Parameters ------
 * sector_pos: The world position
 *
 * ------ Returns ------
 * The position in range of the sectors concern (0-512)
 * ============================================================================
 */
glm::ivec3 Sector::Convert_Sector_To_Chunk(const glm::ivec3 sector_pos) {
    glm::ivec3 chunk_pos;

    chunk_pos.x = WD_Mod(sector_pos.x, CHUNK_X_MAX);
    chunk_pos.y = WD_Mod(sector_pos.y, CHUNK_Y_MAX);
    chunk_pos.z = WD_Mod(sector_pos.z, CHUNK_Z_MAX);

    return chunk_pos;
}
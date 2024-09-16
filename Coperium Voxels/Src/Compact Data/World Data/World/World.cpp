#include "World.h"
/* ============================================================================
 * --------------------------- World
 * Default Constructor
 * ============================================================================
 */
World::World(){}

/* ============================================================================
 * --------------------------- ~World
 * Default De-Structor
 * ============================================================================
 */
World::~World() {
    Clear_Sectors();
}

/* ============================================================================
 * --------------------------- Add_Voxel
 * Adds a voxel to the given world position
 * 
 * ------ Parameters ------
 * position: the world position
 * colour: the colour of the voxel
 * l: the light level of the voxel
 * type: the type of the voxel
 * ============================================================================
 */
void World::Add_Voxel(
    const glm::ivec3    position,   const glm::ivec3    colour,
    const int           l,          const int           type    
){
    Sector* sector = Get_Sector_W(position.x, position.y, position.z);

    glm::ivec3 sector_pos =
        Convert_World_To_Sector(position);


    if (sector != nullptr) {
        sector->Add_Voxel(sector_pos, colour, l, type);

    }else{
        glm::ivec3 local_pos =
            Convert_World_To_Local(position);

        Create_Sector(local_pos.x, local_pos.z);

        //printf("Sector: %d %d\n", local_pos.x, local_pos.z);

        sector = Get_Sector_L(local_pos.x, local_pos.y, local_pos.z);

        if (sector != nullptr) {
            sector->Add_Voxel(sector_pos, colour, l, type);
        }

    }
}

/* ============================================================================
 * --------------------------- Create_Sector
 * Creates and adds a new sector to the list/map
 * ============================================================================
 */
void World::Create_Sector(const int x, const int z){
    Sector s;
    s.Set_Offset(x, z);
    sectors[Sector::Compact(x, z)] = s;
}

/* ============================================================================
 * --------------------------- Add_Sector
 * Adds a sector at the specified sector (x, y) position.
 *
 * ------ Parameters ------
 * x: The x-coordinate of the sector.
 * y: The y-coordinate of the sector.
 * sector: The sector to add to the world.
 * ============================================================================
 */
void World::Add_Sector(const Sector& sector) {
    sectors[Sector::Compact(
        sector.Get_Offset_X(), 
        sector.Get_Offset_Z()
    )] = sector;
}

/* ============================================================================
 * --------------------------- Clear_Sectors
 * Clears the Sectors list
 * ============================================================================
 */
void World::Clear_Sectors(){
    sectors.clear();
}

/* ============================================================================
 * --------------------------- Get_Voxel
 * Retrieves a voxel at the world position (x, y, z).
 *
 * ------ Parameters ------
 * x: The x-coordinate of the voxel in the world.
 * y: The y-coordinate of the voxel in the world.
 * z: The z-coordinate of the voxel in the world.
 *
 * ------ Returns ------
 * A Voxel object from the correct sector, chunk, or an INVALID voxel if not
 * found.
 * ============================================================================
 */
Voxel World::Get_Voxel(const int x, const int y, const int z) {

    Sector* sector = Get_Sector_W(x, y, z);

    if (sector != nullptr) {
        glm::ivec3 sector_pos = 
            Convert_World_To_Sector(glm::ivec3(x, y, z));
        return sector->Get_Voxel(sector_pos.x, sector_pos.y, sector_pos.z);
    }

    Voxel invalid_voxel;
    invalid_voxel.Set_Type(voxel_type_t::INVALID);
    return invalid_voxel;
}



/* ============================================================================
 * --------------------------- Get_Sector_L
 * Retrieves a given sector using the local co-ordinates so its based on the
 * sector and not the voxel location
 *
 * ------ Parameters ------
 * x: The x-coordinate of the sector (local).
 * y: The y-coordinate of the sector (local).
 * z: The z-coordinate of the sector (local).
 * sector: The Sector to be returned.
 *
 * ------ Returns ------
 * true: success
 * false: failure
 * ============================================================================
 */
Sector* World::Get_Sector_L(
    const int x, const int y, const int z
){
    uint32_t location = Sector::Compact(x, z);

    auto it = sectors.find(location);
    if (it != sectors.end()) {
        return &it->second;

    }else {
        return nullptr;
    }
}

/* ============================================================================
 * --------------------------- Get_Sector_W
 * Retrieves a given sector using the world co-ordinates so its based on the 
 * voxel location
 *
 * ------ Parameters ------
 * x: The x-coordinate of the sector (world).
 * y: The y-coordinate of the sector (world).
 * z: The z-coordinate of the sector (world).
 * sector: The Sector to be returned.
 *
 * ------ Returns ------
 * true: success
 * false: failure
 * ============================================================================
 */
Sector* World::Get_Sector_W(
    const int x, const int y, const int z
) {
    glm::ivec3 local_co = Convert_World_To_Local(glm::ivec3(x, y, z));
    return Get_Sector_L(local_co.x, local_co.y, local_co.z);
}

/* ============================================================================
 * --------------------------- Get_Sectors
 * Retrieves the Sectors list/set
 *
 * ------ Returns ------
 * Sectors reference
 * ============================================================================
 */
sector_set_t* World::Get_Sectors(){
    return &sectors;
}

/* ============================================================================
 * --------------------------- Display
 * Displays the World Data
 * ============================================================================
 */
void World::Display(){
    for (auto& sector_entry : sectors) {
        sector_entry.second.Display();
    }
}

/* ============================================================================
 * --------------------------- Convert_World_to_Local
 * Converts a given world position and deduces the sector at
 * which it belongs to example 1010,1010 would be located in the Sector 
 * 1,1
 * 
 *  ------ Parameters ------
 * world_pos: The world position 
 *
 * ------ Returns ------
 * The relative Sector position so the id of the sector
 * in which that world location falls into
 * ============================================================================
 */
glm::ivec3 World::Convert_World_To_Local(const glm::ivec3 world_pos){
    glm::ivec3 local_pos;

    local_pos.x = WD_Div(world_pos.x, SECTOR_X_MAX);
    local_pos.z = WD_Div(world_pos.z, SECTOR_Z_MAX);;
    local_pos.y =  world_pos.y;

    return local_pos;
}

/* ============================================================================
 * --------------------------- Convert_World_to_Sector
 * Converts a given world position into that recognised by a sector
 * meaning that if the location for example 1010,1010 would be 
 * located in the Sector 1,1, then the total number of voxels which
 * would fall under the previous sectors is removed so that the sector
 * is given the location 498,498 which is relative to the sector
 *
 *  ------ Parameters ------
 * world_pos: The world position
 *
 * ------ Returns ------
 * The position in range of the sectors concern (0-512)
 * ============================================================================
 */
glm::ivec3 World::Convert_World_To_Sector(const glm::ivec3 world_pos){
    glm::ivec3 sector_pos;
    sector_pos.x = WD_Mod(world_pos.x, SECTOR_X_MAX);
    sector_pos.z = WD_Mod(world_pos.z, SECTOR_Z_MAX);
    sector_pos.y = world_pos.y;

    return sector_pos;
}

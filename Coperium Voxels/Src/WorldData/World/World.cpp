#include "World.h"

class World {

};

glm::ivec3 World::Convert_Loc(glm::ivec3 value, rel_loc_t from, rel_loc_t to){
    switch (from) {
        case rel_loc_t::WORLD_LOC:
            switch (to){
                case rel_loc_t::WORLD_LOC:
                    glm::ivec3 local_pos;

                    local_pos.x = Safe_Div(value.x, SECTOR_X_MAX);
                    local_pos.z = Pos_Mod(value.z, SECTOR_Z_MAX);;
                    local_pos.y = value.y;

                    return local_pos;
                case rel_loc_t::SECTOR_LOC:

                case rel_loc_t::CHUNK_LOC:

                case rel_loc_t::VOXEL_LOC:

            }
        case rel_loc_t::SECTOR_LOC:
            switch (to) {
                case rel_loc_t::CHUNK_LOC:

                case rel_loc_t::VOXEL_LOC:

                default:
                    return value

            }
        case rel_loc_t::CHUNK_LOC:
            switch (to) {
                case rel_loc_t::VOXEL_LOC:

                default:
                    return value

            }
        default:
            return value
    }
    return glm::ivec3();
}

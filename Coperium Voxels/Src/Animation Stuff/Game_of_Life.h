#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Cell {
    int  x          = 0;
    int  y          = 0;
    bool alive      = false;
    bool changed    = false;
    Cell(int x_val = 0, int y_val = 0, bool alive_val = false, bool changed_val = false)
        : x(x_val), y(y_val), alive(alive_val), changed(changed_val) {}
    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }
};


// Hash function for unordered_map
struct CellHash {
    size_t operator()(const Cell& c) const {
        return hash<int>()(c.x) ^ hash<int>()(c.y);
    }
};

class GameOfLife {
private:
    unordered_map<Cell, Cell, CellHash> cells;
    int                                 width, height;
    milliseconds                        update_interval;
    steady_clock::time_point            last_update_time;
    int                                 min_x, max_x, min_y, max_y; // Play area bounds

    vector<Cell> getNeighbours(const Cell& cell) {
        vector<Cell> neighbours;

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue; // Skip the cell itself
                int nx = cell.x + dx;
                int ny = cell.y + dy;

                // Ensure neighbours are within bounds
                if (nx >= min_x && nx <= max_x && ny >= min_y && ny <= max_y) {
                    neighbours.push_back({ nx, ny });
                }
            }
        }
        return neighbours;
    }

public:
    GameOfLife(int w, int h, const vector<Cell>& init_cells, int mill_sec_interval) {
        init(w, h, init_cells, mill_sec_interval);
    }

    void init(int w, int h, const vector<Cell>& init_cells, int mill_sec_interval) {
        width = w;
        height = h;
        cells.clear();
        update_interval = milliseconds(mill_sec_interval);
        last_update_time = steady_clock::now();

        // Default play area bounds
        min_x = 0;
        max_x = width - 1;
        min_y = 0;
        max_y = height - 1;

        for (const auto& cell : init_cells) {
            if (cell.x >= min_x && cell.x <= max_x && cell.y >= min_y && cell.y <= max_y) {
                cells[cell] = { cell.x, cell.y, true, true };
            }
        }
    }

    void Update_Game() {
        unordered_map<Cell, int, CellHash> neighbour_count;
        unordered_map<Cell, Cell, CellHash> new_cells;

        for (auto& [_, cell] : cells) {
            cell.changed = false;
            for (const auto& neighbour : getNeighbours(cell)) {
                neighbour_count[neighbour]++;
            }
        }

        // Apply rules and track changes
        for (const auto& [cell, count] : neighbour_count) {
            if (cell.x < min_x || cell.x > max_x || cell.y < min_y || cell.y > max_y) {
                continue; // Prevents cells from growing outside the play area
            }

            bool was_alive = cells.count(cell) && cells[cell].alive;
            bool now_alive = (count == 3 || (count == 2 && was_alive));

            if (was_alive != now_alive) {
                new_cells[cell] = { cell.x, cell.y, now_alive, true };
            } else if (was_alive) {
                new_cells[cell] = { cell.x, cell.y, true, false };
            }
        }

        cells = move(new_cells);
    }

    inline glm::ivec3 Lerp(const glm::ivec3& a, const glm::ivec3& b, float t)
    {
        return glm::ivec3(
            (int)(a.r + t * (b.r - a.r)),
            (int)(a.g + t * (b.g - a.g)),
            (int)(a.b + t * (b.b - a.b))
        );
    }

    void Update_World(WorldManager& world, glm::ivec3 min_cube, glm::ivec3 max_cube)
    {
        // Adjust play area
        min_x = min_cube.x;
        max_x = max_cube.x;
        min_y = min_cube.z; // your code calls the z dimension "y" in the simulation
        max_y = max_cube.z;

        // Define 8-bit colors
        glm::ivec3 royal_blue(65, 105, 225);
        glm::ivec3 crimson(220, 20, 60);

        // Get all sectors from the world
        sectors_t* sectors = world.Get_World().Get_All_Sectrs();
        for (sector_pair_t sector_pair : *sectors) {
            chunks_t* chunks = sector_pair.second.Get_All_Chunks();
            for (chunk_pair_t chunk_pair : *chunks) {

                glm::ivec3 offset(
                    chunk_pair.first.X() * CHUNK_SIZE_X + sector_pair.first.X() * SECTR_SIZE_X,
                    chunk_pair.first.Y() * CHUNK_SIZE_Y,
                    chunk_pair.first.Z() * CHUNK_SIZE_Z + sector_pair.first.Z() * SECTR_SIZE_Z
                );

                // Iterate over the local voxel coords in this chunk
                for (int local_x = MIN_ID_V_X; local_x <= MAX_ID_V_X; local_x++) {
                    for (int local_z = MIN_ID_V_Z; local_z <= MAX_ID_V_Z; local_z++) {
                        // Compute simulation cell coords
                        int sim_x = offset.x + local_x;
                        int sim_y = offset.z + local_z;

                        // Skip out-of-bounds
                        if (sim_x < min_x || sim_x > max_x || sim_y < min_y || sim_y > max_y)
                            continue;

                        Cell sim_cell{ sim_x, sim_y };
                        auto it = cells.find(sim_cell);
                        if (it != cells.end() && it->second.changed) {
                            // Default to black
                            glm::ivec3 finalColor4(0, 0, 0);

                            // If alive, compute gradient color, then quantize to 4-bit
                            if (it->second.alive) {
                                // Simple left-to-right gradient
                                float t = 0.0f;
                                if (max_x != min_x) {
                                    t = float(sim_x - min_x) / float(max_x - min_x);
                                }

                                // Get the 8-bit interpolated color
                                glm::ivec3 color8 = Lerp(royal_blue, crimson, t);

                                // Now scale to 4-bit range [0..15]
                                finalColor4.r = (color8.r * 15) / 255;
                                finalColor4.g = (color8.g * 15) / 255;
                                finalColor4.b = (color8.b * 15) / 255;

                                // Alternatively: finalColor4.r = color8.r >> 4; etc.
                            }

                            // Set the voxel color with 4-bit channels
                            chunk_pair.second
                                .Get_Voxel(glm::ivec3(local_x, 0, local_z))
                                ->SetColour(finalColor4);

                            chunk_pair.second.Get_Chunk_Data().updated = true;
                        }
                    }
                }
            }
        }
    }

    void Update(WorldManager& world, glm::ivec3 min_cube, glm::ivec3 max_cube) {
        auto now     = steady_clock::now();
        auto elapsed = duration_cast<milliseconds>(now - last_update_time);

        if (elapsed >= update_interval) {
            last_update_time = now;
            Update_Game();
            Update_World(world, min_cube, max_cube);
        }
    }
};

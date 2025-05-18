#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include "../WorldData/Chunk_Management/WorldManager.h"
using namespace std;
using namespace std::chrono;

struct Cell {
    int x;
    int y;
    bool alive;
    bool changed;

    Cell(int x_val = 0, int y_val = 0, bool alive_val = false, bool changed_val = false)
        : x(x_val), y(y_val), alive(alive_val), changed(changed_val) {}

    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }
};

// Hash function for Cell
struct CellHash {
    size_t operator()(const Cell& c) const {
        return std::hash<int>()(c.x) ^ (std::hash<int>()(c.y) << 1);
    }
};

// GameOfLife with arbitrary centered play area
class GameOfLife {
public:
    /**
     * Constructor: specify explicit bounds and initial live cells
     * @param minX  Minimum x-coordinate (inclusive)
     * @param maxX  Maximum x-coordinate (inclusive)
     * @param minY  Minimum y-coordinate (inclusive)
     * @param maxY  Maximum y-coordinate (inclusive)
     * @param init_cells  List of initially alive cells (world coordinates)
     * @param mill_sec_interval  Update interval in milliseconds
     */
    GameOfLife(int minX, int maxX, int minY, int maxY,
        const std::vector<Cell>& init_cells,
        int mill_sec_interval)
    {
        init(minX, maxX, minY, maxY, init_cells, mill_sec_interval);
    }

    /**
     * Re-init simulation bounds and state
     */
    void init(int minX, int maxX, int minY, int maxY,
        const std::vector<Cell>& init_cells,
        int mill_sec_interval)
    {
        this->min_x = minX;
        this->max_x = maxX;
        this->min_y = minY;
        this->max_y = maxY;
        cells.clear();
        update_interval = std::chrono::milliseconds(mill_sec_interval);
        last_update_time = std::chrono::steady_clock::now();

        // Only insert cells within bounds
        for (const auto& c : init_cells) {
            if (c.x >= min_x && c.x <= max_x
                && c.y >= min_y && c.y <= max_y)
            {
                cells[c] = Cell(c.x, c.y, true, true);
            }
        }
    }

    /**
     * Advance the simulation by one generation
     */
    void Update_Game() {
        std::unordered_map<Cell, int, CellHash> neighbour_count;
        std::unordered_map<Cell, Cell, CellHash> new_state;

        // Count neighbours for each alive cell
        for (auto& kv : cells) {
            Cell cell = kv.first;
            auto& data = kv.second;
            data.changed = false;
            for (auto& nb : getNeighbours(cell)) {
                neighbour_count[nb]++;
            }
        }

        // Apply Game of Life rules
        for (auto& kv : neighbour_count) {
            const Cell& cell = kv.first;
            int count = kv.second;

            if (cell.x < min_x || cell.x > max_x ||
                cell.y < min_y || cell.y > max_y)
                continue;

            bool was_alive = cells.count(cell) && cells[cell].alive;
            bool now_alive = (count == 3) || (was_alive && count == 2);

            if (was_alive != now_alive) {
                new_state[cell] = Cell(cell.x, cell.y, now_alive, true);
            }
            else if (was_alive) {
                new_state[cell] = Cell(cell.x, cell.y, true, false);
            }
        }

        cells = std::move(new_state);
    }

    /**
     * Update the voxel world from current simulation state
     */
    void Update_World(WorldManager& world,
        const glm::ivec3& min_cube,
        const glm::ivec3& max_cube)
    {
        // Update sim bounds if cube region changed
        min_x = min_cube.x;
        max_x = max_cube.x;
        min_y = min_cube.z;
        max_y = max_cube.z;

        // Colors for interpolation
        glm::ivec3 colA(65, 105, 225), colB(220, 20, 60);

        auto sectors = world.Get_World().Get_All_Sectrs();
        for (auto sec_pair : *sectors) {
            auto chunks = sec_pair.second->Get_All_Chunks();
            for (auto chk_pair : *chunks) {
                glm::ivec3 offset(
                    sec_pair.first.X() * SECTR_SIZE_X + chk_pair.first.X() * CHUNK_SIZE_X,
                    chk_pair.first.Y() * CHUNK_SIZE_Y,
                    sec_pair.first.Z() * SECTR_SIZE_Z + chk_pair.first.Z() * CHUNK_SIZE_Z
                );

                for (int lx = MIN_ID_V_X; lx <= MAX_ID_V_X; ++lx) for (int lz = MIN_ID_V_Z; lz <= MAX_ID_V_Z; ++lz) {
                    int sx = offset.x + lx;
                    int sy = offset.z + lz;
                    if (sx < min_x || sx > max_x || sy < min_y || sy > max_y)
                        continue;

                    Cell key(sx, sy);
                    auto it = cells.find(key);
                    if (it != cells.end() && it->second.changed) {
                        glm::ivec3 c4(0);
                        if (it->second.alive) {
                            float t = (max_x > min_x)
                                ? float(sx - min_x) / float(max_x - min_x)
                                : 0.0f;
                            auto lerp = [&](int a, int b) { return int(a + t * (b - a)); };
                            c4.r = (lerp(colA.r, colB.r) * 15) / 255;
                            c4.g = (lerp(colA.g, colB.g) * 15) / 255;
                            c4.b = (lerp(colA.b, colB.b) * 15) / 255;
                        }
                        auto voxel = chk_pair.second->Get_Voxel({ lx,0,lz });
                        voxel->SetColour(c4);
                        chk_pair.second->Get_Chunk_Data().updated = true;
                    }
                }
            }
        }
    }

    /**
     * Main update call; advances sim on timer and pushes to world
     */
    void Update(WorldManager& world,
        const glm::ivec3& min_cube,
        const glm::ivec3& max_cube)
    {
        auto now = std::chrono::steady_clock::now();
        auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_update_time);
        if (dt >= update_interval) {
            last_update_time = now;
            Update_Game();
            Update_World(world, min_cube, max_cube);
        }
    }

private:
    int min_x, max_x, min_y, max_y;
    std::unordered_map<Cell, Cell, CellHash> cells;
    std::chrono::milliseconds update_interval;
    std::chrono::steady_clock::time_point last_update_time;

    // Generate neighbour coords
    std::vector<Cell> getNeighbours(const Cell& c) const {
        std::vector<Cell> out;
        for (int dx = -1; dx <= 1; ++dx) for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            out.emplace_back(c.x + dx, c.y + dy);
        }
        return out;
    }
};

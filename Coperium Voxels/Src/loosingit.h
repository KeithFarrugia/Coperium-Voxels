#pragma once
#include "WorldData/Chunk_Management/WorldManager.h"
#include "WorldData/Create_Generic_Chunks.h"
#include <random>
#include "WorldData/Chunk_Management/Mesh Generation/Chunk_Mesh.h"
#include <map>

inline void generate_multiple(WorldManager& world_1, float solid_chance, int iterations = 10) {
    constexpr int SIZE_X = 16;
    constexpr int SIZE_Y = 64;
    constexpr int SIZE_Z = 16;

    std::mt19937 rng(std::random_device{}());  // Random number generator
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    sector_loc_t s_l = sector_loc_t::Compact(glm::ivec3(0, 0, 0));
    chunk_loc_t  c_l = chunk_loc_t::Compact(glm::ivec3(0, 0, 0));
    std::shared_ptr<Chunk> c = std::make_shared<Chunk>();
    std::shared_ptr<Sector> s = std::make_shared<Sector>();

    double total_faces = 0;
    double total_voxels = 0;
    double total_time = 0;

    for (int iter = 0; iter < iterations; ++iter) {
        Chunk gen_chun;
        Create_Air_Chunk(gen_chun);
        Create_Air_Chunk(*c.get());

        int solid_voxel_count = 0;
        auto start = std::chrono::high_resolution_clock::now();

        for (int x = 0; x < SIZE_X; ++x) {
            for (int y = 0; y < SIZE_Y; ++y) {
                for (int z = 0; z < SIZE_Z; ++z) {
                    if (dist(rng) > solid_chance) continue;

                    vox_data_t voxel_data = {
                        glm::ivec3(x, y, z),
                        glm::ivec3(128, 180, 255),
                        voxel_type_t::NORMAL,
                        true,
                        false,
                        rel_loc_t::WORLD_LOC
                    };
                    c->Create_Voxel(voxel_data);
                    ++solid_voxel_count;
                }
            }
        }

        int faces = Generate_Chunk_Mesh(
            world_1.Get_World(),
            sector_pair_t{ s_l, s },
            chunk_pair_t{ c_l, c },
            gen_chun
        );

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        total_faces += faces;
        total_voxels += solid_voxel_count;
        total_time += duration.count();

        std::cout << "Iteration " << iter + 1 << ": "
            << "Voxels = " << solid_voxel_count
            << ", Faces = " << faces
            << ", Time = " << duration.count() << "s" << std::endl;
    }

    std::cout << "\n--- Averages over " << iterations << " runs ---\n"
        << "Average Voxels: " << (total_voxels / iterations) << "\n"
        << "Average Faces: "  << (total_faces / iterations) << "\n"
        << "Average Time: "   << (total_time / iterations) << " seconds\n";
}

inline void test_looping() {
    glm::ivec3 col = glm::ivec3(0, 0, 0);

    // ====== XYZ ORDER ======
    std::shared_ptr<Chunk> c_xyz = std::make_shared<Chunk>();
    auto start_xyz = std::chrono::steady_clock::now();
    uint64_t cycles_xyz_start = __rdtsc();

    for (int x = MIN_ID_V_X; x <= MAX_ID_V_X; x++) {
        for (int y = MIN_ID_V_Y; y <= MAX_ID_V_Y; y++) {
            for (int z = MIN_ID_V_Z; z <= MAX_ID_V_Z; z++) {
                c_xyz->Get_Voxel(glm::ivec3(x, y, z), rel_loc_t::CHUNK_LOC)->SetColour(col);
            }
        }
    }

    uint64_t cycles_xyz_end = __rdtsc();
    auto end_xyz = std::chrono::steady_clock::now();

    uint64_t total_cycles_xyz = cycles_xyz_end - cycles_xyz_start;
    std::chrono::duration<double> elapsed_xyz = end_xyz - start_xyz;

    std::cout << "\n[XYZ loop order]\n";
    std::cout << "  Wall time:   " << elapsed_xyz.count() << " seconds\n";
    std::cout << "  CPU cycles:  " << total_cycles_xyz << "\n";

    // ====== ZYX ORDER ======
    std::shared_ptr<Chunk> c_zyx = std::make_shared<Chunk>();
    auto start_zyx = std::chrono::steady_clock::now();
    uint64_t cycles_zyx_start = __rdtsc();

    for (int z = MIN_ID_V_Z; z <= MAX_ID_V_Z; z++) {
        for (int y = MIN_ID_V_Y; y <= MAX_ID_V_Y; y++) {
            for (int x = MIN_ID_V_X; x <= MAX_ID_V_X; x++) {
                c_zyx->Get_Voxel(glm::ivec3(x, y, z), rel_loc_t::CHUNK_LOC)->SetColour(col);
            }
        }
    }

    uint64_t cycles_zyx_end = __rdtsc();
    auto end_zyx = std::chrono::steady_clock::now();

    uint64_t total_cycles_zyx = cycles_zyx_end - cycles_zyx_start;
    std::chrono::duration<double> elapsed_zyx = end_zyx - start_zyx;

    std::cout << "\n[ZYX loop order]\n";
    std::cout << "  Wall time:   " << elapsed_zyx.count() << " seconds\n";
    std::cout << "  CPU cycles:  " << total_cycles_zyx << "\n";
}

inline void generate_multiple_density_sweep(WorldManager& world_1, int iterations = 10) {
    constexpr int SIZE_X = 16;
    constexpr int SIZE_Y = 64;
    constexpr int SIZE_Z = 16;
    constexpr int STEP_PERCENT = 5;

    std::vector<double> voxel_avgs;
    std::vector<double> face_avgs;

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    sector_loc_t s_l = sector_loc_t::Compact(glm::ivec3(0, 0, 0));
    chunk_loc_t  c_l = chunk_loc_t::Compact(glm::ivec3(0, 0, 0));
    std::shared_ptr<Chunk> c = std::make_shared<Chunk>();
    std::shared_ptr<Sector> s = std::make_shared<Sector>();
    Chunk gen_chun;

    Create_Air_Chunk(gen_chun);
    for (int percent = 0; percent <= 100; percent += STEP_PERCENT) {
        float solid_chance = percent / 100.0f;
        double total_voxels = 0;
        double total_faces = 0;

        for (int iter = 0; iter < iterations; ++iter) {
            Create_Air_Chunk(*c.get());

            int solid_voxel_count = 0;

            for (int x = 0; x < SIZE_X; ++x) {
                for (int y = 0; y < SIZE_Y; ++y) {
                    for (int z = 0; z < SIZE_Z; ++z) {
                        if (dist(rng) > solid_chance) continue;

                        vox_data_t voxel_data = {
                            glm::ivec3(x, y, z),
                            glm::ivec3(128, 180, 255),
                            voxel_type_t::NORMAL,
                            true,
                            false,
                            rel_loc_t::WORLD_LOC
                        };
                        c->Create_Voxel(voxel_data);
                        ++solid_voxel_count;
                    }
                }
            }

            int faces = Generate_Chunk_Mesh(
                world_1.Get_World(),
                sector_pair_t{ s_l, s },
                chunk_pair_t{ c_l, c },
                gen_chun
            );

            total_voxels += solid_voxel_count;
            total_faces += faces;
        }

        double avg_voxels = total_voxels / iterations;
        double avg_faces = total_faces / iterations;

        voxel_avgs.push_back(avg_voxels);
        face_avgs.push_back(avg_faces);

        std::cout << "Solid %: " << std::setw(3) << percent << "% "
            << "| Avg Voxels: " << std::setw(6) << avg_voxels
            << " | Avg Faces: " << std::setw(6) << avg_faces << std::endl;
    }

    // Output arrays as Python-compatible strings
    std::ostringstream vox_stream, face_stream;
    vox_stream << "[";
    face_stream << "[";
    for (size_t i = 0; i < voxel_avgs.size(); ++i) {
        if (i != 0) {
            vox_stream << ", ";
            face_stream << ", ";
        }
        vox_stream << std::fixed << std::setprecision(2) << voxel_avgs[i];
        face_stream << std::fixed << std::setprecision(2) << face_avgs[i];
    }
    vox_stream << "]";
    face_stream << "]";

    std::cout << "\nCopy for Python plotting:\n";
    std::cout << "voxels = " << vox_stream.str() << "\n";
    std::cout << "faces  = " << face_stream.str() << "\n";
}



inline void generate_lod_density_sweep(WorldManager& world_1, int iterations = 10) {
    constexpr int SIZE_X = 16;
    constexpr int SIZE_Y = 64;
    constexpr int SIZE_Z = 16;
    constexpr int STEP_PERCENT = 5;
    const std::vector<int> LODS = { 2, 4, 8, 16 };

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    sector_loc_t s_l = sector_loc_t::Compact(glm::ivec3(0, 0, 0));
    chunk_loc_t  c_l = chunk_loc_t::Compact(glm::ivec3(0, 0, 0));
    std::shared_ptr<Chunk> c = std::make_shared<Chunk>();
    std::shared_ptr<Sector> s = std::make_shared<Sector>();
    Chunk gen_chun;

    Create_Air_Chunk(gen_chun);

    // Store results for each LOD
    std::map<int, std::vector<double>> lod_voxel_avgs;
    std::map<int, std::vector<double>> lod_face_avgs;

    for (int lod : LODS) {
        std::cout << "\n=== LOD: " << lod << " ===\n";

        for (int percent = 0; percent <= 100; percent += STEP_PERCENT) {
            float solid_chance = percent / 100.0f;
            double total_voxels = 0;
            double total_faces = 0;

            for (int iter = 0; iter < iterations; ++iter) {
                Create_Air_Chunk(*c);

                int solid_voxel_count = 0;

                for (int x = 0; x < SIZE_X; ++x) {
                    for (int y = 0; y < SIZE_Y; ++y) {
                        for (int z = 0; z < SIZE_Z; ++z) {
                            if (dist(rng) > solid_chance) continue;

                            vox_data_t voxel_data = {
                                glm::ivec3(x, y, z),
                                glm::ivec3(128, 180, 255),
                                voxel_type_t::NORMAL,
                                true,
                                false,
                                rel_loc_t::WORLD_LOC
                            };
                            c->Create_Voxel(voxel_data);
                            ++solid_voxel_count;
                        }
                    }
                }

                int faces = Generate_Chunk_Mesh(
                    world_1.Get_World(),
                    sector_pair_t{ s_l, s },
                    chunk_pair_t{ c_l, c },
                    gen_chun,
                    lod
                );

                total_voxels += solid_voxel_count;
                total_faces += faces;
            }

            double avg_voxels = total_voxels / iterations;
            double avg_faces = total_faces / iterations;

            lod_voxel_avgs[lod].push_back(avg_voxels);
            lod_face_avgs[lod].push_back(avg_faces);

            std::cout << "Solid %: " << std::setw(3) << percent << "% "
                << "| Avg Voxels: " << std::setw(6) << avg_voxels
                << " | Avg Faces: " << std::setw(6) << avg_faces << std::endl;
        }
    }

    // Output Python-compatible arrays per LOD
    std::cout << "\n=== Python Arrays (per LOD) ===\n";
    for (int lod : LODS) {
        std::ostringstream vox_stream, face_stream;
        vox_stream << "[";
        face_stream << "[";
        for (size_t i = 0; i < lod_voxel_avgs[lod].size(); ++i) {
            if (i != 0) {
                vox_stream << ", ";
                face_stream << ", ";
            }
            vox_stream << std::fixed << std::setprecision(2) << lod_voxel_avgs[lod][i];
            face_stream << std::fixed << std::setprecision(2) << lod_face_avgs[lod][i];
        }
        vox_stream << "]";
        face_stream << "]";

        std::cout << "voxels_lod_" << lod << " = " << vox_stream.str() << "\n";
        std::cout << "faces_lod_" << lod << "  = " << face_stream.str() << "\n\n";
    }
}

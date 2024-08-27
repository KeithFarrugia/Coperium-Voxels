#pragma once
#ifndef TEST_H
#define TEST_H

#include <COIL/Utility.h>
#include <COIL/Shaders/Shader.h>
#include <COIL/Mesh/Basic_Mesh.h>
#include <COIL/Window/Window.h>
#include <COIL/Camera/Fly Camera/Fly_Camera.h>


#include "../Compact Data/Compact Location Data/CLD.h"
#include "../Compact Data/Compact Colour Data/CCD.h"
#include "../Compact Data/Compact Block/CB.h"

constexpr int GRID_SIZE_X = 16;
constexpr int GRID_SIZE_Y = 64;
constexpr int GRID_SIZE_Z = 16;

std::unique_ptr<GLfloat[]> FlattenMeshVector(const std::vector<std::unique_ptr<GLfloat[]>>& meshes, int& totalSize) {
    totalSize = 0;
    for (const auto& mesh : meshes) {
        totalSize += COMPACT_CUBE_SIZE;
    }

    auto flattenedMesh = std::make_unique<GLfloat[]>(totalSize);
    size_t offset = 0;
    for (const auto& mesh : meshes) {
        std::copy(mesh.get(), mesh.get() + COMPACT_CUBE_SIZE, flattenedMesh.get() + offset);
        offset += COMPACT_CUBE_SIZE;
    }
    return flattenedMesh;
}

std::unique_ptr<GLfloat[]> FlattenMeshVector_OLD(const std::vector<std::unique_ptr<GLfloat[]>>& meshes, int& totalSize) {
    totalSize = 0;
    for (const auto& mesh : meshes) {
        totalSize += SIMPLE_CUBE_SIZE;
    }

    auto flattenedMesh = std::make_unique<GLfloat[]>(totalSize);
    size_t offset = 0;
    for (const auto& mesh : meshes) {
        std::copy(mesh.get(), mesh.get() + SIMPLE_CUBE_SIZE, flattenedMesh.get() + offset);
        offset += SIMPLE_CUBE_SIZE;
    }
    return flattenedMesh;
}



inline void Render_Simple_Cube_Mesh(Coil::Basic_Mesh& mesh, Coil::Shader& shader) {
    std::vector<std::unique_ptr<GLfloat[]>> cubeMeshes;
    for (int x = 0; x < GRID_SIZE_X; x++) {
        for (int y = 0; y < GRID_SIZE_Y; y++) {
            for (int z = 0; z < GRID_SIZE_Z; z++) {
                CB cube(x, y, z, x, (int)(y / 4.0f), z);
                auto sub_mesh = cube.Generate_Mesh_Old();
                cubeMeshes.push_back(std::move(sub_mesh));
            }
        }
    }

    int totalSize   = 0;
    auto cubesMesh  = FlattenMeshVector_OLD(cubeMeshes, totalSize);

    printf("Size : %d floats\n", totalSize);

    mesh.Configure_Mesh(
        cubesMesh.get(),
        sizeof(GLfloat),
        totalSize,
        GL_FLOAT,
        SIMPLE_CUBE_ELEMENTS
    );

    mesh.Add_Vertex_Set(0, 3, 0);
    mesh.Add_Vertex_Set(1, 3, 3);
    mesh.Clean_Mesh();

    shader.Add_Shaders(
        Coil::shader_list_t{
            Coil::shader_info_t{ "basic.vert", Coil::shader_type_t::VERTEX_SHADER   },
            Coil::shader_info_t{ "basic.frag", Coil::shader_type_t::FRAGMENT_SHADER }
        });
    shader.Compile_And_Link();
}

inline void Render_Compact_Cube_Mesh(Coil::Basic_Mesh& mesh, Coil::Shader& shader) {
    std::vector<std::unique_ptr<GLfloat[]>> cubeMeshes;
    for (int x = 0; x < GRID_SIZE_X; x++) {
        for (int y = 0; y < GRID_SIZE_Y; y++) {
            for (int z = 0; z < GRID_SIZE_Z; z++) {
                CB cube(x, y, z, x, (int)(y / 4.0f), z);
                auto sub_mesh = cube.Generate_Mesh();
                cubeMeshes.push_back(std::move(sub_mesh));
            }
        }
    }

    int totalSize = 0;
    auto cubesMesh = FlattenMeshVector(cubeMeshes, totalSize);

    printf("Size : %d floats\n", totalSize);

    mesh.Configure_Mesh(
        cubesMesh.get(),
        sizeof(GLfloat),
        totalSize,
        GL_FLOAT,
        COMPACT_CUBE_ELEMENTS
    );

    mesh.Add_Vertex_Set(0, 1, 0);
    mesh.Add_Vertex_Set(1, 1, 1);
    mesh.Clean_Mesh();

    shader.Add_Shaders(
        Coil::shader_list_t{
            Coil::shader_info_t{ "compact_v2.vert", Coil::shader_type_t::VERTEX_SHADER   },
            Coil::shader_info_t{ "compact_v2.frag", Coil::shader_type_t::FRAGMENT_SHADER }
        });
    shader.Compile_And_Link();
}

#endif // !TEST_H
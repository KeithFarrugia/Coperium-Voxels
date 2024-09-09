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

std::unique_ptr<GLuint[]> FlattenIndexVector(const std::vector<std::unique_ptr<GLuint[]>>& indexBuffers, int& totalSize) {
    totalSize = 0;
    for (const auto& buffer : indexBuffers) {
        totalSize += COMPACT_CUBE_INDEX_SIZE;
    }

    auto flattenedIndices = std::make_unique<GLuint[]>(totalSize);
    size_t offset = 0;
    for (const auto& buffer : indexBuffers) {
        std::copy(buffer.get(), buffer.get() + COMPACT_CUBE_INDEX_SIZE, flattenedIndices.get() + offset);
        offset += COMPACT_CUBE_INDEX_SIZE;
    }
    return flattenedIndices;
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

std::unique_ptr<GLuint[]> AdjustIndices(const GLuint* indices, size_t indexCount, int vertexOffset) {
    auto adjustedIndices = std::make_unique<GLuint[]>(indexCount);
    for (size_t i = 0; i < indexCount; i++) {
        adjustedIndices[i] = indices[i] + vertexOffset;
    }
    return adjustedIndices;
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
    std::vector<std::unique_ptr<GLuint[]>> indexBuffers;

    int totalVertices = 0;
    int totalIndices = 0;

    // Iterate over the grid to create and collect cube meshes and index buffers.
    for (int x = 0; x < GRID_SIZE_X; x++) {
        for (int y = 0; y < GRID_SIZE_Y; y++) {
            for (int z = 0; z < GRID_SIZE_Z; z++) {
                CB cube(x, y, z, x, static_cast<int>(y / 4.0f), z);
                auto sub_mesh = cube.Generate_Mesh();

                // Push vertex data.
                cubeMeshes.push_back(std::move(sub_mesh.vert_data));

                // Adjust index data for the accumulated number of vertices and push it.
                auto adjustedIndices = AdjustIndices(sub_mesh.inde_data.get(), COMPACT_CUBE_INDEX_SIZE, totalVertices);
                indexBuffers.push_back(std::move(adjustedIndices));

                // Update totals.
                totalVertices += COMPACT_CUBE_SIZE / COMPACT_CUBE_ELEMENTS;
                totalIndices += COMPACT_CUBE_INDEX_SIZE;
            }
        }
    }

    int totalSizeVertices = totalVertices * COMPACT_CUBE_ELEMENTS; // Total number of elements in vertex data.
    int totalSizeIndices = totalIndices;

    auto flattenedVertices = FlattenMeshVector(cubeMeshes, totalSizeVertices);
    auto flattenedIndices = FlattenIndexVector(indexBuffers, totalSizeIndices);

    printf("Total Vertices: %d, Total Indices: %d\n", totalVertices, totalIndices);

    // Configure the mesh with both vertex and index data.
    mesh.Configure_Mesh(
        flattenedVertices.get(),
        sizeof(GLfloat),
        totalSizeVertices,
        GL_FLOAT,
        COMPACT_CUBE_ELEMENTS
    );

    // Configure the index buffer
    mesh.Configure_Index_Buffer(
        flattenedIndices.get(),
        sizeof(GLuint),
        totalSizeIndices
    );

    mesh.Add_Vertex_Set(0, 1, 0);
    mesh.Add_Vertex_Set(1, 1, 1);
    mesh.Clean_Mesh();

    shader.Add_Shaders(
        Coil::shader_list_t{
            Coil::shader_info_t{"compact_v2.vert", Coil::shader_type_t::VERTEX_SHADER},
            Coil::shader_info_t{"compact_v2.frag", Coil::shader_type_t::FRAGMENT_SHADER}
        });
    shader.Compile_And_Link();
}

#endif // !TEST_H
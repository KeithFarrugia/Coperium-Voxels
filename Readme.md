<h1 align="center">Coperium Voxels</h1>

<p align="center">
  <img src="ict_logo.png" alt="University of Malta Logo" width="50%"/>
</p>

<h2 align="center"><em>A novel data structure for voxel rendering</em></h2>

<p align="center">
  <strong>Keith Farrugia</strong>  
  <br/>
  University of Malta
  <br/>
  Supervisor: Dr Keith Bugeja 
  <br/>
  Co-Supervisor: Dr Sandro Spina
</p>

<p align="center">
  <img src="Banner.png" alt="Coperium Voxels Banner" width="800"/>
</p>

---

## Overview

*Coperium Voxels* is a voxel-based 3D rendering and interaction system developed as part of my final year dissertation at the University of Malta. The project explores efficient voxel data structures, real-time rendering techniques, and interactive editing capabilities.

---

## Prerequisites

To build and run this project, ensure you have the following installed:

- **Visual Studio 2022** with the following workloads:
  - **Desktop Development with C++**
- **Windows 10 SDK** (typically included with Visual Studio)
- Needs a **windows 10** / **11 machine**
---

## Building and Running the Project

1. **Clone the Repository**
   ```bash
   git clone https://github.com/KeithFarrugia/Coperium-Voxels.git
   cd Coperium-Voxels
2. **Open the Solution**

   * Launch **Visual Studio 2022**.
   * Open the `Coperium Voxels.sln` solution file.

3. **Build the Solution**

   * Select the desired build configuration (**Debug** or **Release**).
   * Press `Ctrl + Shift + B` to build the solution.

4. **Run the Application**

   * Set the startup project if not already set:

     * Right-click on the desired project in the **Solution Explorer**.
     * Select **Set as Startup Project**.
   * Press `F5` to run the application.

---

## Controls & Inputs

* **W, A, S, D**: Move forward, left, backward, and right relative to the camera's facing direction.
* **Space**: Move up.
* **Left Shift**: Move down.
* **Scroll Wheel**: Zoom the camera in and out.
* **Tab**: Unlocks the mouse cursor for free movement, but is somewhat unstable - may require multiple presses and can be finicky.
* **Window Resizing**: The application window can be resized, but this feature is unstable and **not recommended** for regular use.

---


## Default World Selection (Using `Create_Default_World`)

This voxel engine provides several **example world setups** designed to demonstrate key features, configurations, and test scenarios used throughout the development and evaluation in the accompanying report. These defaults act as starting templates to showcase how different world behaviours and systems can be configured using the engine.

-  **Note:** These preset names are *examples only* and not required. The engine supports **any custom world name**. However, names listed below receive special configuration in the `Create_Default_World` function for demonstration purposes. You can remove or replace them entirely in your own implementation.

### How to Set the Default World

When creating a `WorldManager` instance, you specify the world by passing a string name to its constructor. If you are passing the world through the `Create_Default_World` function this name will be used to pick a pre-configured setup:

```cpp
WorldManager world("mount");
Create_Default_World(world);
```

Replace `"mount"` with one of the supported world preset names to load a specific world configuration.

| **World Name** | **Description**                                                                                     |
| :------------: | :-------------------------------------------------------------------------------------------------- |
|     `mount`    | Static model world loaded from heightmap data. Procedural generation disabled.                      |
|    `sponza`    | Static model world using sky-blue colour mapping. Procedural generation disabled.                   |
|    `canway`    | Runs Conway's Game of Life simulation within the voxel world. No chunk loading/saving.              |
|     `wave`     | Procedurally generates a wave-like landscape with static chunks.                                    |
|    `dynamic`   | Dynamic world with automatic chunk loading/unloading and file storage enabled. Procedural disabled. |


---

## World Settings

The `world_settings_t` struct contains configuration options for world loading, rendering, level of detail, generation, and debugging. Below is a description of each setting:

### General Settings Table

|        **Setting**       |     **Type**    |  **Default**  | **Description**                                     |
| :----------------------: | :-------------: | :-----------: | :-------------------------------------------------- |
|        `mass_load`       |      `bool`     |    `false`    | Load entire world from save during initialization   |
|        `auto_load`       |      `bool`     |    `false`    | Automatically load new chunks as needed             |
|       `auto_unload`      |      `bool`     |    `false`    | Automatically unload chunks that are far away       |
|  `allow_load_from_file`  |      `bool`     |     `true`    | Permit loading chunks from disk                     |
| `allow_chunk_generation` |      `bool`     |     `true`    | Allow procedural generation of chunks               |
|    `allow_chunk_store`   |      `bool`     |     `true`    | Allow saving chunks back to disk                    |
|      `render_world`      |      `bool`     |     `true`    | Enable rendering of the world                       |
|      `mesh_changes`      |      `bool`     |     `true`    | Allow updates to chunk meshes                       |
|   `update_interval_ms`   |      `int`      |     `500`     | Minimum milliseconds between mesh updates           |
|         `use_lod`        |      `bool`     |     `true`    | Enable level-of-detail (LOD) based mesh detail      |
|       `dynamic_lod`      |      `bool`     |     `true`    | Recompute LOD on camera movement                    |
|      `smart_update`      |      `bool`     |     `true`    | Skip LOD update if camera hasn't moved              |
|         `lod_set`        | `lod_dst_set_t` | *(see below)* | Distance thresholds for different LOD levels        |
|      `chunk_radius`      |      `int`      |      `1`      | Radius in chunks around the player to generate/load |
|      `generic_chunk`     |     `Chunk`     |    *(none)*   | Prototype chunk used for mesh generation            |
|      `smart_render`      |      `bool`     |     `true`    | Render only chunks visible to the player            |
|          `debug`         |      `bool`     |    `false`    | Enable debug logging                                |

---

### LOD Distance Thresholds (`lod_set`)

| **LOD Level** | **Distance Threshold (units²)** |  **Calculation**  |
| :-----------: | :-----------------------------: | :---------------: |
|    `NORMAL`   |             `2500.0`            |  `50.0f * 50.0f`  |
|    `LOD_2`    |            `10000.0`            | `100.0f * 100.0f` |
|    `LOD_4`    |            `40000.0`            | `200.0f * 200.0f` |
|    `LOD_8`    |            `160000.0`           | `400.0f * 400.0f` |

---




## External Libraries Used

This project uses a number of open-source libraries to streamline development and provide key functionality in rendering, input handling, mathematics, and GUI support:

| **Library** | **Description**                                                                                     | **Link**                                                     |
| ----------- | --------------------------------------------------------------------------------------------------- | ------------------------------------------------------------ |
| **GLFW 3**  | A multi-platform library for creating windows, handling input, and managing OpenGL/Vulkan contexts. | [glfw.org](https://www.glfw.org/)                            |
| **Glad**    | OpenGL function loader that simplifies working with modern OpenGL extensions and function pointers. | [glad.dav1d.de](https://glad.dav1d.de/)                      |
| **GLM**     | Header-only mathematics library designed for graphics software and compliant with GLSL syntax.      | [github.com/g-truc/glm](https://github.com/g-truc/glm)       |
| **ImGui**   | Immediate-mode graphical user interface toolkit for in-app tools, debug panels, and overlays.       | [github.com/ocornut/imgui](https://github.com/ocornut/imgui) |
| **KHR**     | Khronos platform headers and definitions used with OpenGL/Vulkan implementations.                   | [github.com/KhronosGroup](https://github.com/KhronosGroup)   |
| **STB**     | Collection of single-file public-domain libraries for image loading, font rendering, etc.           | [github.com/nothings/stb](https://github.com/nothings/stb)   |

### COIL (Custom Wrapper Library)

COIL is a general-purpose C++ wrapper library that I developed to simplify working with OpenGL and associated systems. It provides abstraction layers for window creation, input handling, shader management, and other utilities by integrating the libraries listed above into a more user-friendly interface.

    Note: COIL is heavily inspired by the structure and coding style of LearnOpenGL, borrowing many ideas in its abstraction and resource management.
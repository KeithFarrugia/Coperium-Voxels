#pragma once

// Forward declare OpenGL types instead of including glad
typedef unsigned int GLuint;

#include <glm/glm.hpp>
#include <COIL/Shaders/Shader.h>
#include <COIL/Window/Window.h>
#include <iostream>

class DeferredRenderer {
public:
    DeferredRenderer(int width, int height);
    ~DeferredRenderer();

    void BindFramebuffer();
    void UnbindFramebuffer();
    void Init(Coil::Shader& shader);
    void Render(Coil::Shader& shader);
    void Resize(int newWidth, int newHeight);

private:
    int width, height;
    GLuint gBuffer = 0;
    GLuint gPosition = 0, gNormal = 0, gColorSpec = 0, rboDepth = 0;
    GLuint quadVAO = 0, quadVBO = 0;

    void setupFramebuffer();
    void renderQuad();
};

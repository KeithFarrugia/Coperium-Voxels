

#include <glad/glad.h>
#include "DeferredRenderer.h"
DeferredRenderer::DeferredRenderer(int width, int height)
    : width(width), height(height) {
    setupFramebuffer();
}

DeferredRenderer::~DeferredRenderer() {
    glDeleteFramebuffers(1, &gBuffer);
    glDeleteTextures(1, &gPosition);
    glDeleteTextures(1, &gNormal);
    glDeleteTextures(1, &gColorSpec);
    glDeleteRenderbuffers(1, &rboDepth);
    if (quadVAO) glDeleteVertexArrays(1, &quadVAO);
    if (quadVBO) glDeleteBuffers(1, &quadVBO);
}

void DeferredRenderer::BindFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
}

void DeferredRenderer::UnbindFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DeferredRenderer::Init(Coil::Shader& shader) {
    shader.Use();
    shader.Set_Int("gPosition", 0);
    shader.Set_Int("gNormal", 1);
    shader.Set_Int("gAlbedoSpec", 2);
}

void DeferredRenderer::Render(Coil::Shader& shader) {
    shader.Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, gColorSpec);
    renderQuad();

    glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
}

void DeferredRenderer::Resize(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
    glDeleteFramebuffers(1, &gBuffer);
    glDeleteTextures(1, &gPosition);
    glDeleteTextures(1, &gNormal);
    glDeleteTextures(1, &gColorSpec);
    glDeleteRenderbuffers(1, &rboDepth);
    setupFramebuffer();
}

void DeferredRenderer::SetSizeCallback(Coil::Window& window){
    window.Add_Size_Callback([this](Coil::Window& win) {
        this->Window_Size_Callback(win);
    });
}

void DeferredRenderer::setupFramebuffer() {
    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

    auto setupTexture = [](GLuint& tex, int w, int h) {
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB10_A2, w, h, 0, GL_RGBA, GL_UNSIGNED_INT_10_10_10_2, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        };

    setupTexture(gPosition, width, height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

    setupTexture(gNormal, width, height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

    setupTexture(gColorSpec, width, height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gColorSpec, 0);

    GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);

    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DeferredRenderer::renderQuad() {
    if (quadVAO == 0) {
        float quadVertices[] = {
            1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
           -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
           -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        };
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void DeferredRenderer::Window_Size_Callback(Coil::Window& window){
    int new_width, new_height;
    window.Get_Size(new_width, new_height);

    Resize(new_width, new_height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}



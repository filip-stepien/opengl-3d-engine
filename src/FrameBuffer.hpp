#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

struct PixelInfo {
    GLuint idObject { 0 };
    GLuint idPrim { 0 };
    GLuint _ { 0 };

    void print() {
        std::printf("object = %d, prim = %d\n", idObject, idPrim);
    }
};

class FrameBuffer {
private:
    GLuint id { 0 };
    GLuint idPrimitiveTexture { 0 };
    GLuint idDepthTexture { 0 };

    void generatePrimitiveTexture(GLuint windowWidth, GLuint windowHeight);
    void generateDepthTexture(GLuint windowWidth, GLuint windowHeight);
    void initialize();

public:
    FrameBuffer();
    ~FrameBuffer();

    void bind();
    void unbind();
    void bindPrimitiveTexture();
    void bindDepthTexture();
    void unbindTexture();
    void enableWriting();
    void disableWriting();
    void enableReading();
    void disableReading();

    PixelInfo readPixel(GLuint x, GLuint y);
};

#endif
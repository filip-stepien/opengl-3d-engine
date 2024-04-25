#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

class FrameBuffer {
private:
    GLuint id { 0 };
    GLuint idPrimitiveTexture { 0 };
    GLuint idDepthTexture { 0 };

    void generatePrimitiveTexture(GLuint windowWidth, GLuint windowHeight);
    void generateDepthTexture(GLuint windowWidth, GLuint windowHeight);

public:
    struct PixelInfo {
        GLuint idObject = 0;
        GLuint idDraw = 0;
        GLuint idPrim = 0;

        void print() {
            std::printf("object = %d, draw = %d, prim = %d\n", idObject, idDraw, idPrim);
        }
    };

    FrameBuffer();
    ~FrameBuffer();

    void initialize();
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
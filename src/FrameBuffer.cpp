#include "FrameBuffer.hpp"
#include "Engine.hpp"

FrameBuffer::FrameBuffer() {
    glGenFramebuffers(1, &id);
    glGenTextures(1, &idPrimitiveTexture);
    glGenTextures(1, &idDepthTexture);
    initialize();
}

FrameBuffer::~FrameBuffer() {
    glDeleteBuffers(1, &id);
    glDeleteTextures(1, &idPrimitiveTexture);
    glDeleteTextures(1, &idDepthTexture);
}

void FrameBuffer::generatePrimitiveTexture(GLuint windowWidth, GLuint windowHeight) {
    bindPrimitiveTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32UI, windowWidth, windowHeight, 0, GL_RGB_INTEGER, GL_UNSIGNED_INT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, idPrimitiveTexture, 0);
}

void FrameBuffer::generateDepthTexture(GLuint windowWidth, GLuint windowHeight) {
    bindDepthTexture();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, windowWidth, windowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, idDepthTexture, 0);
}

void FrameBuffer::initialize() {
    GLuint windowWidth = Engine::get().getWindowWidth();
    GLuint windowHeight = Engine::get().getWindowHeight();

    bind();
    generatePrimitiveTexture(windowWidth, windowHeight);
    generateDepthTexture(windowWidth, windowHeight);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer error: " << status << std::endl;
    }

    unbindTexture();
    unbind();
}

void FrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void FrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::bindPrimitiveTexture() {
    glBindTexture(GL_TEXTURE_2D, idPrimitiveTexture);
}

void FrameBuffer::bindDepthTexture() {
    glBindTexture(GL_TEXTURE_2D, idDepthTexture);
}

void FrameBuffer::unbindTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void FrameBuffer::enableWriting() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, id);
}

void FrameBuffer::disableWriting() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void FrameBuffer::enableReading() {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, id);
    glReadBuffer(GL_COLOR_ATTACHMENT0);
}

void FrameBuffer::disableReading() {
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

PixelInfo FrameBuffer::readPixel(GLuint x, GLuint y) {
    PixelInfo pixel;

    enableReading();
    glReadPixels(x, y, 1, 1, GL_RGB_INTEGER, GL_UNSIGNED_INT, &pixel);
    disableReading();

    return pixel;
}
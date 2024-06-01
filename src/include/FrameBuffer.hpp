#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include "EngineObject.hpp"

/**
 * @struct PixelInfo
 * @brief Structure to hold information about a pixel.
 */
struct PixelInfo {
    /// ID of the object.
    GLuint idObject { 0 };

    /// ID of the primitive.
    GLuint idPrim { 0 };

    /// Unused placeholder.
    GLuint _ { 0 };

    /**
     * @brief Prints the pixel information.
     */
    void print() {
        std::printf("object = %d, prim = %d\n", idObject, idPrim);
    }
};

/**
 * @class FrameBuffer
 * @brief OpenGL Frame Buffer Object.
 */
class FrameBuffer {
private:
    /// ID of the frame buffer.
    GLuint id { 0 };

    /// ID of the primitive texture.
    GLuint idPrimitiveTexture { 0 };

    /// ID of the depth texture.
    GLuint idDepthTexture { 0 };

    /**
     * @brief Generates the primitive texture.
     *
     * It's the texture to which the pixels will be written.
     *
     * @param windowWidth The width of the window.
     * @param windowHeight The height of the window.
     */
    void generatePrimitiveTexture(GLuint windowWidth, GLuint windowHeight);

    /**
     * @brief Generates the depth texture.
     *
     * The depth of the pixel is being written as well.
     *
     * @param windowWidth The width of the window.
     * @param windowHeight The height of the window.
     */
    void generateDepthTexture(GLuint windowWidth, GLuint windowHeight);

    /**
     * @brief Initializes the frame buffer.
     *
     * Initialization consist of generating textures to which the pixels will be written.
     */
    void initialize();

public:
    /**
     * @brief Constructor for FrameBuffer.
     * Generates the frame buffer and textures.
     */
    FrameBuffer();

    /**
     * @brief Destructor for FrameBuffer.
     * Deletes the framebuffer and textures.
     */
    ~FrameBuffer();

    /**
     * @brief Binds the frame buffer.
     */
    void bind();

    /**
     * @brief Unbinds the frame buffer.
     */
    void unbind();

    /**
     * @brief Binds the primitive texture.
     */
    void bindPrimitiveTexture();

    /**
     * @brief Binds the depth texture.
     */
    void bindDepthTexture();

    /**
     * @brief Unbinds the texture.
     */
    void unbindTexture();

    /**
     * @brief Enables writing to the frame buffer.
     */
    void enableWriting();

    /**
     * @brief Disables writing to the frame buffer.
     */
    void disableWriting();

    /**
     * @brief Enables reading from the frame buffer.
     */
    void enableReading();

    /**
     * @brief Disables reading from the frame buffer.
     */
    void disableReading();

    /**
     * @brief Reads a pixel from the frame buffer.
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @return The information of the pixel.
     */
    PixelInfo readPixel(GLuint x, GLuint y);
};

#endif

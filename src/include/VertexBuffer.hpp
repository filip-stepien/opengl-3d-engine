#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

namespace engine {
    /**
     * @struct Vertex
     * @brief Structure to hold vertex data.
     */
    struct Vertex {
        /// Position of the vertex.
        glm::vec3 position;

        /// Normal of the vertex.
        glm::vec3 normal;

        /// Texture coordinates of the vertex.
        glm::vec2 texture;
    };

/**
 * @class VertexBuffer
 * @brief OpenGL Vertex Buffer Object.
 */
    class VertexBuffer {
    private:
        /// ID of the Vertex Buffer Object.
        GLuint id;

    public:
        /**
         * @brief Constructor for VertexBuffer.
         * Generates the VBO.
         */
        VertexBuffer();

        /**
         * @brief Destructor for VertexBuffer.
         * Deletes the VBO.
         */
        ~VertexBuffer();

        /**
         * @brief Sets the data for the vertex buffer.
         * @param vertices A vector of vertices to be stored in the buffer.
         * @param usage The usage pattern of the buffer. Defaults to GL_STATIC_DRAW.
         */
        void setData(std::vector<Vertex> &vertices, GLenum usage = GL_STATIC_DRAW);

        /**
         * @brief Binds the vertex buffer.
         */
        void bind();

        /**
         * @brief Unbinds the vertex buffer.
         */
        void unbind();
    };
}

#endif

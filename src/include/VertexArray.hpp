#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "VertexBuffer.hpp"

namespace engine {
    /**
     * @class VertexArray
     * @brief OpenGL Vertex Array Object.
     */
    class VertexArray {
    private:
        /// ID of the Vertex Array Object.
        GLuint id { 0 };

    public:
        /**
         * @brief Constructor for VertexArray.
         * Generates the VAO.
         */
        VertexArray();

        /**
         * @brief Destructor for VertexArray.
         * Deletes the VAO.
         */
        ~VertexArray();

        /**
         * @brief Sets the attribute pointer for the vertex array.
         * @param layout The layout location of the attribute.
         * @param numOfValues The number of values in the attribute.
         * @param pointerVal The offset of the first component of the attribute.
         */
        void setAttribPointer(GLuint layout, GLuint numOfValues, GLuint pointerVal);

        /**
         * @brief Binds the VAO.
         */
        void bind();

        /**
         * @brief Unbinds the VAO.
         */
        void unbind();

        /**
         * @brief Draws the vertices in the VAO.
         * @param numOfVertices The number of vertices to draw.
         * @param primitive The type of primitive to draw. Defaults to GL_TRIANGLES.
         */
        void drawVertices(GLuint numOfVertices, GLenum primitive = GL_TRIANGLES);

        /**
         * @brief Draws the elements in the VAO.
         * @param numOfIndices The number of indices to draw.
         * @param primitive The type of primitive to draw. Defaults to GL_TRIANGLES.
         */
        void drawIndices(GLuint numOfIndices, GLenum primitive = GL_TRIANGLES);
    };
}

#endif

#ifndef ELEMENT_BUFFER_H
#define ELEMENT_BUFFER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace engine {
    /**
     * @class ElementBuffer
     * @brief OpenGL Element Buffer Object.
     */
    class ElementBuffer {
    private:
        /// ID of the element buffer.
        GLuint id;

    public:
        /**
         * @brief Constructor for ElementBuffer.
         * Generates and initializes the element buffer.
         */
        ElementBuffer();

        /**
         * @brief Destructor for ElementBuffer.
         * Deletes the element buffer.
         */
        ~ElementBuffer();

        /**
         * @brief Sets the data for the element buffer.
         * @param indices A vector of indices to be stored in the buffer.
         * @param usage The usage pattern of the buffer. Defaults to GL_STATIC_DRAW.
         */
        void setData(std::vector<GLuint> &indices, GLenum usage = GL_STATIC_DRAW);

        /**
         * @brief Binds the element buffer.
         */
        void bind();

        /**
         * @brief Unbinds the element buffer.
         */
        void unbind();
    };
}

#endif

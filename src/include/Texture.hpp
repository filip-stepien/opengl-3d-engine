#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace engine {
    /**
     * @class Texture
     * @brief OpenGL texture.
     */
    class Texture {
    public:
        /// Texture type.
        using TextureType = enum TEXTURE {
            DIFFUSE,
            SPECULAR
        };

    private:
        /// Type of the texture.
        TextureType type{DIFFUSE};

        /// ID of the texture.
        GLuint id{0};

        /// Wrapping mode for the texture.
        GLenum wrapping{GL_REPEAT};

        /// Path to the texture file.
        const char *path{"../resources/textures/default.png"};

        /**
         * @brief Loads the image from the specified path.
         * @param path The path to the image file.
         *
         * @note Image loading supports multiple formats.
         */
        void loadImage(const char *path);

    public:
        /**
         * @brief Constructor for Texture.
         * @param type The type of the texture (DIFFUSE or SPECULAR).
         * @param path The path to the texture file.
         * @param wrapping The wrapping mode for the texture.
         */
        Texture(
                TextureType type = DIFFUSE,
                const char *path = "../resources/textures/default.png",
                GLenum wrapping = GL_REPEAT
        );

        /**
         * @brief Destructor for Texture.
         * Deletes texture.
         */
        ~Texture();

        /**
         * @brief Initializes the texture.
         * Loads an image and generates the texture.
         */
        void initialize();

        /**
         * @brief Binds the texture.
         */
        void bind();

        /**
         * @brief Unbinds the texture.
         */
        void unbind();
    };
}

#endif

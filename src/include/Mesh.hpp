#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "ElementBuffer.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Drawable.hpp"
#include "Transformable.hpp"

namespace engine {
    /**
     * @class Mesh
     * @brief Mesh of the 3D object.
     */
    class Mesh : public Drawable, public Transformable {
    protected:
        /// Vertices of the mesh.
        std::vector<Vertex> vertices{};

        /// Indices of the mesh.
        std::vector<GLuint> indices{};

        /// Vertex Array Object.
        VertexArray *vao{nullptr};

        /// Vertex Buffer Object.
        VertexBuffer *vbo{nullptr};

        /// Element Buffer Object.
        ElementBuffer *ebo{nullptr};

        /// Diffuse texture.
        Texture *diffuse{new Texture(Texture::DIFFUSE)};

        /// Specular texture.
        Texture *specular{new Texture(Texture::SPECULAR)};

        /// Shininess of the mesh.
        GLfloat shininess{30.0f};

        /// Texture scale in X direction.
        GLfloat textureScaleX{1.0f};

        /// Texture scale in Y direction.
        GLfloat textureScaleY{1.0f};

        /// Flag indicating if the mesh is view independent.
        bool viewIndependent{false};

        /// Flag indicating if the mesh ignores lighting.
        bool ignoreLight{false};

        /// Flag indicating if the mesh is in the foreground.
        bool foreground{false};

    public:
        /**
         * @brief Constructor for Mesh.
         * @param vertices A vector of vertices for the mesh.
         * @param indices A vector of indices for the mesh.
         *
         * Adds Mesh to the rendering queue.
         */
        Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);

        /**
         * @brief Destructor for Mesh.
         * Deletes buffer objects and textures.
         */
        ~Mesh();

        /**
         * @brief Sets the diffuse texture.
         * @param path Path to the texture file.
         */
        void setDiffuseTexture(const char *path);

        /**
         * @brief Sets the specular texture.
         * @param path Path to the texture file.
         */
        void setSpecularTexture(const char *path);

        /**
         * @brief Sets the shininess of the mesh.
         * @param shininess The new shininess value.
         */
        void setShininess(GLfloat shininess);

        /**
         * @brief Sets the texture scale.
         * @param scaleX Scale in the X direction.
         * @param scaleY Scale in the Y direction.
         */
        void setTextureScale(float scaleX, float scaleY);

        /**
         * @brief Sets whether the mesh should ignore light.
         * @param ignore Whether to ignore light.
         */
        void setIgnoreLight(bool ignore);

        /**
         * @brief Sets whether the mesh is view independent.
         * @param independent Whether the mesh is view independent.
         *
         * If the mesh is view independent, it ignores view matrix in the basic vertex shader.
         */
        void setViewIndependent(bool independent);

        /**
         * @brief Sets whether the mesh is in the foreground.
         * @param foreground Whether the mesh is in the foreground.
         *
         * Foreground object is drawn as the last object.
         * Also before a render call the depth buffer is cleared.
         */
        void setOnForeground(bool foreground);

        /**
         * @brief Gets the diffuse texture.
         * @return Pointer to the diffuse texture.
         */
        Texture *getDiffuseTexture();

        /**
         * @brief Gets the specular texture.
         * @return Pointer to the specular texture.
         */
        Texture *getSpecularTexture();

        /**
         * @brief Gets the shininess of the mesh.
         * @return The shininess value.
         */
        GLfloat getShininess();

        /**
         * @brief Checks if the mesh is view independent.
         * @return True if the mesh is view independent, false otherwise.
         */
        bool isViewIndependent();

        /**
         * @brief Checks if the mesh is in the foreground.
         * @return True if the mesh is in the foreground, false otherwise.
         */
        bool isOnForeground();

        /**
         * @brief Initializes the mesh.
         * Sets buffers' data and initializes textures.
         */
        virtual void initialize();

        /**
         * @brief Draws the mesh using the provided shader.
         * @param shader The shader to use for drawing.
         *
         * It also sets the uniforms in the shaders which are responsible for mesh
         * model, material parameters, texture scale and booleans indicating view
         * independence and light ignoring.
         */
        void draw(Shader &shader) override;

        /**
         * @brief Draws the mesh to a buffer using the provided shader.
         * @param shader The shader to use for drawing to the buffer.
         *
         * It also sets the uniform in the picking shader which is responsible
         * for setting object ID in the 'r' (red) component of the pixel
         * in the frame buffer texture.
         */
        void drawToBuffer(Shader &shader) override;
    };
}

#endif

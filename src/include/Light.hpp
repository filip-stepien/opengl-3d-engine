#ifndef LIGHT_H
#define LIGHT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

#include "Transformable.hpp"
#include "Updatable.hpp"
#include "Shader.hpp"

namespace engine {
    /**
     * @class Light
     * @brief Point light present in the scene.
     *
     * It implements simple [Phong lighting model](https://en.wikipedia.org/wiki/Phong_reflection_model).
     */
    class Light : public Updatable, public Transformable {
    private:
        /// Constant defining maximum number of lights in the scene.
        const int MAX_LIGHTS{8};

        /// Ambient color of the light.
        glm::vec3 ambient{0.2f};

        /// Diffuse color of the light.
        glm::vec3 diffuse{1.0f};

        /// Specular color of the light.
        glm::vec3 specular{1.0f};

    public:
        /**
         * @brief Constructor for Light.
         * Adds the light to the rendering queue.
         */
        Light();

        /**
         * @brief Sets the ambient color of the light.
         * @param ambient The new ambient color (r, g, b).
         */
        void setAmbient(glm::vec3 ambient);

        /**
         * @brief Sets the diffuse color of the light.
         * @param diffuse The new diffuse color (r, g, b).
         */
        void setDiffuse(glm::vec3 diffuse);

        /**
         * @brief Sets the specular color of the light.
         * @param specular The new specular color (r, g, b).
         */
        void setSpecular(glm::vec3 specular);

        /**
         * @brief Sets the ambient color of the light using RGB values.
         * @param r Red component of the ambient color.
         * @param g Green component of the ambient color.
         * @param b Blue component of the ambient color.
         */
        void setAmbient(GLfloat r, GLfloat g, GLfloat b);

        /**
         * @brief Sets the diffuse color of the light using RGB values.
         * @param r Red component of the diffuse color.
         * @param g Green component of the diffuse color.
         * @param b Blue component of the diffuse color.
         */
        void setDiffuse(GLfloat r, GLfloat g, GLfloat b);

        /**
         * @brief Sets the specular color of the light using RGB values.
         * @param r Red component of the specular color.
         * @param g Green component of the specular color.
         * @param b Blue component of the specular color.
         */
        void setSpecular(GLfloat r, GLfloat g, GLfloat b);

        /**
         * @brief Gets the ambient color of the light.
         * @return The current ambient color (r, g, b).
         */
        glm::vec3 getAmbient();

        /**
         * @brief Gets the diffuse color of the light.
         * @return The current diffuse color (r, g, b).
         */
        glm::vec3 getDiffuse();

        /**
         * @brief Gets the specular color of the light.
         * @return The current specular color (r, g, b).
         */
        glm::vec3 getSpecular();

        /**
         * @brief Updates the light properties in the shader.
         * @param shader The shader program to update.
         * @param index The index of the light in the shader.
         *
         * @note The maximum index of the light is constrained by MAX_LIGHTS constant.
         *       If you want to exceed this limit, you also need to update a define
         *       declaration in the basic fragment shader.
         */
        void update(Shader &shader, int index) override;
    };
}

#endif

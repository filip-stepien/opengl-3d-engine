#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace engine {
    /**
     * @class Shader
     * @brief OpenGL shader program.
     */
    class Shader {
    private:
        /// Type of shader.
        using ShaderType = enum SHADER_TYPE {
            VERTEX,
            FRAGMENT
        };

        /// Type of shader exception.
        using Exception = enum EXCEPTION {
            COMPILE,
            LINK
        };

        /// ID of the fragment shader.
        GLuint fragmentShader;

        /// ID of the vertex shader.
        GLuint vertexShader;

        /// ID of the shader program.
        GLuint id;

        /**
         * @brief Loads the shader source code from a file.
         * @param path The path to the shader file.
         * @return The shader source code as a string.
         */
        std::string loadShaderFromFile(std::string path);

        /**
         * @brief Creates a shader of the given type.
         * @param path The path to the shader file.
         * @param type The type of the shader.
         * @return The ID of the created shader.
         */
        GLuint createShader(std::string path, ShaderType type);

        /**
         * @brief Creates the shader program by linking vertex and fragment shaders.
         * @return The ID of the created shader program.
         */
        GLuint createProgram();

        /**
         * @brief Checks for shader compilation or linking errors.
         * @param program The shader or program ID to check.
         * @param exceptionType The type of exception to check for.
         */
        void checkForException(GLuint program, Exception exceptionType);

    public:
        /**
         * @brief Constructor for Shader.
         * @param fragmentPath The path to the fragment shader file.
         * @param vertexPath The path to the vertex shader file.
         *
         * Creates shader program.
         */
        Shader(
                std::string fragmentPath = "../resources/shaders/basic_fragment.glsl",
                std::string vertexPath = "../resources/shaders/basic_vertex.glsl"
        );

        /**
         * @brief Uses the shader program.
         */
        void use();

        /**
         * @brief Sets a boolean uniform in the shader.
         * @param name The name of the uniform.
         * @param value The boolean value to set.
         */
        void setBool(std::string name, bool value);

        /**
         * @brief Sets an integer uniform in the shader.
         * @param name The name of the uniform.
         * @param value The integer value to set.
         */
        void setInt(std::string name, int value);

        /**
         * @brief Sets an unsigned integer uniform in the shader.
         * @param name The name of the uniform.
         * @param value The unsigned integer value to set.
         */
        void setUInt(std::string name, unsigned int value);

        /**
         * @brief Sets a float uniform in the shader.
         * @param name The name of the uniform.
         * @param value The float value to set.
         */
        void setFloat(std::string name, float value);

        /**
         * @brief Sets a 2D vector uniform in the shader.
         * @param name The name of the uniform.
         * @param value The 2D vector value to set.
         */
        void setVec2(std::string name, const glm::vec2 &value);

        /**
         * @brief Sets a 2D vector uniform in the shader.
         * @param name The name of the uniform.
         * @param x The x component of the vector.
         * @param y The y component of the vector.
         */
        void setVec2(std::string name, float x, float y);

        /**
         * @brief Sets a 3D vector uniform in the shader.
         * @param name The name of the uniform.
         * @param value The vector value to set.
         */
        void setVec3(std::string name, const glm::vec3 &value);

        /**
         * @brief Sets a 3D vector uniform in the shader.
         * @param name The name of the uniform.
         * @param x The x component of the vector.
         * @param y The y component of the vector.
         * @param z The z component of the vector.
         */
        void setVec3(std::string name, float x, float y, float z);

        /**
         * @brief Sets a 4D vector uniform in the shader.
         * @param name The name of the uniform.
         * @param value The 4D vector to set.
         */
        void setVec4(std::string name, const glm::vec4 &value);

        /**
         * @brief Sets a 4D vector uniform in the shader.
         * @param name The name of the uniform.
         * @param x The x component of the vector.
         * @param y The y component of the vector.
         * @param z The z component of the vector.
         * @param w The w component of the vector.
         */
        void setVec4(std::string name, float x, float y, float z, float w);

        /**
         * @brief Sets a 2D matrix uniform in the shader.
         * @param name The name of the uniform.
         * @param mat The 2D matrix to set.
         */
        void setMat2(std::string name, const glm::mat2 &mat);

        /**
         * @brief Sets a 3D matrix uniform in the shader.
         * @param name The name of the uniform.
         * @param mat The 3D matrix to set.
         */
        void setMat3(std::string name, const glm::mat3 &mat);

        /**
         * @brief Sets a 4D matrix uniform in the shader.
         * @param name The name of the uniform.
         * @param mat The 4D matrix to set.
         */
        void setMat4(std::string name, const glm::mat4 &mat);
    };
}

#endif

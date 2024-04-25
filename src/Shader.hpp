#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
private:
    using ShaderType = enum SHADER_TYPE { VERTEX, FRAGMENT };
    using Exception = enum EXCEPTION { COMPILE, LINK };
    GLuint fragmentShader;
    GLuint vertexShader;
    GLuint id;

    std::string loadShaderFromFile(std::string path);
    GLuint createShader(std::string path, ShaderType type);
    GLuint createProgram();
    void checkForException(GLuint program, Exception exceptionType);

public:
    Shader(
        std::string fragmentPath = "C:/Users/user/Desktop/opengl-3d-engine/resources/shaders/basic_fragment.glsl",
        std::string vertexPath = "C:/Users/user/Desktop/opengl-3d-engine/resources/shaders/basic_vertex.glsl"
    );

    void use();
    void setBool(std::string name, bool value);
    void setInt(std::string name, int value);
    void setUInt(std::string name, unsigned int value);
    void setFloat(std::string name, float value);
    void setVec2(std::string name, const glm::vec2& value);
    void setVec2(std::string name, float x, float y);
    void setVec3(std::string name, const glm::vec3& value);
    void setVec3(std::string name, float x, float y, float z);
    void setVec4(std::string name, const glm::vec4& value);
    void setVec4(std::string name, float x, float y, float z, float w);
    void setMat2(std::string name, const glm::mat2& mat);
    void setMat3(std::string name, const glm::mat3& mat);
    void setMat4(std::string name, const glm::mat4& mat);
};

#endif
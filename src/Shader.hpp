#pragma once

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

    std::string loadShaderFromFile(const char* path);
    GLuint createShader(const char* path, ShaderType type);
    GLuint createProgram();
    void checkForException(GLuint program, Exception exceptionType);

public:
    Shader(const char* vertexPath, const char* fragmentPath);

    void use();
    void setBool(const char* name, bool value);
    void setInt(const char* name, int value);
    void setFloat(const char* name, float value);
    void setVec2(const char* name, const glm::vec2& value);
    void setVec2(const char* name, float x, float y);
    void setVec3(const char* name, const glm::vec3& value);
    void setVec3(const char* name, float x, float y, float z);
    void setVec4(const char* name, const glm::vec4& value);
    void setVec4(const char* name, float x, float y, float z, float w);
    void setMat2(const char* name, const glm::mat2& mat);
    void setMat3(const char* name, const glm::mat3& mat);
    void setMat4(const char* name, const glm::mat4& mat);
};
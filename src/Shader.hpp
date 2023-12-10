#pragma once

#include <glad/glad.h>
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
};
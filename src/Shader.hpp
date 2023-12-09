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
    unsigned int fragmentShader;
    unsigned int vertexShader;
    unsigned int programId;

    const char* loadShaderFromFile(const char* path);
    unsigned int createShader(const char* path, ShaderType type);
    unsigned int createProgram();
    void checkForException(unsigned int program, Exception exceptionType);

public:
    Shader(const char* vertexPath, const char* fragmentPath);

    void use();
    void setBool(const char* name, bool value);
    void setInt(const char* name, int value);
    void setFloat(const char* name, float value);
};
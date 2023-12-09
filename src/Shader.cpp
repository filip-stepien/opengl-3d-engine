#include "Shader.hpp"

const char* Shader::loadShaderFromFile(const char* path) {
    std::string shaderCode;
    std::ifstream shaderFile;
    std::stringstream fileStream;
    
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(path);
        fileStream << shaderFile.rdbuf();
        shaderCode = fileStream.str();
        shaderFile.close();
    } catch (std::ifstream::failure e) {
        std::cout << "Unable to read a file: " << path << std::endl;
        return nullptr;
    }

    return shaderCode.c_str();
}

unsigned int Shader::createShader(const char* path, ShaderType type) {
    unsigned int shader;

    const char* code = loadShaderFromFile(path);

    if (code == nullptr) return false;
    
    if(type == VERTEX) {
        shader = glCreateShader(GL_VERTEX_SHADER);
    } else {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    }

    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    checkForException(shader, COMPILE);

    return shader;
}

unsigned int Shader::createProgram() {
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    checkForException(program, LINK);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void Shader::checkForException(unsigned int program, Exception exceptionType) {
    int success;
    std::string type;
    char infoLog[1024];
    
    if (exceptionType == COMPILE) {
        type = "COMPILE";
        glGetShaderiv(program, GL_COMPILE_STATUS, &success);
    } else {
        type = "LINK";
        glGetProgramiv(program, GL_LINK_STATUS, &success);
    }
    
    if (!success) {
        glGetShaderInfoLog(program, 1024, NULL, infoLog);
        std::cout << "SHADER " << type << " ERROR " << std::endl << infoLog << std::endl;
    }
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    vertexShader = createShader(vertexPath, VERTEX);
    fragmentShader = createShader(fragmentPath, FRAGMENT);
    programId = createProgram();
}

void Shader::use() {
    glUseProgram(programId);
}

void Shader::setBool(const char* name, bool value) {
    glUniform1i(glGetUniformLocation(programId, name), (int)value);
}

void Shader::setInt(const char* name, int value) {
    glUniform1i(glGetUniformLocation(programId, name), value);
}

void Shader::setFloat(const char* name, float value) {
    glUniform1f(glGetUniformLocation(programId, name), value);
}
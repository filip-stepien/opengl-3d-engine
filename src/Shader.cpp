#include "Shader.hpp"

std::string engine::Shader::loadShaderFromFile(std::string path) {
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

    return shaderCode;
}

unsigned int engine::Shader::createShader(std::string path, ShaderType type) {
    GLuint shader;

    std::string file = loadShaderFromFile(path);
    const char* code = file.c_str();

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

GLuint engine::Shader::createProgram() {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    checkForException(program, LINK);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void engine::Shader::checkForException(GLuint program, Exception exceptionType) {
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

engine::Shader::Shader(std::string fragmentPath, std::string vertexPath) {
    vertexShader = createShader(vertexPath, VERTEX);
    fragmentShader = createShader(fragmentPath, FRAGMENT);
    id = createProgram();
}

void engine::Shader::use() {
    glUseProgram(id);
}

void engine::Shader::setBool(std::string name, bool value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void engine::Shader::setInt(std::string name, int value) {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void engine::Shader::setUInt(std::string name, unsigned int value) {
    glUniform1ui(glGetUniformLocation(id, name.c_str()), value);
}

void engine::Shader::setFloat(std::string name, float value) {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void engine::Shader::setVec2(std::string name, const glm::vec2& value) {
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}

void engine::Shader::setVec2(std::string name, float x, float y) {
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}

void engine::Shader::setVec3(std::string name, const glm::vec3& value) {
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void engine::Shader::setVec3(std::string name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

void engine::Shader::setVec4(std::string name, const glm::vec4& value) {
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void engine::Shader::setVec4(std::string name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}

void engine::Shader::setMat2(std::string name, const glm::mat2& mat) {
    glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void engine::Shader::setMat3(std::string name, const glm::mat3& mat) {
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void engine::Shader::setMat4(std::string name, const glm::mat4& mat) {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
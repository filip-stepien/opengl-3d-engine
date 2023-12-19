#include "Shader.hpp"

std::string Shader::loadShaderFromFile(const char* path) {
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

unsigned int Shader::createShader(const char* path, ShaderType type) {
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

GLuint Shader::createProgram() {
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    checkForException(program, LINK);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void Shader::checkForException(GLuint program, Exception exceptionType) {
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
    id = createProgram();
}

void Shader::use() {
    glUseProgram(id);
}

void Shader::setBool(const char* name, bool value) {
    glUniform1i(glGetUniformLocation(id, name), (int)value);
}

void Shader::setInt(const char* name, int value) {
    glUniform1i(glGetUniformLocation(id, name), value);
}

void Shader::setFloat(const char* name, float value) {
    glUniform1f(glGetUniformLocation(id, name), value);
}

void Shader::setVec2(const char* name, const glm::vec2& value) {
    glUniform2fv(glGetUniformLocation(id, name), 1, &value[0]);
}

void Shader::setVec2(const char* name, float x, float y) {
    glUniform2f(glGetUniformLocation(id, name), x, y);
}

void Shader::setVec3(const char* name, const glm::vec3& value) {
    glUniform3fv(glGetUniformLocation(id, name), 1, &value[0]);
}
void Shader::setVec3(const char* name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(id, name), x, y, z);
}

void Shader::setVec4(const char* name, const glm::vec4& value) {
    glUniform4fv(glGetUniformLocation(id, name), 1, &value[0]);
}
void Shader::setVec4(const char* name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(id, name), x, y, z, w);
}

void Shader::setMat2(const char* name, const glm::mat2& mat) {
    glUniformMatrix2fv(glGetUniformLocation(id, name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const char* name, const glm::mat3& mat) {
    glUniformMatrix3fv(glGetUniformLocation(id, name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const char* name, const glm::mat4& mat) {
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, &mat[0][0]);
}
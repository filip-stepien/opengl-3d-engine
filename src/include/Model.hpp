#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>

#include "Model.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

class Model {
private:
    std::vector<Mesh*> meshes;

public:
    ~Model();

    void load(const std::string& path);
    std::vector<Mesh*> getMeshes();

    void setDiffuseTexture(const char* path);
    void setSpecularTexture(const char* path);
    void setShininess(GLfloat shininess);
    void setTextureScale(float scaleX, float scaleY);
    void setIgnoreLight(bool ignore);
    void setViewIndependent(bool independent);

    void setPosition(glm::vec3 position);
    void setPosition(GLfloat x, GLfloat y, GLfloat z);
    void move(GLfloat x, GLfloat y, GLfloat z);
    void move(glm::vec3 translation);
    void setRotation(GLfloat angleDegrees, GLfloat x, GLfloat y, GLfloat z);
    void setRotation(GLfloat angleDegrees, glm::vec3 origin);
    void rotate(GLfloat angleDegrees, GLfloat x, GLfloat y, GLfloat z);
    void rotate(GLfloat angleDegrees, glm::vec3 origin);
    void setScale(GLfloat x, GLfloat y, GLfloat z);
    void setScale(glm::vec3 scale);
    void scale(GLfloat x, GLfloat y, GLfloat z);
    void scale(glm::vec3 scale);
};

#endif

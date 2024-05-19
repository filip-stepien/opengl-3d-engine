#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "EngineObject.hpp"

class Transformable : public EngineObject {
protected:
	glm::mat4 model { 1.0f };
    glm::vec3 position { 0.0f };
    glm::vec3 rotationFactor { 0.0f };
    glm::vec3 scaleFactor { 1.0f };

    glm::mat4 positionMatrix { 1.0f };
    glm::mat4 rotationMatrix { 1.0f };
    glm::mat4 scaleMatrix { 1.0f };

private:
    void transform();

public:
    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getScale();

    void setModelMatrix(glm::mat4 model);
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
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
public:
    glm::vec3 getPosition();
    virtual void setPosition(glm::vec3 position);
    virtual void setPosition(GLfloat x, GLfloat y, GLfloat z);
    virtual void move(GLfloat x, GLfloat y, GLfloat z);
    virtual void move(glm::vec3 translation);
    virtual void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
    virtual void rotate(GLfloat angle, glm::vec3 origin);
    virtual void scale(GLfloat x, GLfloat y, GLfloat z);
    virtual void scale(glm::vec3 scale);
};

#endif
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transformable {
protected:
	glm::mat4 model;

public:
	Transformable();

	virtual void translate(GLfloat x, GLfloat y, GLfloat z);
	virtual void translate(glm::vec3 translation);
	virtual void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	virtual void rotate(GLfloat angle, glm::vec3 origin);
	virtual void scale(GLfloat x, GLfloat y, GLfloat z);
	virtual void scale(glm::vec3 scale);
};
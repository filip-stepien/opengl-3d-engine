#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Transformable.hpp"

class Movable : virtual public Transformable {
protected:
	glm::vec3 position;
public:
	Movable();
	glm::vec3 getPosition();
	virtual void move(GLfloat x, GLfloat y, GLfloat z);
	virtual void move(glm::vec3 translation);
};
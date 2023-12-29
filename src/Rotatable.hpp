#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Transformable.hpp"

class Rotatable : virtual public Transformable {
public:
	virtual void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	virtual void rotate(GLfloat angle, glm::vec3 origin);
};
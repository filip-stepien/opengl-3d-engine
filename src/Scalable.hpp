#ifndef SCALABLE_H
#define SCALABLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Transformable.hpp"

class Scalable : virtual public Transformable {
public:
	virtual void scale(GLfloat x, GLfloat y, GLfloat z);
	virtual void scale(glm::vec3 scale);
};

#endif
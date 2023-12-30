#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Movable.hpp"

class Light : public Movable {
private:
	glm::vec3 color;
	GLfloat ambientStrength;
	GLfloat specularStrength;

public:
	Light();
	void setColor(glm::vec3 color);
	void setColor(GLfloat r, GLfloat g, GLfloat b);
	void setAmbientStrength(GLfloat strength);
	void setSpecularStength(GLfloat strength);

	glm::vec3 getColor();
	GLfloat getAmbientStrength();
	GLfloat getSpecularStength();
};
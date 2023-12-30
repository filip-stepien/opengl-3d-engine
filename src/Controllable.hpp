#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Movable.hpp"

class Controllable : public Movable {
public:
	using Direction = enum DIRECTION { FORWARD, BACKWARD, LEFT, RIGHT };
	
private:
	GLfloat yaw;
	GLfloat pitch;
	GLfloat speed;
	GLfloat sensitivity;
	GLfloat zoom;

	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	void updateVectors();

public:
	Controllable();

	void setYaw(GLfloat yaw);
	void setPitch(GLfloat pitch);
	void setSpeed(GLfloat speed);
	void setSensitivity(GLfloat sensitivity);
	void setZoom(GLfloat zoom);

	GLfloat getYaw();
	GLfloat getPitch();
	GLfloat getSpeed();
	GLfloat getSensitivity();
	GLfloat getZoom();

	void processKeyboard(Direction direction);
};
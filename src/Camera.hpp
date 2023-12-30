#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.hpp"
#include "Movable.hpp"
#include "Updatable.hpp"

class Camera : public Updatable, public Movable {
public:
	using Projection = enum PROJECTION { PERSPECTIVE, ORTHO };

private:
	Projection projection;
	GLfloat near;
	GLfloat far;
	GLfloat fov;

	bool firstMouse;
	GLfloat lastX;
	GLfloat lastY;

	bool movementEnabled;
	GLfloat yaw;
	GLfloat pitch;
	GLfloat speed;
	GLfloat sensitivity;
	GLfloat zoom;

	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	void updateVectors();
	void processMovement();

public:
	using Direction = enum DIRECTION { FORWARD, BACKWARD, LEFT, RIGHT };

	Camera();
	void setProjection(Projection projection, GLfloat near, GLfloat far, GLfloat fovDegrees = 45.0f);
	void update(Shader& shader);

	void setYaw(GLfloat yaw);
	void setPitch(GLfloat pitch);
	void setSpeed(GLfloat speed);
	void setSensitivity(GLfloat sensitivity);
	void setZoom(GLfloat zoom);
	void setMovementEnabled(bool enabled);

	GLfloat getYaw();
	GLfloat getPitch();
	GLfloat getSpeed();
	GLfloat getSensitivity();
	GLfloat getZoom();
	bool isMovementEnabled();

	void processKeyboard(Direction direction);
	void processMouse(GLfloat offsetX, GLfloat offsetY);
	void handleMouseMove(double posX, double posY);
	void updateProjection();
};
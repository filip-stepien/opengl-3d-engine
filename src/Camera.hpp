#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.hpp"
#include "Movable.hpp"
#include "Updatable.hpp"

class Camera : public Updatable, public Movable {
private:
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
	glm::vec3 looksAt;

	void updateVectors();

public:
	using Projection = enum PROJECTION { PERSPECTIVE, ORTHO };
	using Direction = enum DIRECTION { FORWARD, BACKWARD, LEFT, RIGHT };

	Camera();
	void lookAt(glm::vec3 position);
	void lookAt(float posX, float posY, float posZ);
	void setProjection(Projection projection, float near, float far, float fovDegrees = 45.0f);
	void update(Shader& shader);

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
	void processMouse(GLfloat offsetX, GLfloat offsetY);
};
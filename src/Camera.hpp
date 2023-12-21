#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.hpp"
#include "Engine.hpp"

class Camera {
private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::vec3 position;
	glm::vec3 looksAt;
	Shader* viewShader;

public:
	using Projection = enum PROJECTION { PERSPECTIVE, ORTHO };

	Camera(Shader* viewShader);
	Camera(glm::vec3 position, Shader* viewShader);
	Camera(float posX, float posY, float posZ, Shader* viewShader);

	void setPosition(glm::vec3 position);
	void setPosition(float posX, float posY, float posZ);

	void lookAt(glm::vec3 position);
	void lookAt(float posX, float posY, float posZ);
	void setProjection(Projection projection, float near, float far, float fovDegrees = 45.0f);
	void update();
};
#include "Camera.hpp"

Camera::Camera() {
	this->viewMatrix = glm::mat4(1.0f);
	this->looksAt = glm::vec3(0.0f);
	this->projectionMatrix = glm::perspective(45.0f, Engine::get().getAspectRatio(), 0.1f, 100.0f);
}

void Camera::setProjection(Projection projection, float near, float far, float fovDegrees) {
	if (projection == PERSPECTIVE) {
		projectionMatrix = glm::perspective(
			glm::radians(fovDegrees), 
			Engine::get().getAspectRatio(), 
			near, 
			far
		);
	} else {
		projectionMatrix = glm::ortho(
			-Engine::get().getAspectRatio(),
			Engine::get().getAspectRatio(),
			-1.0f,
			1.0f,
			near,
			far
		);
	}
}

void Camera::lookAt(glm::vec3 position) {
	looksAt = position;
}

void Camera::lookAt(float posX, float posY, float posZ) {
	looksAt = glm::vec3(posX, posY, posZ);
}

void Camera::update(Shader& shader) {
	viewMatrix = glm::lookAt(position, looksAt, glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("projection", projectionMatrix);
	shader.setMat4("view", viewMatrix);
	shader.setVec3("viewPos", position);
}
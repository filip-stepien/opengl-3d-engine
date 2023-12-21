#include "Camera.hpp"

Camera::Camera(Shader* viewShader) {
	this->viewMatrix = glm::mat4(1.0f);
	this->looksAt = glm::vec3(0.0f);
	this->position = glm::vec3(0.0f);
	this->viewShader = viewShader;
	this->projectionMatrix = glm::perspective(45.0f, Engine::get().getAspectRatio(), 0.1f, 100.0f);
	viewShader->setMat4("projection", projectionMatrix);
}

Camera::Camera(glm::vec3 position, Shader* viewShader) {
	this->viewMatrix = glm::mat4(1.0f);
	this->looksAt = glm::vec3(0.0f);
	this->position = position;
	this->viewShader = viewShader;
	this->projectionMatrix = glm::perspective(45.0f, Engine::get().getAspectRatio(), 0.1f, 100.0f);
	viewShader->setMat4("projection", projectionMatrix);
}

Camera::Camera(float posX, float posY, float posZ, Shader* viewShader) {
	this->viewMatrix = glm::mat4(1.0f);
	this->looksAt = glm::vec3(0.0f);
	this->position = glm::vec3(posX, posY, posZ);
	this->viewShader = viewShader;
	this->projectionMatrix = glm::perspective(45.0f, Engine::get().getAspectRatio(), 0.1f, 100.0f);
	viewShader->setMat4("projection", projectionMatrix);
}

void Camera::setPosition(glm::vec3 position) {
	this->position = position;
}

void Camera::setPosition(float posX, float posY, float posZ) {
	this->position = glm::vec3(posX, posY, posZ);
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

	viewShader->setMat4("projection", projectionMatrix);
}

void Camera::lookAt(glm::vec3 position) {
	looksAt = position;
}

void Camera::lookAt(float posX, float posY, float posZ) {
	looksAt = glm::vec3(posX, posY, posZ);
}

void Camera::update() {
	viewMatrix = glm::lookAt(position, looksAt, glm::vec3(0.0f, 1.0f, 0.0f));
	viewShader->setMat4("view", viewMatrix);
}
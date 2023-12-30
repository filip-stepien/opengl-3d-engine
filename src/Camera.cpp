#include "Camera.hpp"
#include "Engine.hpp"

Camera::Camera() {
	viewMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::perspective(45.0f, Engine::get().getAspectRatio(), 0.1f, 100.0f);

	near = 0.1f;
	far = 100.0f;
	fov = 45.0f;

	firstMouse = true;
	lastX = 0.0f;
	lastY = 0.0f;

	movementEnabled = true;
	yaw = -90.0f;
	pitch = 0.0f;
	speed = 2.5f;
	sensitivity = 0.1f;
	zoom = 45.0f;

	front = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	initialFocus = glm::vec3(0.0f, 0.0f, 0.0f);

	updateVectors();
}

void Camera::setProjection(Projection projection, GLfloat near, GLfloat far, GLfloat fovDegrees) {
	this->projection = projection;
	this->near = near;
	this->far = far;
	this->fov = fovDegrees;

	updateProjection();
}

void Camera::updateProjection() {
	if (projection == PERSPECTIVE) {
		projectionMatrix = glm::perspective(
			glm::radians(fov),
			Engine::get().getAspectRatio(),
			near,
			far
		);
	}
	else {
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

void Camera::setYaw(GLfloat yaw) {
	this->yaw = yaw;
	updateVectors();
}

void Camera::setPitch(GLfloat pitch) {
	this->pitch = pitch;
	updateVectors();
}

void Camera::setSpeed(GLfloat speed) {
	this->speed = speed;
}

void Camera::setSensitivity(GLfloat sensitivity) {
	this->sensitivity = sensitivity;
}

void Camera::setZoom(GLfloat zoom) {
	this->zoom = zoom;
}

void Camera::setMovementEnabled(bool movementEnabled) {
	this->movementEnabled = movementEnabled;
}

void Camera::setInitialFocus(glm::vec3 initalFocus) {
	this->initialFocus = initalFocus;
	updateFocus();
}

void Camera::setInitialFocus(GLfloat x, GLfloat y, GLfloat z) {
	this->initialFocus = glm::vec3(x, y, z);
	updateFocus();
}

GLfloat Camera::getYaw() {
	return yaw;
}

GLfloat Camera::getPitch() {
	return pitch;
}

GLfloat Camera::getSpeed() {
	return speed;
}

GLfloat Camera::getSensitivity() {
	return sensitivity;
}

GLfloat Camera::getZoom() {
	return zoom;
}

glm::vec3 Camera::getInitalFocus() {
	return initialFocus;
}

bool Camera::isMovementEnabled() {
	return movementEnabled;
}

void Camera::processKeyboard(Direction direction) {
	float velocity = speed * Engine::get().getDeltaTime();
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
}

void Camera::handleMouseMove(double posX, double posY) {
	GLfloat xpos = static_cast<GLfloat>(posX);
	GLfloat ypos = static_cast<GLfloat>(posY);

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	processMouse(xoffset, yoffset);
}

void Camera::processMouse(GLfloat offsetX, GLfloat offsetY) {
	offsetX *= sensitivity;
	offsetY *= sensitivity;

	yaw += offsetX;
	pitch += offsetY;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	updateVectors();
}

void Camera::updateVectors() {
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::updateFocus() {
	glm::vec3 direction = glm::normalize(initialFocus - position);
	float yaw = glm::degrees(atan2(direction.z, direction.x));
	float pitch = glm::degrees(asin(direction.y));
	setYaw(yaw);
	setPitch(pitch);
}

void Camera::processMovement() {
	GLFWwindow* window = Engine::get().getWindow();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		processKeyboard(Camera::FORWARD);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		processKeyboard(Camera::BACKWARD);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		processKeyboard(Camera::LEFT);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		processKeyboard(Camera::RIGHT);
}

void Camera::update(Shader& shader) {
	viewMatrix = glm::lookAt(position, position + front, glm::vec3(0.0f, 1.0f, 0.0f));
	
	shader.setMat4("projection", projectionMatrix);
	shader.setMat4("view", viewMatrix);
	shader.setVec3("viewPos", position);

	if(movementEnabled)
		processMovement();
}

void Camera::move(GLfloat x, GLfloat y, GLfloat z) {
	Movable::move(x, y, z);
	updateFocus();
}

void Camera::move(glm::vec3 translation) {
	Movable::move(translation);
	updateFocus();
}
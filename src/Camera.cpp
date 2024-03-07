#include "Camera.hpp"
#include "Engine.hpp"

void Camera::setProjection(Projection projection, GLfloat near, GLfloat far, GLfloat fovDegrees) {
	this->projection = projection;
	this->near = near;
	this->far = far;
	this->fov = fovDegrees;
}

void Camera::updateProjection() {
    float apsect = Engine::get().getAspectRatio();

	if (projection == PERSPECTIVE) {
		projectionMatrix = glm::perspective(
			glm::radians(fov),
            apsect,
			near,
			far
		);
	} else {
		projectionMatrix = glm::ortho(
			-apsect,
            apsect,
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
}

void Camera::setInitialFocus(GLfloat x, GLfloat y, GLfloat z) {
	this->initialFocus = glm::vec3(x, y, z);
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
    double dt = Engine::get().getDeltaTime();
	float velocity = static_cast<float>(speed * dt);

	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
}

void Camera::handleMouseMove(double mouseX, double mouseY) {
	GLfloat x = static_cast<GLfloat>(mouseX);
	GLfloat y = static_cast<GLfloat>(mouseY);

	if (firstMouse) {
		lastX = x;
		lastY = y;
		firstMouse = false;
	}

	GLfloat offsetX = x - lastX;
	GLfloat offsetY = lastY - y;

	lastX = x;
	lastY = y;

	processMouse(offsetX, offsetY);
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

void Camera::updateFocus() {
    glm::vec3 diff = initialFocus - position;

    if (glm::length(diff) <= 0.0)
        return;

    glm::vec3 direction = glm::normalize(diff);
    double newYaw = glm::degrees(atan2(direction.z, direction.x));
    double newPitch = glm::degrees(asin(direction.y));

    yaw = static_cast<float>(newYaw);
    pitch = static_cast<float>(newPitch);

    updateVectors();
}

void Camera::updateVectors() {
    float yawRad = glm::radians(yaw);
    float pitchRad = glm::radians(pitch);

	front.x = std::cos(yawRad) * std::cos(pitchRad);
	front.y = std::sin(pitchRad);
	front.z = std::sin(yawRad) * std::cos(pitchRad);

	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, up));
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
    if (movementEnabled)
        processMovement();

	viewMatrix = glm::lookAt(position, position + front, up);
	
	shader.setMat4("projection", projectionMatrix);
	shader.setMat4("view", viewMatrix);
	shader.setVec3("viewPos", position);
}

void Camera::initialize() {
    updateProjection();
    updateFocus();
}

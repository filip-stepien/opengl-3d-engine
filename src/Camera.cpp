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
    resetMousePosition();
}

void Camera::setInitialFocus(glm::vec3 initalFocus) {
	this->initialFocus = initalFocus;
}

void Camera::setInitialFocus(GLfloat x, GLfloat y, GLfloat z) {
	this->initialFocus = glm::vec3(x, y, z);
}

void Camera::setYAxisLocked(bool locked) {
    this->yAxisLocked = locked;
}

void Camera::setRestrictMovementBox(GLfloat sizeX, GLfloat sizeY, GLfloat sizeZ) {
    this->restrictX = sizeX;
    this->restrictY = sizeY;
    this->restrictZ = sizeZ;
}

void Camera::setCursorPosition(GLfloat x, GLfloat y) {
    mouseX = x;
    mouseY = y;
}

void Camera::disperseInitialFocus() {
    firstMouse = false;
    resetMousePosition();
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

glm::mat4 Camera::getProjectionMatrix() {
    return projectionMatrix;
}

glm::mat4 Camera::getViewMatrix() {
    return viewMatrix;
}

glm::vec3 Camera::getInitalFocus() {
	return initialFocus;
}

glm::vec3 Camera::getRaycast() {
    return front;
}

bool Camera::isMovementEnabled() {
	return movementEnabled;
}

void Camera::resetMousePosition() {
    double x, y;
    glfwGetCursorPos(Engine::get().getWindow(), &x, &y);

    lastX = static_cast<GLfloat>(x);
    lastY = static_cast<GLfloat>(y);
}

void Camera::restrictMovement() {
    GLfloat margin = std::nextafter(0.0f, 1.0f);

    position.x = std::clamp(position.x, -restrictX + margin, restrictX - margin);
    position.y = std::clamp(position.y, -restrictY + margin, restrictY - margin);
    position.z = std::clamp(position.z, -restrictZ + margin, restrictZ - margin);
}

void Camera::processKeyboard(Direction direction) {
    double dt = Engine::get().getDeltaTime();
	float velocity = static_cast<float>(speed * dt);

    glm::vec3 frontBackMove = yAxisLocked ? front * glm::vec3(velocity, 0.0f, velocity) : front * velocity;
    glm::vec3 leftRightMove = yAxisLocked ? right * glm::vec3(velocity, 0.0f, velocity) : right * velocity;

	if (direction == FORWARD)
		position += frontBackMove;
	if (direction == BACKWARD)
		position -= frontBackMove;
	if (direction == LEFT)
		position -= leftRightMove;
	if (direction == RIGHT)
		position += leftRightMove;

    restrictMovement();
}

void Camera::handleMouseMove(double mX, double mY) {
	mouseX = static_cast<GLfloat>(mX);
	mouseY = static_cast<GLfloat>(mY);

	if (firstMouse) {
		lastX = mouseX;
		lastY = mouseY;
		firstMouse = false;
	}

	GLfloat offsetX = mouseX - lastX;
	GLfloat offsetY = lastY - mouseY;

	lastX = mouseX;
	lastY = mouseY;

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

	viewMatrix = glm::lookAt(position, firstMouse ? initialFocus : position + front, up);

    shader.use();
	shader.setMat4("projection", projectionMatrix);
	shader.setMat4("view", viewMatrix);
	shader.setVec3("viewPos", position);
    shader.setVec3("viewFront", front);
}

void Camera::initialize() {
    updateProjection();
    updateFocus();
}

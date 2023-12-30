#include "Controllable.hpp"
#include "Engine.hpp"

Controllable::Controllable() {
	yaw = -90.0f;
	pitch = 0.0f;
	speed = 2.5f;
	sensitivity = 0.1f;
	zoom = 45.0f;

    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);

    updateVectors();
}

void Controllable::setYaw(GLfloat yaw) {
    this->yaw = yaw;
}

void Controllable::setPitch(GLfloat pitch) {
    this->pitch = pitch;
}

void Controllable::setSpeed(GLfloat speed) {
    this->speed = speed;
}

void Controllable::setSensitivity(GLfloat sensitivity) {
    this->sensitivity = sensitivity;
}

void Controllable::setZoom(GLfloat zoom) {
    this->zoom = zoom;
}

GLfloat Controllable::getYaw() {
    return yaw;
}

GLfloat Controllable::getPitch() {
    return pitch;
}

GLfloat Controllable::getSpeed() {
    return speed;
}

GLfloat Controllable::getSensitivity() {
    return sensitivity;
}

GLfloat Controllable::getZoom() {
    return zoom;
}

void Controllable::processKeyboard(Direction direction) {
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

void Controllable::updateVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));
}
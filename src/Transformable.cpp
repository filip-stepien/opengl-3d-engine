#include "Transformable.hpp"

glm::vec3 Transformable::getPosition() {
    return position;
}

glm::vec3 Transformable::getRotation() {
    return rotationFactor;
}

glm::vec3 Transformable::getScale() {
    return scaleFactor;
}

void Transformable::setPosition(glm::vec3 position) {
    positionMatrix = glm::translate({ 1.0f }, position);
    this->position = position;
    transform();
}

void Transformable::setPosition(GLfloat x, GLfloat y, GLfloat z) {
    positionMatrix = glm::translate({ 1.0f }, glm::vec3(x, y, z));
    this->position = glm::vec3(x, y, z);
    transform();
}

void Transformable::move(GLfloat x, GLfloat y, GLfloat z) {
    model = glm::translate(model, glm::vec3(x, y, z));
    position += glm::vec3(x, y, z);
}

void Transformable::move(glm::vec3 translation) {
    model = glm::translate(model, translation);
    position += translation;
}

void Transformable::setRotation(GLfloat angleDegrees, GLfloat x, GLfloat y, GLfloat z) {
    rotationFactor = { angleDegrees * x, angleDegrees * y, angleDegrees * z };
    rotationMatrix = glm::rotate({ 1.0f }, glm::radians(angleDegrees), glm::vec3(x, y, z));
    transform();
}

void Transformable::setRotation(GLfloat angleDegrees, glm::vec3 origin) {
    rotationFactor = { angleDegrees * origin };
    rotationMatrix = glm::rotate({ 1.0f }, glm::radians(angleDegrees), origin);
    transform();
}

void Transformable::rotate(GLfloat angleDegrees, GLfloat x, GLfloat y, GLfloat z) {
    model = glm::rotate(model, glm::radians(angleDegrees), glm::vec3(x, y, z));
}

void Transformable::rotate(GLfloat angleDegrees, glm::vec3 origin) {
    model = glm::rotate(model, glm::radians(angleDegrees), origin);
}

void Transformable::setScale(GLfloat x, GLfloat y, GLfloat z) {
    scaleFactor = { scaleFactor.x + x, scaleFactor.y + y, scaleFactor.z + z };
    scaleMatrix = glm::scale({ 1.0f }, glm::vec3(x, y, z));
    transform();
}

void Transformable::setScale(glm::vec3 scale) {
    scaleFactor *= scale;
    scaleMatrix = glm::scale({ 1.0f }, scale);
    transform();
}

void Transformable::scale(GLfloat x, GLfloat y, GLfloat z) {
    model = glm::scale(model, glm::vec3(x, y, z));
}

void Transformable::scale(glm::vec3 scale) {
    model = glm::scale({ 1.0f }, scale);
}

void Transformable::setModelMatrix(glm::mat4 model) {
    this->model = model;
}

void Transformable::transform() {
    model = positionMatrix * scaleMatrix * rotationMatrix;
}
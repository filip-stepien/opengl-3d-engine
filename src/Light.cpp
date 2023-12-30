#include "Light.hpp"

Light::Light() {
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientStrength = 0.1f;
	specularStrength = 0.5f;
}

void Light::setColor(glm::vec3 color) {
	this->color = color;
}

void Light::setColor(GLfloat r, GLfloat g, GLfloat b) {
	this->color = glm::vec3(r, g, b);
}

void Light::setAmbientStrength(GLfloat ambientStrength) {
	this->ambientStrength = ambientStrength;
}

void Light::setSpecularStength(GLfloat specularStrength) {
	this->specularStrength = specularStrength;
}

glm::vec3 Light::getColor() {
	return color;
}

GLfloat Light::getAmbientStrength() {
	return ambientStrength;
}

GLfloat Light::getSpecularStength() {
	return specularStrength;
}
#include "Movable.hpp"

Movable::Movable() {
	position = glm::vec3(0.0f);
}

glm::vec3 Movable::getPosition() {
	return position;
}

void Movable::move(GLfloat x, GLfloat y, GLfloat z) {
	model = glm::translate(model, glm::vec3(x, y, z));
	position = glm::vec3(x, y, z);
}

void Movable::move(glm::vec3 translation) {
	model = glm::translate(model, translation);
	position = translation;
}
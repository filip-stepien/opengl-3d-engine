#include "Movable.hpp"

void Movable::move(GLfloat x, GLfloat y, GLfloat z) {
	model = glm::translate(model, glm::vec3(x, y, z));
}

void Movable::move(glm::vec3 translation) {
	model = glm::translate(model, translation);
}
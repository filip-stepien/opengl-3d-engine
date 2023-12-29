#include "Scalable.hpp"

void Scalable::scale(GLfloat x, GLfloat y, GLfloat z) {
	model = glm::scale(model, glm::vec3(x, y, z));
}

void Scalable::scale(glm::vec3 scale) {
	model = glm::scale(model, scale);
}
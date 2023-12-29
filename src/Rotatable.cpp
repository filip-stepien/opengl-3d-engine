#include "Rotatable.hpp"

void Rotatable::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
	model = glm::rotate(model, angle, glm::vec3(x, y, z));
}

void Rotatable::rotate(GLfloat angle, glm::vec3 origin) {
	model = glm::rotate(model, angle, origin);
}
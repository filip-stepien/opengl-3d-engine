#include "Transformable.hpp"

Transformable::Transformable() {
	model = glm::mat4(1.0f);
}

void Transformable::translate(GLfloat x, GLfloat y, GLfloat z) {
	model = glm::translate(model, glm::vec3(x, y, z));
}

void Transformable::translate(glm::vec3 translation) {
	model = glm::translate(model, translation);
}

void Transformable::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
	model = glm::rotate(model, angle, glm::vec3(x, y, z));
}

void Transformable::rotate(GLfloat angle, glm::vec3 origin) {
	model = glm::rotate(model, angle, origin);
}

void Transformable::scale(GLfloat x, GLfloat y, GLfloat z) {
	model = glm::scale(model, glm::vec3(x, y, z));
}

void Transformable::scale(glm::vec3 scale) {
	model = glm::scale(model, scale);
}
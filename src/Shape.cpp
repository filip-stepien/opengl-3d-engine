#include "Shape.hpp"

Shape::Shape() : Mesh(vertices, indices) {
	color = glm::vec3(1.0, 1.0, 1.0f);
}

void Shape::setColor(glm::vec3 color) {
    this->color = color;
}

void Shape::setColor(GLfloat r, GLfloat g, GLfloat b) {
    this->color = glm::vec3(r, g, b);
}

glm::vec3 Shape::getColor() {
    return color;
}
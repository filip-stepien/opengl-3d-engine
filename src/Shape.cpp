#include "Shape.hpp"

Shape::Shape(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, const char* texturePath) 
    : Mesh(vertices, indices, texturePath) 
{
	this->color = glm::vec3(1.0, 1.0, 1.0f);
    this->vertices = vertices;
    this->indices = indices;

    initialize();
}

void Shape::populateVertices() {
    vertices = std::vector<Vertex>();
}

void Shape::populateIndices() {
    indices = std::vector<GLuint>();
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
#include "Shape.hpp"

Shape::Shape(std::vector<Vertex>& vertices, std::vector<GLuint>& indices) 
    : Mesh(vertices, indices) 
{
	this->color = glm::vec3(1.0, 1.0, 1.0f);
    this->vertices = vertices;
    this->indices = indices;
}

void Shape::populateVertices() {
    vertices = std::vector<Vertex>();
}

void Shape::populateIndices() {
    indices = std::vector<GLuint>();
}
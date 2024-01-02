#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices) {
	this->vertices = vertices;
	this->indices = indices;
	this->texture = new Texture;
	this->color = glm::vec3(1.0f, 1.0f, 1.0f);
	this->vao = nullptr;
}

void Mesh::initialize() {
	VertexBuffer vbo;
	ElementBuffer ebo;
	vao = new VertexArray;

	vao->bind();
	vbo.bind();
	ebo.bind();

	vbo.setData(vertices);
	ebo.setData(indices);

	vao->setAttribPointer(0, 3, 0);
	vao->setAttribPointer(1, 3, offsetof(Vertex, normal));
	vao->setAttribPointer(2, 2, offsetof(Vertex, texture));

	vao->unbind();
	vbo.unbind();
	ebo.unbind();

	texture->initialize();
}

Mesh::~Mesh() {
	delete texture;
}

void Mesh::setTexture(const char* path) {
	texture = new Texture(path);
}

void Mesh::setColor(glm::vec3 color) {
	this->color = color;
}

void Mesh::setColor(GLfloat r, GLfloat g, GLfloat b) {
	this->color = glm::vec3(r, g, b);
}

glm::vec3 Mesh::getColor() {
	return color;
}

Texture* Mesh::getTexture() {
	return texture;
}

void Mesh::draw(Shader& shader) {
	shader.use();
	shader.setMat4("model", model);
	shader.setVec3("objectColor", color);

	vao->bind();
	texture->bind();
	vao->drawIndices(indices.size());
}
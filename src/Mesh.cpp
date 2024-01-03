#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices) {
	this->vertices = vertices;
	this->indices = indices;
	this->vao = nullptr;
	this->diffuse = new Texture(Texture::DIFFUSE);
	this->specular = new Texture(Texture::SPECULAR);
	this->shininess = 30.0f;
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

	diffuse->initialize();
	specular->initialize();
}

Mesh::~Mesh() {
	delete diffuse;
	delete specular;
}

void Mesh::setDiffuseTexture(const char* path) {
	diffuse = new Texture(Texture::DIFFUSE, path);
}

void Mesh::setSpecularTexture(const char* path) {
	specular = new Texture(Texture::SPECULAR, path);
}

void Mesh::setShininess(GLfloat shininess) {
	this->shininess = shininess;
}

Texture* Mesh::getDiffuseTexture() {
	return diffuse;
}

Texture* Mesh::getSpecularTexture() {
	return specular;
}

GLfloat Mesh::getShininess() {
	return shininess;
}

void Mesh::draw(Shader& shader) {
	vao->bind();
	diffuse->bind();
	specular->bind();

	shader.use();
	shader.setMat4("model", model);
	shader.setInt("material.diffuse", 0);
	shader.setInt("material.specular", 1);
	shader.setFloat("material.shininess", shininess);

	vao->drawIndices(indices.size());
}
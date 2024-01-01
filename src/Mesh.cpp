#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, const char* texturePath) {
	this->vertices = vertices;
	this->indices = indices;
	this->texture = texturePath == nullptr ? new Texture : new Texture(texturePath);
	
	VertexBuffer vbo;
	ElementBuffer ebo;

	vao.bind();
	vbo.bind();
	ebo.bind();

	vbo.setData(vertices);
	ebo.setData(indices);

	vao.setAttribPointer(0, 3, 0);
	vao.setAttribPointer(1, 3, offsetof(Vertex, normal));
	vao.setAttribPointer(2, 2, offsetof(Vertex, texture));

	vao.unbind();
	vbo.unbind();
	ebo.unbind();
}

Mesh::~Mesh() {
	delete texture;
}

void Mesh::setTexture(const char* path) {
	texture = new Texture(path);
}

Texture* Mesh::getTexture() {
	return texture;
}

void Mesh::draw(Shader& shader) {
	shader.use();
	shader.setMat4("model", model);

	vao.bind();
	texture->bind();
	vao.drawIndices(indices.size());
}
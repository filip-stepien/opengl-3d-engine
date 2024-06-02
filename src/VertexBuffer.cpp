#include "VertexBuffer.hpp"

engine::VertexBuffer::VertexBuffer() {
	glGenBuffers(1, &id);
}

void engine::VertexBuffer::setData(std::vector<Vertex>& vertices, GLenum usage) {
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), usage);
}

engine::VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &id);
}

void engine::VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void engine::VertexBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
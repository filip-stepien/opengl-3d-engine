#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer() {
	glGenBuffers(1, &id);
}

void VertexBuffer::setData(GLfloat* vertices, GLsizei size, GLenum usage) {
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &id);
}

void VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
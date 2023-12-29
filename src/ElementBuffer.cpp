#include "ElementBuffer.hpp"

ElementBuffer::ElementBuffer() {
	glGenBuffers(1, &id);
}

ElementBuffer::~ElementBuffer() {
	glDeleteBuffers(1, &id);
}

void ElementBuffer::setData(std::vector<GLuint>& indices, GLenum usage) {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), usage);
}

void ElementBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
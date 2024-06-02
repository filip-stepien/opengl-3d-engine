#include "ElementBuffer.hpp"

engine::ElementBuffer::ElementBuffer() {
	glGenBuffers(1, &id);
}

engine::ElementBuffer::~ElementBuffer() {
	glDeleteBuffers(1, &id);
}

void engine::ElementBuffer::setData(std::vector<GLuint>& indices, GLenum usage) {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), usage);
}

void engine::ElementBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void engine::ElementBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
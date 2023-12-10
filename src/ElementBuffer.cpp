#include "ElementBuffer.hpp"

ElementBuffer::ElementBuffer() {
	glGenBuffers(1, &id);
}

ElementBuffer::~ElementBuffer() {
	glDeleteBuffers(1, &id);
}

void ElementBuffer::setData(GLuint* vertices, GLsizei size, GLenum usage) {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, usage);
}

void ElementBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
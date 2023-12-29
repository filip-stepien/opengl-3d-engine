#include "VertexArray.hpp"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &id);
}

void VertexArray::bind() {
	glBindVertexArray(id);
}

void VertexArray::unbind() {
	glBindVertexArray(0);
}

void VertexArray::setAttribPointer(GLuint layout, GLuint numOfValues, GLuint pointerVal) {
	glVertexAttribPointer(
		layout, 
		numOfValues, 
		GL_FLOAT, 
		GL_FALSE, 
		sizeof(Vertex),
		(void*)pointerVal
	);
	glEnableVertexAttribArray(layout);
}

void VertexArray::drawVertices(GLuint numOfVertices, GLenum primitive) {
	glDrawArrays(primitive, 0, numOfVertices);
}

void VertexArray::drawIndices(GLuint numOfIndices, GLenum primitive) {
	glDrawElements(primitive, numOfIndices, GL_UNSIGNED_INT, 0);
}
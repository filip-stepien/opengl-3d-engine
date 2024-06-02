#include "VertexArray.hpp"

engine::VertexArray::VertexArray() {
	glGenVertexArrays(1, &id);
}

engine::VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &id);
}

void engine::VertexArray::bind() {
	glBindVertexArray(id);
}

void engine::VertexArray::unbind() {
	glBindVertexArray(0);
}

void engine::VertexArray::setAttribPointer(GLuint layout, GLuint numOfValues, GLuint pointerVal) {
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

void engine::VertexArray::drawVertices(GLuint numOfVertices, GLenum primitive) {
	glDrawArrays(primitive, 0, numOfVertices);
}

void engine::VertexArray::drawIndices(GLuint numOfIndices, GLenum primitive) {
	glDrawElements(primitive, numOfIndices, GL_UNSIGNED_INT, 0);
}
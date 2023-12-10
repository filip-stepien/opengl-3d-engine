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

void VertexArray::setAttribPointer(GLuint layout, GLuint numOfValues, GLuint strideVal, GLuint pointerVal) {
	glVertexAttribPointer(
		layout, 
		numOfValues, 
		GL_FLOAT, 
		GL_FALSE, 
		strideVal * sizeof(GLfloat), 
		(void*)(pointerVal * sizeof(GLfloat))
	);
	glEnableVertexAttribArray(layout);
}

void VertexArray::draw(GLuint numOfVertices, GLenum primitive) {
	bind();
	glDrawArrays(primitive, 0, numOfVertices);
}
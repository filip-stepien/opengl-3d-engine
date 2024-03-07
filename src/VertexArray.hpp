#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "VertexBuffer.hpp"

class VertexArray {
private:
	GLuint id;

public:
	VertexArray();
	~VertexArray();

	void setAttribPointer(GLuint layout, GLuint numOfValues, GLuint pointerVal);
	void bind();
	void unbind();
	void drawVertices(GLuint numOfVertices, GLenum primitive = GL_TRIANGLES);
	void drawIndices(GLuint numOfIndices, GLenum primitive = GL_TRIANGLES);
};

#endif
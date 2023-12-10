#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "VertexBuffer.hpp"

class VertexArray {
private:
	GLuint id;

public:
	VertexArray();
	~VertexArray();

	void setAttribPointer(GLuint layout, GLuint numOfValues, GLuint numOfStride, GLuint pointerVal);
	void bind();
	void unbind();
	void draw(GLuint numOfVertices, GLenum primitive = GL_TRIANGLES);
};
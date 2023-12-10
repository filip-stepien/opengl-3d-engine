#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

class VertexBuffer {
private:
	GLuint id;

public:
	VertexBuffer();
	~VertexBuffer();

	void setData(GLfloat* vertices, GLsizei size, GLenum usage = GL_STATIC_DRAW);
	void bind();
	void unbind();
};
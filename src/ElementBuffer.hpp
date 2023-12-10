#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ElementBuffer {
private:
	GLuint id;

public:
	ElementBuffer();
	~ElementBuffer();

	void setData(GLuint* vertices, GLsizei size, GLenum usage = GL_STATIC_DRAW);
	void bind();
	void unbind();
};
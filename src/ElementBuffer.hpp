#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class ElementBuffer {
private:
	GLuint id;

public:
	ElementBuffer();
	~ElementBuffer();

	void setData(std::vector<GLuint>& indices, GLenum usage = GL_STATIC_DRAW);
	void bind();
	void unbind();
};

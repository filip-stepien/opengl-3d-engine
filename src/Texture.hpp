#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Texture {
private:
	GLuint id;

	void loadImage(const char* path);

public:
	Texture(const char* path, GLenum wrapping = GL_REPEAT);
	~Texture();

	void bind();
	void unbind();
};
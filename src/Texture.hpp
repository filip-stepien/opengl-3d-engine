#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Texture {
private:
	GLuint id;
	GLenum wrapping;
	const char* path;

	void loadImage(const char* path);

public:
	Texture(const char* path = "../resources/textures/default.png", GLenum wrapping = GL_REPEAT);
	~Texture();

	void initialize();
	void bind();
	void unbind();
};
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Texture {
public:
	using TextureType = enum TEXTURE { DIFFUSE, SPECULAR };

private:
	TextureType type;
	GLuint id;
	GLenum wrapping;
	const char* path;

	void loadImage(const char* path);

public:
	Texture(
		TextureType type = DIFFUSE,
		const char* path = "../resources/textures/default.png", 
		GLenum wrapping = GL_REPEAT
	);
	~Texture();

	void initialize();
	void bind();
	void unbind();
};
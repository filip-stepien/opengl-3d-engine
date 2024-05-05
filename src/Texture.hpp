#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Texture {
public:
	using TextureType = enum TEXTURE { DIFFUSE, SPECULAR };

private:
	TextureType type { DIFFUSE };
	GLuint id { 0 };
	GLenum wrapping { GL_REPEAT };
	const char* path { "../resources/textures/default.png" };

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

#endif
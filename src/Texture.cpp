#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void engine::Texture::loadImage(const char* path) {
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 3);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
}

engine::Texture::Texture(TextureType type, const char* path, GLenum wrapping) {
	this->path = path;
	this->wrapping = wrapping;
	this->type = type;
}

void engine::Texture::initialize() {
	glGenTextures(1, &id);
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	loadImage(path);
	unbind();
}

engine::Texture::~Texture() {
	glDeleteTextures(1, &id);
}

void engine::Texture::bind() {
	type == DIFFUSE ? glActiveTexture(GL_TEXTURE0) : glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, id);
}

void engine::Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
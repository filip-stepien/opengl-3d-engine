#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture;
};

class VertexBuffer {
private:
	GLuint id;

public:
	VertexBuffer();
	~VertexBuffer();

	void setData(std::vector<Vertex>& vertices, GLenum usage = GL_STATIC_DRAW);
	void bind();
	void unbind();
};
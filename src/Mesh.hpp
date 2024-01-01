#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "ElementBuffer.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

#include "Drawable.hpp"
#include "Scalable.hpp"
#include "Rotatable.hpp"
#include "Movable.hpp"

class Mesh : public Drawable, public Scalable, public Rotatable, public Movable {
protected:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	Texture* texture;
	glm::vec3 color;
	VertexArray vao;

	void initialize();

public:
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
	~Mesh();

	void setTexture(const char* path);
	void setColor(glm::vec3 color);
	void setColor(GLfloat r, GLfloat g, GLfloat b);

	Texture* getTexture();
	glm::vec3 getColor();

	void draw(Shader& shader);
};
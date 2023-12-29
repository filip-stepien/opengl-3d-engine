#pragma once

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
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	Texture* texture;
	VertexArray vao;

public:
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, const char* texturePath = nullptr);
	~Mesh();
	void draw(Shader& shader);
};
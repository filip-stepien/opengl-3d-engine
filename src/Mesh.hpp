#pragma once

#include "Drawable.hpp"
#include "Transformable.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "ElementBuffer.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

class Mesh : public Drawable, public Transformable {
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
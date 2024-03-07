#ifndef MESH_H
#define MESH_H

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
	VertexArray* vao;
	Texture* diffuse;
	Texture* specular;
	GLfloat shininess;

public:
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
	~Mesh();

	void setDiffuseTexture(const char* path);
	void setSpecularTexture(const char* path);
	void setShininess(GLfloat shininess);

	Texture* getDiffuseTexture();
	Texture* getSpecularTexture();
	GLfloat getShininess();

	virtual void initialize();
	void draw(Shader& shader) override;
};

#endif
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
#include "Transformable.hpp"

class Mesh : public Drawable, public Transformable {
protected:
	std::vector<Vertex> vertices {};
	std::vector<GLuint> indices {};

	VertexArray* vao = nullptr;
    VertexBuffer* vbo = nullptr;
    ElementBuffer* ebo = nullptr;

	Texture* diffuse = new Texture(Texture::DIFFUSE);
	Texture* specular = new Texture(Texture::SPECULAR);
	GLfloat shininess = 30.0f;

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
    void drawToBuffer(Shader& shader) override;
};

#endif
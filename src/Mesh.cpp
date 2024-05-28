#include "Mesh.hpp"

#include <utility>
#include "Engine.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices) {
	this->vertices = std::move(vertices);
	this->indices = std::move(indices);

    Engine::get().addMesh(this);
}

void Mesh::initialize() {
	ebo = new ElementBuffer;
    vbo = new VertexBuffer;
	vao = new VertexArray;

	vao->bind();
	vbo->bind();
	ebo->bind();

	vbo->setData(vertices);
	ebo->setData(indices);

	vao->setAttribPointer(0, 3, 0);
	vao->setAttribPointer(1, 3, offsetof(Vertex, normal));
	vao->setAttribPointer(2, 2, offsetof(Vertex, texture));

	vao->unbind();
	vbo->unbind();
	ebo->unbind();

	diffuse->initialize();
	specular->initialize();
}

Mesh::~Mesh() {
	delete diffuse;
	delete specular;
    delete vao;
    delete vbo;
    delete ebo;
}

void Mesh::setDiffuseTexture(const char* path) {
	diffuse = new Texture(Texture::DIFFUSE, path);
}

void Mesh::setSpecularTexture(const char* path) {
	specular = new Texture(Texture::SPECULAR, path);
}

void Mesh::setShininess(GLfloat shininess) {
	this->shininess = shininess;
}

Texture* Mesh::getDiffuseTexture() {
	return diffuse;
}

Texture* Mesh::getSpecularTexture() {
	return specular;
}

GLfloat Mesh::getShininess() {
	return shininess;
}

void Mesh::draw(Shader& shader) {
	vao->bind();
	diffuse->bind();
	specular->bind();

	shader.use();
    shader.setFloat("textureScaleX", textureScaleX);
    shader.setFloat("textureScaleY", textureScaleY);
    shader.setBool("ignoreLight", ignoreLight);
    shader.setBool("viewIndependent", viewIndependent);
	shader.setMat4("model", model);
	shader.setInt("material.diffuse", 0);
	shader.setInt("material.specular", 1);
	shader.setFloat("material.shininess", shininess);

	vao->drawIndices(indices.size());
}

void Mesh::drawToBuffer(Shader &shader) {
    vao->bind();

    shader.use();
    shader.setUInt("objectIndex", 200);
    shader.setMat4("model", model);

    vao->drawIndices(indices.size());
}

void Mesh::setTextureScale(float scaleX, float scaleY) {
    this->textureScaleX = scaleX;
    this->textureScaleY = scaleY;
}

void Mesh::setIgnoreLight(bool ignore) {
    this->ignoreLight = ignore;
}

void Mesh::setViewIndependent(bool independent) {
    this->viewIndependent = independent;
}

void Mesh::setOnForeground(bool isOnForeground) {
	this->foreground = isOnForeground;
}

bool Mesh::isOnForeground() {
	return foreground;
}
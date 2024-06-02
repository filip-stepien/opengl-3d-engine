#include "Mesh.hpp"

#include <utility>
#include "Engine.hpp"

engine::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices) {
	this->vertices = std::move(vertices);
	this->indices = std::move(indices);

    Engine::get().addMesh(this);
}

void engine::Mesh::initialize() {
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

engine::Mesh::~Mesh() {
	delete diffuse;
	delete specular;
    delete vao;
    delete vbo;
    delete ebo;
}

void engine::Mesh::setDiffuseTexture(const char* path) {
	diffuse = new Texture(Texture::DIFFUSE, path);
}

void engine::Mesh::setSpecularTexture(const char* path) {
	specular = new Texture(Texture::SPECULAR, path);
}

void engine::Mesh::setShininess(GLfloat shininess) {
	this->shininess = shininess;
}

engine::Texture* engine::Mesh::getDiffuseTexture() {
	return diffuse;
}

engine::Texture* engine::Mesh::getSpecularTexture() {
	return specular;
}

GLfloat engine::Mesh::getShininess() {
	return shininess;
}

bool engine::Mesh::isViewIndependent() {
    return viewIndependent;
}

bool engine::Mesh::isOnForeground() {
    return foreground;
}

void engine::Mesh::draw(Shader& shader) {
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

void engine::Mesh::drawToBuffer(Shader &shader) {
    vao->bind();

    shader.use();
    shader.setUInt("objectIndex", getID());
    shader.setMat4("model", model);

    vao->drawIndices(indices.size());
}

void engine::Mesh::setTextureScale(float scaleX, float scaleY) {
    this->textureScaleX = scaleX;
    this->textureScaleY = scaleY;
}

void engine::Mesh::setIgnoreLight(bool ignore) {
    this->ignoreLight = ignore;
}

void engine::Mesh::setViewIndependent(bool independent) {
    this->viewIndependent = independent;
}

void engine::Mesh::setOnForeground(bool foreground) {
    this->foreground = foreground;
}

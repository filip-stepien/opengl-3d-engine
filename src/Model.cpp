#include "Model.hpp"
#include <OBJ_loader.h>

Model::~Model() {
    for (Mesh* mesh : meshes) {
        delete mesh;
    }

    meshes.clear();
}

std::vector<Mesh *> Model::getMeshes() {
    return meshes;
}

void Model::load(const std::string& path) {
    objl::Loader loader;
    bool fileLoaded = loader.LoadFile(path);

    if (!fileLoaded) {
        std::cout << "Failed to load file: " << path << std::endl;
        return;
    }

    for (objl::Mesh& mesh : loader.LoadedMeshes) {
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;

        vertices.reserve(mesh.Vertices.size());
        for (objl::Vertex v : mesh.Vertices) {
            vertices.push_back({
                glm::vec3(v.Position.X, v.Position.Y, v.Position.Z),
                glm::vec3(v.Normal.X, v.Normal.Y, v.Position.Z),
                glm::vec2(v.TextureCoordinate.X, v.TextureCoordinate.Y)
            });
        }

        indices.reserve(mesh.Indices.size());
        for (GLuint i : mesh.Indices) {
            indices.push_back(i);
        }

        meshes.push_back(
            new Mesh(vertices, indices)
        );
    }
}


void Model::setPosition(glm::vec3 position) {
    for (auto mesh : meshes)
        mesh->setPosition(position);
}

void Model::setPosition(GLfloat x, GLfloat y, GLfloat z) {
    for (auto mesh : meshes)
        mesh->setPosition(x, y, z);
}

void Model::move(GLfloat x, GLfloat y, GLfloat z) {
    for (auto mesh : meshes)
        mesh->move(x, y, z);
}

void Model::move(glm::vec3 translation) {
    for (auto& mesh : meshes)
        mesh->move(translation);
}

void Model::setRotation(GLfloat angleDegrees, GLfloat x, GLfloat y, GLfloat z) {
    for (auto& mesh : meshes)
        mesh->setRotation(angleDegrees, x, y, z);
}

void Model::setRotation(GLfloat angleDegrees, glm::vec3 origin) {
    for (auto& mesh : meshes)
        mesh->setRotation(angleDegrees, origin);
}

void Model::rotate(GLfloat angleDegrees, GLfloat x, GLfloat y, GLfloat z) {
    for (auto& mesh : meshes)
        mesh->rotate(angleDegrees, x, y, z);
}

void Model::rotate(GLfloat angleDegrees, glm::vec3 origin) {
    for (auto& mesh : meshes)
        mesh->rotate(angleDegrees, origin);
}

void Model::setScale(GLfloat x, GLfloat y, GLfloat z) {
    for (auto& mesh : meshes)
        mesh->setScale(x, y, z);
}

void Model::setScale(glm::vec3 scale) {
    for (auto& mesh : meshes)
        mesh->setScale(scale);
}

void Model::scale(GLfloat x, GLfloat y, GLfloat z) {
    for (auto& mesh : meshes)
        mesh->scale(x, y, z);
}

void Model::scale(glm::vec3 scale) {
    for (auto& mesh : meshes)
        mesh->scale(scale);
}

void Model::setDiffuseTexture(const char* path) {
    for (auto& mesh : meshes)
        mesh->setDiffuseTexture(path);
}

void Model::setSpecularTexture(const char* path) {
    for (auto& mesh : meshes)
        mesh->setSpecularTexture(path);
}

void Model::setShininess(GLfloat shininess) {
    for (auto& mesh : meshes)
        mesh->setShininess(shininess);
}

void Model::setTextureScale(float scaleX, float scaleY) {
    for (auto& mesh : meshes)
        mesh->setTextureScale(scaleX, scaleY);
}

void Model::setIgnoreLight(bool ignore) {
    for (auto& mesh : meshes)
        mesh->setIgnoreLight(ignore);
}

void Model::setViewIndependent(bool independent) {
    for (auto& mesh : meshes)
        mesh->setViewIndependent(independent);
}

void Model::setOnForeground(bool foreground) {
    for (auto& mesh : meshes)
        mesh->setOnForeground(foreground);
}


#include "Model.hpp"
#include <OBJ_loader.h>

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
#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>

#include "Model.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

class Model {
private:
    std::vector<Mesh*> meshes;

public:
    ~Model();

    void load(const std::string& path);
    std::vector<Mesh*> getMeshes();
};

#endif

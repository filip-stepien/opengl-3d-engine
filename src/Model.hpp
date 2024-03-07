#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>

#include "Model.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

class Model {
public:
    ~Model();
    std::vector<Mesh*> meshes;
    void load(const std::string& path);
};

#endif

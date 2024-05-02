#ifndef PLANE_3D_H
#define PLANE_3D_H

#include "Mesh.hpp"

class Plane3D : public Mesh {
public:
    Plane3D() : Mesh(getVertices(), getIndices()) {}

private:
    std::vector<Vertex> getVertices();
    std::vector<GLuint> getIndices();
};

#endif
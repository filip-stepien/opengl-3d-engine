#include "Plane3D.hpp"

std::vector<Vertex> Plane3D::getVertices() {
    return {
        { {-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
        { { 1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f} },
        { { 1.0f,  1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f} },
        { {-1.0f,  1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} }
    };
}

std::vector<GLuint> Plane3D::getIndices() {
    return {
        0, 1, 2,
        2, 3, 0
    };
}
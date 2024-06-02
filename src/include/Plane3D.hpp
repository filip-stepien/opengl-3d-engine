#ifndef PLANE_3D_H
#define PLANE_3D_H

#include "Mesh.hpp"

namespace engine {
    /**
     * @class Plane3D
     * @brief Plane mesh.
     */
    class Plane3D : public Mesh {
    public:
        /**
         * @brief Constructor for Plane3D.
         * Initializes the mesh with vertices and indices for a 3D plane.
         */
        Plane3D() : Mesh(getVertices(), getIndices()) {}

    private:
        /**
         * @brief Gets the vertices for the 3D plane.
         * @return A vector of vertices for the 3D plane.
         */
        std::vector<Vertex> getVertices();

        /**
         * @brief Gets the indices for the 3D plane.
         * @return A vector of indices for the 3D plane.
         */
        std::vector<GLuint> getIndices();
    };
}

#endif

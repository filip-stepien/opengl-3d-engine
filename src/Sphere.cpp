#include "Sphere.hpp"

void Sphere::populateVertices() {
    GLfloat x, y, z, xy;
    GLfloat nx, ny, nz, lengthInv = 1.0f / radius;
    GLfloat s, t;

    GLfloat sectorStep = 2 * M_PI / static_cast<GLfloat>(sectorCount);
    GLfloat stackStep = M_PI / static_cast<GLfloat>(stackCount);
    GLfloat sectorAngle, stackAngle;

    Vertex vertex;
    for (GLuint i = 0; i <= stackCount; ++i) {
        stackAngle = M_PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (GLuint j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            vertex.position = glm::vec3(x, y, z);

            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            vertex.normal = glm::vec3(nx, ny, nz);

            s = (GLfloat)j / sectorCount;
            t = (GLfloat)i / stackCount;
            vertex.texture = glm::vec2(s, t);

            vertices.push_back(vertex);
        }
    }
}

void Sphere::populateIndices() {
    GLuint k1, k2;
    for (GLuint i = 0; i < stackCount; i++) {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;

        for (GLuint j = 0; j < sectorCount; j++, k1++, k2++) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stackCount - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

Sphere::Sphere(GLfloat radius, GLuint sectorCount, GLuint stackCount)
    : Shape(vertices, indices) 
{
    this->radius = radius;
    this->sectorCount = sectorCount;
    this->stackCount = stackCount;

    populateVertices();
    populateIndices();
    initialize();
}
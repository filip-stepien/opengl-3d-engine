#include "Torus.hpp"
#include "Engine.hpp"

Torus::Torus(GLuint innerRadius, GLuint outerRadius, GLuint sides, GLuint rings) : Shape(vertices, indices){
	this->sides = sides;
	this->rings = rings;
	this->innerRadius = innerRadius;
	this->outerRadius = outerRadius;

    populateVertices();
    populateIndices();
    Engine::get().addToShapePipeline(this);
}

void Torus::populateVertices() {
    vertices.clear();

    float sideStep = 2 * M_PI / sides;
    float ringStep = 2 * M_PI / rings;
    float theta, phi, x, y, z, u, v;

    for (int i = 0; i <= rings; ++i) {
        theta = i * ringStep;

        for (int j = 0; j <= sides; ++j) {
            phi = j * sideStep;

            x = (outerRadius + innerRadius * cos(phi)) * cos(theta);
            y = (outerRadius + innerRadius * cos(phi)) * sin(theta);
            z = innerRadius * sin(phi);

            glm::vec3 normal = glm::normalize(glm::vec3(cos(phi) * cos(theta), cos(phi) * sin(theta), sin(phi)));

            u = (float)j / sides;
            v = (float)i / rings;

            vertices.push_back(Vertex{ glm::vec3(x, y, z), normal, glm::vec2(u, v) });
        }
    }
}

void Torus::populateIndices() {
    indices.clear();

    int first, second;
    for (int i = 0; i < rings; ++i) {
        for (int j = 0; j < sides; ++j) {
            first = (i * (sides + 1)) + j;
            second = first + sides + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
}

void Torus::setSides(GLuint sides) {
    this->sides = sides;
    populateVertices();
    populateIndices();
}

void Torus::setRings(GLuint rings) {
    this->rings = rings;
    populateVertices();
    populateIndices();
}

void Torus::setOuterRadius(GLfloat outerRadius) {
    this->outerRadius = outerRadius;
    populateVertices();
    populateIndices();
}

void Torus::setInnerRadius(GLfloat innerRadius) {
    this->innerRadius = innerRadius;
    populateVertices();
    populateIndices();
}

GLuint Torus::getSides() {
    return sides;
}

GLuint Torus::getRings() {
    return rings;
}

GLfloat Torus::getOuterRadius() {
    return outerRadius;
}

GLfloat Torus::getInnerRadius() {
    return innerRadius;
}
#pragma once

#define _USE_MATH_DEFINES
#include "Shape.hpp"

class Torus : public Shape {
private:
	GLuint sides;
	GLuint rings;
	GLuint outerRadius;
	GLuint innerRadius;

public:
	Torus(GLuint innerRadius = 1.0f, GLuint outerRadius = 2.0f, GLuint sides = 32, GLuint rings = 32);

	void populateVertices() override;
	void populateIndices() override;
};
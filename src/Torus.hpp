#pragma once

#define _USE_MATH_DEFINES
#include "Shape.hpp"

class Torus : public Shape {
private:
	GLuint sides;
	GLuint rings;
	GLfloat outerRadius;
	GLfloat innerRadius;

public:
	Torus(GLuint innerRadius = 1.0f, GLuint outerRadius = 2.0f, GLuint sides = 32, GLuint rings = 32);

	void setSides(GLuint sides);
	void setRings(GLuint rings);
	void setInnerRadius(GLfloat innerRadius);
	void setOuterRadius(GLfloat outerRadius);
	GLuint getSides();
	GLuint getRings();
	GLfloat getInnerRadius();
	GLfloat getOuterRadius();

	void populateVertices() override;
	void populateIndices() override;
};
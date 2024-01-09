#pragma once

#define _USE_MATH_DEFINES
#include "Shape.hpp"

class Sphere : public Shape {
private:
	GLfloat radius;
	GLuint sectorCount;
	GLuint stackCount;

protected:
	void populateVertices() override;
	void populateIndices() override;
public:
	Sphere(GLfloat radius = 1.0f, GLuint sectorCount = 24, GLuint stackCount = 24);

	void Sphere::setRadius(GLfloat radius);
	void Sphere::setSectors(GLuint sectors);
	void Sphere::setStacks(GLuint stacks);
	
	GLfloat Sphere::getRadius();
	GLuint Sphere::getSectors();
	GLuint Sphere::getStacks();
};
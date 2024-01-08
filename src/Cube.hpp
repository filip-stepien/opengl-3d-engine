#pragma once

#define _USE_MATH_DEFINES
#include "Shape.hpp"

class Cube : public Shape {
public:
	Cube();
	void populateVertices() override;
	void populateIndices() override;
};
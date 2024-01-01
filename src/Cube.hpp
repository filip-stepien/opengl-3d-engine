#pragma once

#include "Shape.hpp"

class Cube : public Shape {
protected:
	void populateVertices() override;
	void populateIndices() override;
public:
	Cube();
};
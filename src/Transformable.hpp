#pragma once

#include <glm/glm.hpp>

class Transformable {
protected:
	glm::mat4 model;
public:
	Transformable();
};
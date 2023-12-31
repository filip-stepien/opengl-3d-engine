#pragma once

#include <glm/glm.hpp>

#include "EngineObject.hpp"

class Transformable : public EngineObject {
protected:
	glm::mat4 model;
public:
	Transformable();
};
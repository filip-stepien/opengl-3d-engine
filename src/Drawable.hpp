#pragma once

#include "Shader.hpp"

class Drawable {
public:
	virtual void draw(Shader& shader) {};
};
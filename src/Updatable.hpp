#pragma once

#include "Shader.hpp"

class Updatable {
public:
	void update(Shader& shader) {};
	void update(Shader& shader, int index) {};
};
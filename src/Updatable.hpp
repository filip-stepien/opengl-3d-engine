#pragma once

#include "Shader.hpp"

class Updatable {
public:
    virtual void update(Shader& shader) {};
	void update(Shader& shader, int index) {};
};
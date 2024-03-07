#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Shader.hpp"

class Drawable {
public:
	virtual void draw(Shader& shader) {};
};

#endif
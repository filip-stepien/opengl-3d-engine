#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.hpp"

int main() {
	Engine& engine = Engine::get();

	engine
	.setWindowDimensions(800, 800)
	.setWindowTitle("Title")
	.build();

	return 0;
}
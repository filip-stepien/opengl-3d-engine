#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine.hpp"

namespace cb {
	void onResize(GLFWwindow* window, int width, int height);
    void onKeyAction(GLFWwindow* window, int key, int scancode, int action, int mods);
    void onButtonAction(GLFWwindow* window, int button, int action, int mods);
    void onMouseMove(GLFWwindow* window, double xpos, double ypos);
}
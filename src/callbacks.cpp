#include "callbacks.hpp"

namespace cb {
	void onResize(GLFWwindow* window, int width, int height) {
		Engine::get().onResize(window, width, height);
	}

	void onKeyAction(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Engine::get().handleKeyAction(action);
	}

	void onButtonAction(GLFWwindow* window, int button, int action, int mods) {
		Engine::get().handleButtonAction(action);
	}

	void onMouseMove(GLFWwindow* window, double xpos, double ypos) {
		Engine::get().handleMouseMove();
	}
}
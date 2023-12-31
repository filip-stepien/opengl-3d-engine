#include "callbacks.hpp"

namespace cb {
	void onResize(GLFWwindow* window, int width, int height) {
		Engine::get().onResize(window, width, height);
		Engine::get().getCamera()->updateProjection();
	}

	void onKeyAction(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Engine::get().handleKeyAction(key, action);
	}

	void onButtonAction(GLFWwindow* window, int button, int action, int mods) {
		Engine::get().handleButtonAction(button, action);
	}

	void onMouseMove(GLFWwindow* window, double xpos, double ypos) {
		Engine::get().handleMouseMove();

		Camera* camera = Engine::get().getCamera();
		if(camera->isMovementEnabled())
			camera->handleMouseMove(xpos, ypos);
	}
}
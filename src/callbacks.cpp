#include "callbacks.hpp"

namespace cb {
	void onResize(GLFWwindow* window, int width, int height) {
		Engine::get().onResize(window, width, height);
	}
}
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.hpp"
#include "App.hpp"

class DebugApp : public App {
	void handler() {
		std::cout << "test" << std::endl;
	}

	void move() {
		glm::vec2 pos = getMousePosition();
		std::cout << "x: " << pos.x << " y: " << pos.y << std::endl;
	}

	void setup() {
		//onKeyClick(GLFW_KEY_A, getHandler(&DebugApp::handler));
		//onMouseClick(GLFW_MOUSE_BUTTON_1, getHandler(&DebugApp::handler));
		//onMouseMove(getHandler(&DebugApp::move));
	}
};


int main() {
	DebugApp app;
	Camera cam;
	cam.setProjection(Camera::PERSPECTIVE, 0.1f, 100.0f);
	cam.setInitialFocus(0.0f, 0.0f, 0.0f);
	cam.move(6.0f, 3.0f, 6.0f);
	cam.setMovementEnabled(false);

	Engine& engine = Engine::get();

	engine
	.setWindowDimensions(800, 800)
	.setWindowTitle("Title")
	.setApp(&app)
	.setCamera(&cam)
	.build();

	return 0;
}
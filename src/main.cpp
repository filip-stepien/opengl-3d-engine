#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.hpp"
#include "App.hpp"

class DebugApp : public App {
public:
	Cube cube;
	Sphere sphere;

	void close() {
		Engine::get().close();
	}

	void setup() {
		cube.setColor(1.0f, 0.0f, 0.0f);
		sphere.setTexture("../resources/textures/ball.jpg");
		sphere.move(3.0f, 0.0f, 0.0f);

		onKeyClick(GLFW_KEY_ESCAPE, getHandler(&DebugApp::close));
	}
};


int main() {
	DebugApp app;

	Camera cam;
	cam.setProjection(Camera::PERSPECTIVE, 0.1f, 100.0f);
	cam.setInitialFocus(0.0f, 0.0f, 0.0f);
	cam.move(6.0f, 3.0f, 6.0f);
	cam.setMovementEnabled(true);

	Engine::get()
	.setWindowDimensions(800, 800)
	.setWindowTitle("Title")
	.setMouseCapture(true)
	.setApp(&app)
	.setCamera(&cam)
	.build();

	return 0;
}
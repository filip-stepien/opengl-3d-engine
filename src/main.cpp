#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.hpp"
#include "App.hpp"

class DebugApp : public App {
public:
	Cube cube;
	Sphere sphere;
	Light light;

	void close() {
		Engine::get().close();
	}

	void setup() {
		sphere.move(3.0f, 0.0f, 0.0f);
		sphere.setDiffuseTexture("../resources/textures/ball.jpg");

		cube.setDiffuseTexture("../resources/textures/container.png");
		cube.setSpecularTexture("../resources/textures/container_specular.png");
		cube.setShininess(5.0f);

		light.move(2.0f, 1.5f, 3.0f);
		light.setAmbient(0.0f, 0.1f, 0.0f);
		light.setDiffuse(1.0f, 1.0f, 1.0f);

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
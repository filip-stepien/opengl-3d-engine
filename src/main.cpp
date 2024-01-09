#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.hpp"
#include "App.hpp"
#include "Torus.hpp"
#include "Cube.hpp"
#include "Sphere.hpp"

class DebugApp : public App {
public:
	//Cube cube;
	Torus torus { 1.0f, 10.0f, 32, 32 };
	Sphere sphere { 3.0f, 32, 32 };
	Light light;

	void close() {
		Engine::get().close();
	}

	void setup() {
		light.move(12.0f, 1.5f, 13.0f);
		light.setAmbient(0.1f, 0.1f, 0.1f);
		light.setDiffuse(1.0f, 1.0f, 1.0f);

		torus.rotate(90.0f, 1.0f, 0.0f, 0.0f);

		torus.setDiffuseTexture("../resources/textures/debug.png");

		sphere.setDiffuseTexture("../resources/textures/ball.jpg");
		sphere.scale(1.0f, 0.5f, 1.0f);

		onKeyClick(GLFW_KEY_ESCAPE, getHandler(&DebugApp::close));
	}

	void loop() {
		float delta = Engine::get().getDeltaTime();

		torus.rotate(1.0f * delta, 0.0f, 0.0f, 1.0f);
		torus.rotate(0.5f * delta, 0.0f, 1.0f, 0.0f);
	}
};


int main() {
	DebugApp app;

	Camera cam;
	cam.setProjection(Camera::PERSPECTIVE, 0.1f, 100.0f);
	cam.setInitialFocus(0.0f, 0.0f, 0.0f);
	cam.move(12.0f, 3.0f, 12.0f);
	cam.setSpeed(15.0f);
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
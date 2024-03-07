#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.hpp"
#include "Model.hpp"

class Test : public App {
    Light light;

    void setup() override {
        light.move(3.0f, 6.0f, 4.0f);
    }
};

int main() {
    Test app;

	Camera cam;
	cam.setProjection(Camera::PERSPECTIVE, 0.1f, 100.0f);
	cam.setInitialFocus(0.0f, 0.0f, 0.0f);
	cam.move(12.0f, 3.0f, 12.0f);
	cam.setSpeed(15.0f);
	cam.setMovementEnabled(true);

	Engine::get()
	.setWindowDimensions(800, 800)
	.setWindowTitle("Demo technologiczne")
	.setWindowMaximized(true)
	.setMouseCapture(true)
	.setApp(&app)
	.setCamera(&cam)
	.build();

	return 0;
}
#include "Demo.hpp"

int main() {
    using namespace demo;

    Demo app;

	Camera cam;
	cam.setProjection(Camera::PERSPECTIVE, 0.1f, 100.0f);
	cam.setPosition(0.0f, 1.0f, 0.0f);
	cam.setSpeed(2.5f);
	cam.setMovementEnabled(false);
    cam.setYAxisLocked(true);
    cam.setRestrictMovementBox(9.5f, 9.5f, 9.5f);
    cam.setInitialFocus(-8.0f, 0.5f, 0.0f);

	Engine::get()
	.setWindowDimensions(800, 800)
	.setWindowTitle("RoboShooter")
	.setWindowMaximized(true)
	.setMouseCapture(true)
	.setApp(&app)
	.setCamera(&cam)
	.build();

	return 0;
}
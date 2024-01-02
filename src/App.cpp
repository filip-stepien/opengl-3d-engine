#include "App.hpp"
#include "Engine.hpp"

void App::setup() {}
void App::loop() {}

App::App() {
	Camera cam;
	cam.setProjection(Camera::PERSPECTIVE, 0.1f, 100.0f);
	cam.setInitialFocus(0.0f, 0.0f, 0.0f);
	cam.move(6.0f, 3.0f, 6.0f);
	cam.setMovementEnabled(true);

	Engine::get()
		.setWindowDimensions(800, 800)
		.setWindowTitle("Title")
		.setMouseCapture(true)
		.setApp(this)
		.setCamera(&cam);
}

void App::run() {

}

void App::onKeyClick(int key, Handler handler) {
	Engine::get().keyClickHandlers[key] = handler;
}

void App::onKeyRelease(int key, Handler handler) {
	Engine::get().keyReleaseHandlers[key] = handler;
}

void App::onMouseClick(int mouseButton, Handler handler) {
	Engine::get().mouseClickHandlers[mouseButton] = handler;
}

void App::onMouseRelease(int mouseButton, Handler handler) {
	Engine::get().mouseReleaseHandlers[mouseButton] = handler;
}

void App::onMouseMove(Handler handler) {
	Engine::get().mouseMoveHandler = handler;
}

glm::vec2 App::getMousePosition() {
	double xpos, ypos;
	glfwGetCursorPos(Engine::get().getWindow(), &xpos, &ypos);
	return glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos));
}
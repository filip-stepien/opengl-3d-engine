#include "App.hpp"
#include "Engine.hpp"

void engine::App::onKeyClick(int key, Handler handler) {
	Engine::get().keyClickHandlers[key] = handler;
}

void engine::App::onKeyRelease(int key, Handler handler) {
	Engine::get().keyReleaseHandlers[key] = handler;
}

void engine::App::onMouseClick(int mouseButton, Handler handler) {
	Engine::get().mouseClickHandlers[mouseButton] = handler;
}

void engine::App::onMouseRelease(int mouseButton, Handler handler) {
	Engine::get().mouseReleaseHandlers[mouseButton] = handler;
}

void engine::App::onMouseMove(Handler handler) {
	Engine::get().mouseMoveHandler = handler;
}

glm::vec2 engine::App::getMousePosition() {
	double xpos, ypos;
	glfwGetCursorPos(Engine::get().getWindow(), &xpos, &ypos);
	return { static_cast<float>(xpos), static_cast<float>(ypos) };
}
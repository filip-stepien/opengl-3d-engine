#include "Engine.hpp"

Engine::Engine() : 
	keyClickHandlers { nullptr },
	keyReleaseHandlers{ nullptr },
	mouseClickHandlers{ nullptr },
	mouseReleaseHandlers{ nullptr }
{
	windowWidth = 800;
	windowHeight = 600;
	windowTitle = nullptr;
	windowMode = WindowMode::DEFAULT;
	window = nullptr;
	app = nullptr;
	camera = nullptr;
	mouseMoveHandler = nullptr;

	currentFrame = 0;
	lastFrame = 0;
	deltaTime = 0;
}

Engine::~Engine() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

Engine& Engine::get() {
	static Engine engine;
	return engine;
}

Engine& Engine::setWindowDimensions(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	return *this;
}

Engine& Engine::setWindowTitle(const char* title) {
	windowTitle = title;
	return *this;
}

Engine& Engine::setWindowMode(WindowMode mode) {
	windowMode = mode;
	return *this;
}

Engine& Engine::setApp(App* app) {
	this->app = app;
	return *this;
}

Engine& Engine::setCamera(Camera* camera) {
	this->camera = camera;
	return *this;
}

float Engine::getAspectRatio() {
	return static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
}

GLuint Engine::getWindowWidth() {
	return windowWidth;
}

GLuint Engine::getWindowHeight() {
	return windowHeight;
}

const char* Engine::getWindowTitle() {
	return windowTitle;
}

Engine::WindowMode Engine::getWindowMode() {
	return windowMode;
}

GLFWwindow* Engine::getWindow() {
	return window;
}

App* Engine::getApp() {
	return app;
}

Camera* Engine::getCamera() {
	return camera;
}

GLdouble Engine::getDeltaTime() {
	return deltaTime;
}

void Engine::onResize(GLFWwindow* window, int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, windowWidth, windowHeight);
}

void Engine::setWindowHints() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
}

void Engine::initGlfw() {
	if (!glfwInit()) {
		std::cout << "Failed to init GLFW." << std::endl;
	}
}

void Engine::initGlad() {
	if (!gladLoadGL()) {
		std::cout << "Failed to create OpenGL context." << std::endl;
		glfwTerminate();
	}
}
void Engine::checkAppState() {
	if (app == nullptr) {
		std::cout << "APP ERROR" << std::endl;
		std::cout << "App class is not defined." << std::endl;
		glfwTerminate();
	}
}

void Engine::createWindow() {
	setWindowHints();
	window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);

	if (window == nullptr) {
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
}

void Engine::setViewport() {
	glViewport(0, 0, windowWidth, windowHeight);
	glfwSetFramebufferSizeCallback(window, cb::onResize);
}

void Engine::setupGl() {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
}

bool Engine::isRunning() {
	return !glfwWindowShouldClose(window);
}

void Engine::close() {
	glfwSetWindowShouldClose(window, true);
}

void Engine::clearWindow(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::endFrame() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Engine::updateDeltaTime() {
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void Engine::handleKeyAction(int action) {
	for (int i = 0; i < GLFW_KEY_LAST; i++) {
		Handler& clickHandler = keyClickHandlers[i];
		Handler& releaseHandler = keyReleaseHandlers[i];

		if (action == GLFW_PRESS && clickHandler != nullptr) {
			std::invoke(clickHandler, app);
		}
		else if (action == GLFW_RELEASE && releaseHandler != nullptr) {
			std::invoke(releaseHandler, app);
		}
	}
}

void Engine::handleButtonAction(int action) {
	for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++) {
		Handler& clickHandler = mouseClickHandlers[i];
		Handler& releaseHandler = mouseReleaseHandlers[i];

		if (action == GLFW_PRESS && clickHandler != nullptr) {
			std::invoke(clickHandler, app);
		}
		else if (action == GLFW_RELEASE && releaseHandler != nullptr) {
			std::invoke(releaseHandler, app);
		}
	}
}

void Engine::handleMouseMove() {
	if (mouseMoveHandler != nullptr) {
		std::invoke(mouseMoveHandler, app);
	}
}

bool Engine::build() {
	initGlfw();
	createWindow();
	initGlad();
	setViewport();
	setupGl();
	checkAppState();

	// DEBUG ///////////////////////////////////////////////////////////////////

	Shader shader(
		"../resources/shaders/basic_vertex.glsl", 
		"../resources/shaders/basic_fragment.glsl"
	);

	Light light1;
	Light light2;

	light1.move(1.2f, 1.0f, 2.0f);
	light2.move(2.0f, 2.0f, 2.0f);

	glfwSetKeyCallback(window, cb::onKeyAction);
	glfwSetMouseButtonCallback(window, cb::onButtonAction);
	glfwSetCursorPosCallback(window, cb::onMouseMove);

	camera->updateProjection();
	app->setup();

	Cube cube;
	cube.setColor(1.0f, 0.0f, 0.0f);

	while (isRunning()) {
		clearWindow(0.3f, 0.3f, 0.3f, 1.0f);
		updateDeltaTime();

		shader.use();

		light1.update(shader, 0);
		light2.update(shader, 1);
		camera->update(shader);

		cube.draw(shader);

		app->loop();
		endFrame();
	}

	///////////////////////////////////////////////////////////////////////////

	return true;
}
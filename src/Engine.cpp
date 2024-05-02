#include "Engine.hpp"
#include "Model.hpp"

#define GLT_IMPLEMENTATION
#include "gltext.h"

Engine::Engine() = default;

Engine::~Engine() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

Engine& Engine::get() {
	static Engine engine;
	return engine;
}

Engine& Engine::setWindowMaximized(bool maximized) {
	this->maximized = maximized;
	return *this;
}

Engine& Engine::setWindowFullscreen(bool fullscreen) {
	this->fullscreen = fullscreen;
	return *this;
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

Engine& Engine::setMouseCapture(bool mouseCapture) {
	this->mouseCapture = mouseCapture;
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

void Engine::watchPixel(GLuint x, GLuint y) {
    pixelX = x;
    pixelY = y;
}

PixelInfo Engine::getPixelInfo() {
    return pixelInfo;
}

void Engine::addLight(Light* light) {
	lights.push_back(light);
}

void Engine::addMesh(Mesh *mesh) {
    meshes.push_back(mesh);
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

	if (fullscreen) {
		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
		window = glfwCreateWindow(videoMode->width, videoMode->height, windowTitle, primaryMonitor, NULL);
		windowWidth = videoMode->width;
		windowHeight = videoMode->height;
	}
	else {
		window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
		if (maximized) {
			glfwMaximizeWindow(window);
			int framebufferWidth, framebufferHeight;
			glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
			windowWidth = framebufferWidth;
			windowHeight = framebufferHeight;
		}
	}

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
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (mouseCapture)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

void Engine::clearBuffer() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::updateDeltaTime() {
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void Engine::updatePixelInfo(FrameBuffer& fbo, Shader& shader) {
    fbo.enableWriting();
    clearBuffer();

    camera->update(shader);
    for (Mesh* mesh : meshes) {
        shader.setInt("objectIndex", mesh->getID());
        mesh->drawToBuffer(shader);
    }

    fbo.disableWriting();
    pixelInfo = fbo.readPixel(pixelX, pixelY);
}

void Engine::handleKeyAction(int key, int action) {
	Handler& clickHandler = keyClickHandlers[key];
	Handler& releaseHandler = keyReleaseHandlers[key];

	if (action == GLFW_PRESS && clickHandler != nullptr) {
		std::invoke(clickHandler, app);
	}
	else if (action == GLFW_RELEASE && releaseHandler != nullptr) {
		std::invoke(releaseHandler, app);
	}
}

void Engine::handleButtonAction(int button, int action) {
	Handler& clickHandler = mouseClickHandlers[button];
	Handler& releaseHandler = mouseReleaseHandlers[button];

	if (action == GLFW_PRESS && clickHandler != nullptr) {
		std::invoke(clickHandler, app);
	}
	else if (action == GLFW_RELEASE && releaseHandler != nullptr) {
		std::invoke(releaseHandler, app);
	}
}

void Engine::handleMouseMove() {
	if (mouseMoveHandler != nullptr) {
		std::invoke(mouseMoveHandler, app);
	}
}

void Engine::setCallbacks() {
	glfwSetKeyCallback(window, cb::onKeyAction);
	glfwSetMouseButtonCallback(window, cb::onButtonAction);
	glfwSetCursorPosCallback(window, cb::onMouseMove);
}

void Engine::initEngineObjects() {
    camera->initialize();
    app->setup();

    for (Mesh* mesh : meshes) {
        mesh->initialize();
    }
}

void Engine::updateEngineObjects(Shader& shader) {
    for (int i = 0; i < lights.size(); i++) {
        lights[i]->update(shader, i);
    }

    camera->update(shader);
    app->loop();
}

void Engine::drawEngineObjects(Shader &shader) {
    for (Mesh* mesh : meshes) {
        // debug
        // shader.setInt("selected", mesh->getID() == pixelInfo.idObject ? 1 : 0);
        //
        mesh->draw(shader);
    }
}

void Engine::endFrame() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Engine::build() {
	initGlfw();
	createWindow();
	initGlad();
	setViewport();
	setupGl();
	checkAppState();
	setCallbacks();
    initEngineObjects();

    FrameBuffer fbo;
	Shader shader;
    Shader pickingShader("C:/Users/user/Desktop/opengl-3d-engine/resources/shaders/picking_fragment.glsl");

    gltInit();
    GLTtext* text = gltCreateText();
    gltSetText(text, "+");

	while (isRunning()) {
        updateDeltaTime();
        updatePixelInfo(fbo, pickingShader);
		clearWindow(0.3f, 0.3f, 0.3f, 1.0f);
        updateEngineObjects(shader);
        drawEngineObjects(shader);

        gltBeginDraw();
        gltColor(1.0f, 1.0f, 1.0f, 1.0f);
        gltDrawText2D(text, windowWidth / 2, windowHeight / 2, 3.0f);
        gltEndDraw();

		endFrame();
	}

    gltDeleteText(text);
    gltTerminate();

	return true;
}
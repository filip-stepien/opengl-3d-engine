#include "Engine.hpp"

engine::Engine::Engine() = default;

engine::Engine::~Engine() {
	glfwDestroyWindow(window);
	glfwTerminate();
    gltTerminate();
}

engine::Engine& engine::Engine::get() {
	static Engine engine;
	return engine;
}

engine::Engine& engine::Engine::setWindowMaximized(bool maximized) {
	this->maximized = maximized;
	return *this;
}

engine::Engine& engine::Engine::setWindowFullscreen(bool fullscreen) {
	this->fullscreen = fullscreen;
	return *this;
}

engine::Engine& engine::Engine::setWindowDimensions(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	return *this;
}

engine::Engine& engine::Engine::setWindowTitle(const char* title) {
	windowTitle = title;
	return *this;
}

engine::Engine& engine::Engine::setWindowMode(WindowMode mode) {
	windowMode = mode;
	return *this;
}

engine::Engine& engine::Engine::setApp(App* app) {
	this->app = app;
	return *this;
}

engine::Engine& engine::Engine::setCamera(Camera* camera) {
	this->camera = camera;
	return *this;
}

engine::Engine& engine::Engine::setMouseCapture(bool mouseCapture) {
	this->mouseCapture = mouseCapture;
	return *this;
}

float engine::Engine::getAspectRatio() {
	return static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
}

GLuint engine::Engine::getWindowWidth() {
	return windowWidth;
}

GLuint engine::Engine::getWindowHeight() {
	return windowHeight;
}

const char* engine::Engine::getWindowTitle() {
	return windowTitle;
}

engine::Engine::WindowMode engine::Engine::getWindowMode() {
	return windowMode;
}

GLFWwindow* engine::Engine::getWindow() {
	return window;
}

engine::App* engine::Engine::getApp() {
	return app;
}

engine::Camera* engine::Engine::getCamera() {
	return camera;
}

GLdouble engine::Engine::getDeltaTime() {
	return deltaTime;
}

unsigned long long engine::Engine::getFramesCount() {
    return framesCount;
}

void engine::Engine::resetFramesCount() {
    framesCount = 0;
}

void engine::Engine::watchPixel(GLuint x, GLuint y) {
    pixelX = x;
    pixelY = y;
}

engine::PixelInfo engine::Engine::getPixelInfo() {
    return pixelInfo;
}

void engine::Engine::addLight(Light* light) {
	lights.push_back(light);
}

void engine::Engine::addMesh(Mesh *mesh) {
    meshes.push_back(mesh);
}

void engine::Engine::addText(Text2D *text) {
    texts.push_back(text);
}

void engine::Engine::onResize(GLFWwindow* window, int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, windowWidth, windowHeight);
}

void engine::Engine::setWindowHints() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
}

void engine::Engine::initGlfw() {
	if (!glfwInit()) {
		std::cout << "Failed to init GLFW." << std::endl;
	}
}

void engine::Engine::initGlad() {
	if (!gladLoadGL()) {
		std::cout << "Failed to create OpenGL context." << std::endl;
		glfwTerminate();
	}
}

void engine::Engine::initGlText() {
    gltInit();

    for (auto& text : texts) {
        text->setGLText(gltCreateText());
    }
};

void engine::Engine::checkAppState() {
	if (app == nullptr) {
		std::cout << "APP ERROR" << std::endl;
		std::cout << "App class is not defined." << std::endl;
		glfwTerminate();
	}
}

void engine::Engine::createWindow() {
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

void engine::Engine::setViewport() {
	glViewport(0, 0, windowWidth, windowHeight);
	glfwSetFramebufferSizeCallback(window, cb::onResize);
}

void engine::Engine::setupGl() {
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (mouseCapture)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

bool engine::Engine::isRunning() {
	return !glfwWindowShouldClose(window);
}

void engine::Engine::close() {
	glfwSetWindowShouldClose(window, true);
}

void engine::Engine::clearWindow(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void engine::Engine::clearBuffer() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void engine::Engine::updateDeltaTime() {
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void engine::Engine::updatePixelInfo(FrameBuffer& fbo, Shader& shader) {
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

void engine::Engine::handleKeyAction(int key, int action) {
	Handler& clickHandler = keyClickHandlers[key];
	Handler& releaseHandler = keyReleaseHandlers[key];

	if (action == GLFW_PRESS && clickHandler != nullptr) {
		std::invoke(clickHandler, app);
	}
	else if (action == GLFW_RELEASE && releaseHandler != nullptr) {
		std::invoke(releaseHandler, app);
	}
}

void engine::Engine::handleButtonAction(int button, int action) {
	Handler& clickHandler = mouseClickHandlers[button];
	Handler& releaseHandler = mouseReleaseHandlers[button];

	if (action == GLFW_PRESS && clickHandler != nullptr) {
		std::invoke(clickHandler, app);
	}
	else if (action == GLFW_RELEASE && releaseHandler != nullptr) {
		std::invoke(releaseHandler, app);
	}
}

void engine::Engine::handleMouseMove() {
	if (mouseMoveHandler != nullptr) {
		std::invoke(mouseMoveHandler, app);
	}
}

void engine::Engine::setCallbacks() {
	glfwSetKeyCallback(window, cb::onKeyAction);
	glfwSetMouseButtonCallback(window, cb::onButtonAction);
	glfwSetCursorPosCallback(window, cb::onMouseMove);
}

void engine::Engine::initEngineObjects() {
    camera->initialize();
    app->setup();

    for (Mesh* mesh : meshes) {
        mesh->initialize();
    }

    for (int i = 0; i < meshes.size(); i++) {
        if (meshes[i]->isOnForeground())
            std::swap(meshes[i], meshes.back());
    }
}

void engine::Engine::updateEngineObjects(Shader& shader) {
    for (int i = 0; i < lights.size(); i++) {
        lights[i]->update(shader, i);
    }

    camera->update(shader);
    app->loop();
}

void engine::Engine::drawEngineObjects(Shader &shader) {
    for (Mesh* mesh : meshes) {
        if (mesh->isOnForeground())
            glClear(GL_DEPTH_BUFFER_BIT);

        mesh->draw(shader);
    }
}

void engine::Engine::drawText() {
    for (auto text : texts) {
        if (!text->isVisible())
            continue;

        GLTtext* textObj = text->getGLText();
        glm::vec2 pos = text->getPosition();
        glm::vec4 color = text->getColor();
        float scale = text->getScale();
        std::string content = text->getContent();

        gltSetText(textObj, content.c_str());
        gltBeginDraw();
        gltColor(color.r, color.g, color.b, color.a);

        if (text->isCentered())
            gltDrawText2DAligned(textObj, pos.x, pos.y, scale, GLT_CENTER, GLT_CENTER);
        else
            gltDrawText2D(textObj, pos.x, pos.y, scale);

        gltEndDraw();
    }
}

void engine::Engine::endFrame() {
    glfwSwapBuffers(window);
    glfwPollEvents();
    framesCount++;
}

bool engine::Engine::build() {
	initGlfw();
	createWindow();
	initGlad();
	setViewport();
	setupGl();
	checkAppState();
	setCallbacks();
    initEngineObjects();
    initGlText();

    FrameBuffer fbo;
	Shader shader;
    Shader pickingShader("../resources/shaders/picking_fragment.glsl");

	while (isRunning()) {
        updateDeltaTime();
        updatePixelInfo(fbo, pickingShader);
		clearWindow(0.3f, 0.3f, 0.3f, 1.0f);
        updateEngineObjects(shader);
        drawEngineObjects(shader);
        drawText();
		endFrame();
	}

    app->cleanup();

	return true;
}

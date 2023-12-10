#include "Engine.hpp"

Engine::Engine() {
	windowWidth = 0;
	windowHeight = 0;
	windowTitle = nullptr;
	windowMode = WindowMode::DEFAULT;
	window = nullptr;
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

bool Engine::isRunning() {
	return !glfwWindowShouldClose(window);
}

void Engine::clearWindow(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
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

	// DEBUG ///////////////////////////////////////////////////////////////////

	Shader shader("../resources/shaders/vertex.glsl", "../resources/shaders/fragment.glsl");

	float vertices[] = {
		 0.5f,  0.5f, 0.0f, 1.0f,  0.0f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f, 0.0f,  1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f,  0.0f, 1.0f, // bottom left
		-0.5f,  0.5f, 0.0f, 1.0f,  0.0f, 1.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	VertexArray vao;
	VertexBuffer vbo;
	ElementBuffer ebo;

	vao.bind();
	vbo.bind();
	ebo.bind();

	vbo.setData(vertices, sizeof(vertices));
	ebo.setData(indices, sizeof(indices));

	vao.setAttribPointer(0, 3, 6, 0);
	vao.setAttribPointer(1, 3, 6, 3);

	while (isRunning()) {
		clearWindow(0.2f, 0.3f, 0.3f, 1.0f);

		shader.use();
		vao.drawIndices(6);

		endFrame();
	}

	///////////////////////////////////////////////////////////////////////////

	return true;
}
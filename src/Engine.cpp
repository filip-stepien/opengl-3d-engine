#include "Engine.hpp"

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

Engine::Engine() {
	windowWidth = 0;
	windowHeight = 0;
	windowTitle = nullptr;
	windowMode = WINDOW_MODE::DEFAULT;
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

bool Engine::buildWindow() {
	if (!glfwInit()) {
		std::cout << "Failed to init GLFW." << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
	
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGL()) {
		std::cout << "Failed to create OpenGL context." << std::endl;
		glfwTerminate();
		return false;
	}

	glViewport(0, 0, windowWidth, windowHeight);
	glfwSetFramebufferSizeCallback(window, cb::onResize);

	// DEBUG ///////////////////////////////////////////////////////////////////

	Shader shader("../resources/shaders/vertex.glsl", "../resources/shaders/fragment.glsl");

	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	VertexArray vao;
	VertexBuffer vbo;

	vao.bind();
	vbo.bind();

	vbo.setData(vertices, sizeof(vertices));
	vao.setAttribPointer(0, 3, 6, 0);
	vao.setAttribPointer(1, 3, 6, 3);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		vao.draw(3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	///////////////////////////////////////////////////////////////////////////

	return true;
}

void Engine::clearWindow(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
}
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

float Engine::getAspectRatio() {
	return static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
}

GLuint Engine::getWindowWidth() {
	return windowWidth;
}

GLuint Engine::getWindowHeight() {
	return windowHeight;
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

void Engine::setupGl() {
	glEnable(GL_DEPTH_TEST);
}

bool Engine::isRunning() {
	return !glfwWindowShouldClose(window);
}

void Engine::clearWindow(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

	// DEBUG ///////////////////////////////////////////////////////////////////
	Vertex vertices[] = {
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)},
		{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)},
		{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)},
		{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)},
		{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)},
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)},

		{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},
		{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},
		{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},
		{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},
		{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},
		{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f)},

		{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
		{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
		{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},
		{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f)},

		{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},
		{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},
		{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},
		{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},
		{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},
		{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f)},

		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f)},
		{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f)},
		{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f)},
		{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f)},
		{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f)},
		{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f)},

		{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)},
		{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)},
		{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)},
		{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)},
		{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)},
		{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f)}
	};

	Shader lightingShader(
		"../resources/shaders/basic_vertex.glsl", 
		"../resources/shaders/basic_fragment.glsl"
	);

	VertexArray vao;
	VertexBuffer vbo;
	
	vao.bind();
	vbo.bind();

	std::vector<Vertex> vec(vertices, vertices + sizeof(vertices) / sizeof(vertices[0]));

	vbo.setData(vec);
	vao.setAttribPointer(0, 3, 0);
	vao.setAttribPointer(1, 3, offsetof(Vertex, normal));

	Camera camera(3.0f, 3.0f, 3.0f);
	camera.setProjection(Camera::PERSPECTIVE, 0.1f, 100.0f);
	camera.lookAt(0.0f, 0.0f, 0.0f);

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	while (isRunning()) {
		clearWindow(0.3f, 0.3f, 0.3f, 1.0f);

		lightingShader.use();
		lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("lightPos", lightPos);
		lightingShader.setVec3("viewPos", camera.getPosition());

		camera.update(&lightingShader);
		glm::mat4 model = glm::mat4(1.0f);
		lightingShader.setMat4("model", model);

		vao.bind();
		vao.drawVertices(36);

		endFrame();
	}

	///////////////////////////////////////////////////////////////////////////

	return true;
}
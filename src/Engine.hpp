#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Engine {
public:
	using WindowMode = enum WINDOW_MODE { DEFAULT, FULLSCREEN };

private:
	Engine();
	~Engine();
	Engine(const Engine&);
	void operator=(const Engine&);

	int windowWidth;
	int windowHeight;
	const char* windowTitle;
	WindowMode windowMode;
	GLFWwindow* window;

public:
	static Engine& get();
	Engine& setWindowDimensions(int windowWidth, int windowHeight);
	Engine& setWindowTitle(const char* title);
	Engine& setWindowMode(WindowMode mode);
	bool buildWindow();
	void clearWindow(GLfloat r = 0.0f, GLfloat g = 0.0f, GLfloat b = 0.0f, GLfloat a = 1.0f);
};
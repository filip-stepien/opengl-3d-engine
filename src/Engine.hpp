#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "callbacks.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"
#include "Texture.hpp"

class Engine {
public:
	using WindowMode = enum WINDOW_MODE { DEFAULT, FULLSCREEN };

private:
	Engine();
	~Engine();
	Engine(const Engine&);
	void operator=(const Engine&);

	GLuint windowWidth;
	GLuint windowHeight;
	const char* windowTitle;
	WindowMode windowMode;
	GLFWwindow* window;
	float deltaTime;

	void setWindowHints();
	void createWindow();
	void initGlfw();
	void initGlad();
	void setViewport();
	void endFrame();
	void updateDeltaTime();

public:
	static Engine& get();
	Engine& setWindowDimensions(int windowWidth, int windowHeight);
	Engine& setWindowTitle(const char* title);
	Engine& setWindowMode(WindowMode mode);
	bool build();

	float getDeltaTime();
	float getAspectRatio();

	bool isRunning();
	void clearWindow(GLfloat r = 0.0f, GLfloat g = 0.0f, GLfloat b = 0.0f, GLfloat a = 1.0f);
	void onResize(GLFWwindow* window, int width, int height);
};
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <set>

#include "callbacks.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "App.hpp"
#include "Cube.hpp"
#include "Sphere.hpp"

class Engine {
public:
	using WindowMode = enum WINDOW_MODE { DEFAULT, FULLSCREEN };

private:
	using Handler = void (App::*)();

	Engine();
	~Engine();
	Engine(const Engine&);
	void operator=(const Engine&);

	App* app;
	Camera* camera;
	GLuint windowWidth;
	GLuint windowHeight;
	const char* windowTitle;
	WindowMode windowMode;
	GLFWwindow* window;
	std::vector<Shape*> shapePipeline;
	std::vector<Light*> lightPipeline;

	GLdouble currentFrame;
	GLdouble lastFrame;
	GLdouble deltaTime;

	bool mouseCapture;
	bool maximized;
	bool fullscreen;

	Handler keyClickHandlers[GLFW_KEY_LAST];
	Handler keyReleaseHandlers[GLFW_KEY_LAST];
	Handler mouseClickHandlers[GLFW_MOUSE_BUTTON_LAST];
	Handler mouseReleaseHandlers[GLFW_MOUSE_BUTTON_LAST];
	Handler mouseMoveHandler;

	void setWindowHints();
	void createWindow();
	void initGlfw();
	void initGlad();
	void checkAppState();
	void setViewport();
	void setupGl();
	void updateDeltaTime();
	void setCallbacks();
	void endFrame();

	friend class App;

public:
	static Engine& get();
	Engine& setWindowDimensions(int windowWidth, int windowHeight);
	Engine& setWindowTitle(const char* title);
	Engine& setWindowMode(WindowMode mode);
	Engine& setApp(App* app);
	Engine& setCamera(Camera* camera);
	Engine& setMouseCapture(bool mouseCapture);
	Engine& setWindowMaximized(bool maximized);
	Engine& setWindowFullscreen(bool fullscreen);
	bool build();

	float getAspectRatio();
	GLuint getWindowWidth();
	GLuint getWindowHeight();
	const char* getWindowTitle();
	WindowMode getWindowMode();
	GLFWwindow* getWindow();
	App* getApp();
	Camera* getCamera();
	GLdouble getDeltaTime();

	void handleKeyAction(int key, int action);
	void handleButtonAction(int button, int action);
	void handleMouseMove();

	void addToShapePipeline(Shape* shape);
	void addToLightPipeline(Light* light);

	bool isRunning();
	void close();
	void clearWindow(GLfloat r = 0.0f, GLfloat g = 0.0f, GLfloat b = 0.0f, GLfloat a = 1.0f);
	void onResize(GLFWwindow* window, int width, int height);
};
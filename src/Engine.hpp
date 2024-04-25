#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <functional>

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
#include "FrameBuffer.hpp"

class Engine {
public:
	using WindowMode = enum WINDOW_MODE { DEFAULT, FULLSCREEN };

private:
	using Handler = void (App::*)();

	Engine();
	~Engine();
	Engine(const Engine&);
	void operator=(const Engine&);

	App* app { nullptr };
	Camera* camera { nullptr };
	GLuint windowWidth = 800;
	GLuint windowHeight = 600;
	const char* windowTitle = nullptr;
	WindowMode windowMode = DEFAULT;
	GLFWwindow* window = nullptr;
	std::vector<Light*> lights = {};

	GLdouble currentFrame { 0 };
	GLdouble lastFrame { 0 };
	GLdouble deltaTime { 0 };

	bool maximized { false };
	bool fullscreen { false };
    bool mouseCapture { true };

    int mouseX;
    int mouseY;

	Handler keyClickHandlers[GLFW_KEY_LAST] = { nullptr };
	Handler keyReleaseHandlers[GLFW_KEY_LAST] = { nullptr };
	Handler mouseClickHandlers[GLFW_MOUSE_BUTTON_LAST] = { nullptr };
	Handler mouseReleaseHandlers[GLFW_MOUSE_BUTTON_LAST] = { nullptr };
	Handler mouseMoveHandler = nullptr;

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
	void handleMouseMove(double mouseX, double mouseY);

	void addLight(Light* light);

	bool isRunning();
	void close();
	void clearWindow(GLfloat r = 0.0f, GLfloat g = 0.0f, GLfloat b = 0.0f, GLfloat a = 1.0f);
	void onResize(GLFWwindow* window, int width, int height);
};

#endif
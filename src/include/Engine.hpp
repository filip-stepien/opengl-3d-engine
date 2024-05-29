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
#include "Text2D.hpp"
#include "Model.hpp"
#include "Plane3D.hpp"

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

	std::vector<Light*> lights {};
    std::vector<Mesh*> meshes {};
    std::vector<Text2D*> texts {};

	GLdouble currentFrame { 0 };
	GLdouble lastFrame { 0 };
	GLdouble deltaTime { 0 };
    unsigned long long framesCount { 0 };

	bool maximized { false };
	bool fullscreen { false };
    bool mouseCapture { true };

    GLuint pixelX { 0 };
    GLuint pixelY { 0 };
    PixelInfo pixelInfo { 0 };

	Handler keyClickHandlers[GLFW_KEY_LAST] = { nullptr };
	Handler keyReleaseHandlers[GLFW_KEY_LAST] = { nullptr };
	Handler mouseClickHandlers[GLFW_MOUSE_BUTTON_LAST] = { nullptr };
	Handler mouseReleaseHandlers[GLFW_MOUSE_BUTTON_LAST] = { nullptr };
	Handler mouseMoveHandler = nullptr;

	void setWindowHints();
	void createWindow();
	void initGlfw();
	void initGlad();
    void initGlText();
	void checkAppState();
	void setViewport();
	void setupGl();
	void updateDeltaTime();
	void setCallbacks();
	void endFrame();
    void initEngineObjects();
    void updateEngineObjects(Shader& shader);
    void drawEngineObjects(Shader& shader);
    void drawText();
    void updatePixelInfo(FrameBuffer& fbo, Shader& shader);

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
    unsigned long long getFramesCount();

    void watchPixel(GLuint x, GLuint y);
    PixelInfo getPixelInfo();

	void handleKeyAction(int key, int action);
	void handleButtonAction(int button, int action);
	void handleMouseMove();

	void addLight(Light* light);
    void addMesh(Mesh* mesh);
    void addText(Text2D* text);

	bool isRunning();
	void close();
	void clearWindow(GLfloat r = 0.0f, GLfloat g = 0.0f, GLfloat b = 0.0f, GLfloat a = 1.0f);
    void clearBuffer();
    void resetFramesCount();
	void onResize(GLFWwindow* window, int width, int height);
};

#endif
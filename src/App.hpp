#ifndef APP_H
#define APP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class App {
public:
    using Handler = void (App::*)();

    virtual void setup() {};
	virtual void loop() {};

	void onKeyClick(int key, Handler handler);
    void onKeyRelease(int key, Handler handler);
    void onMouseClick(int mouseButton, Handler handler);
    void onMouseRelease(int mouseButton, Handler handler);
    void onMouseMove(Handler handler);

    glm::vec2 getMousePosition();

    template <typename T>
    Handler getHandler(T handler) {
        return static_cast<Handler>(handler);
    }
};

#endif
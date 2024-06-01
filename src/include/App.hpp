#ifndef APP_H
#define APP_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

/**
 * @class App
 * @brief A wrapper for an Engine application.
 *
 * This class provides a basic structure for setting up, running, and
 * cleaning up the application, as well as handling input events.
 * Any app should inherit from this class.
 */
class App {
public:
    /// Type alias for a member function pointer that takes no arguments and returns void.
    using Handler = void (App::*)();

    /**
     * @brief Set up the application.
     *
     * This virtual method can be overridden by derived classes to perform
     * any necessary setup for the application.
     * Note that this method is called once before an applications starts.
     */
    virtual void setup() {};

    /**
     * @brief Main application loop.
     *
     * This virtual method can be overridden by derived classes to define
     * the main loop of the application. It executes once every frame.
     */
    virtual void loop() {};

    /**
     * @brief Clean up the application.
     *
     * This virtual method can be overridden by derived classes to perform
     * any necessary cleanup for the application.
     * It's called upon the exit of an application.
     */
    virtual void cleanup() {};

    /**
     * @brief Register a handler for a key press event.
     *
     * @param key The key code of the key press event.
     * @param handler The member function handler to be called.
     *
     * @note The `key` parameter follows GLFW key token constants.
     * See [keyboard key tokens](https://www.glfw.org/docs/3.3/group__keys).
     */
    void onKeyClick(int key, Handler handler);

    /**
     * @brief Register a handler for a key release event.
     *
     * @param key The key code of the key release event.
     * @param handler The member function handler to be called.
     *
     * @note The `key` parameter follows GLFW key token constants.
     * See [keyboard key tokens](https://www.glfw.org/docs/3.3/group__keys).
     */
    void onKeyRelease(int key, Handler handler);

    /**
     * @brief Register a handler for a mouse button click event.
     *
     * @param mouseButton The code of the mouse button click event.
     * @param handler The member function handler to be called.
     *
     * @note The `mouseButton` parameter follows GLFW mouse buttons constants.
     * See [mouse buttons](https://www.glfw.org/docs/3.3/group__buttons.html).
     */
    void onMouseClick(int mouseButton, Handler handler);

    /**
     * @brief Register a handler for a mouse button release event.
     *
     * @param mouseButton The code of the mouse button release event.
     * @param handler The member function handler to be called.
     *
     * @note The `mouseButton` parameter follows GLFW mouse buttons constants.
     * See [mouse buttons](https://www.glfw.org/docs/3.3/group__buttons.html).
     */
    void onMouseRelease(int mouseButton, Handler handler);

    /**
     * @brief Register a handler for a mouse movement event.
     *
     * @param handler The member function handler to be called.
     *
     * @note It can be either a function or a method returned from a getHandler(T handler) call.
     */
    void onMouseMove(Handler handler);

    /**
     * @brief Get the current mouse position.
     *
     * @return The current mouse position as a glm::vec2.
     */
    glm::vec2 getMousePosition();

    /**
     * @brief Template method to cast any member function pointer of a derived class to a Handler type.
     *
     * @tparam T The type of the member function pointer.
     * @param handler The member function pointer to be cast.
     * @return The cast member function pointer as a Handler type.
     */
    template <typename T>
    Handler getHandler(T handler) {
        return static_cast<Handler>(handler);
    }
};

#endif

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine.hpp"

/**
 * @brief Callback functions used in the Engine.
 *
 * @note These functions are used to register GLFW handlers.
 *       For detailed explanation of funtions' parameters see
 *       [GLFW input handling](https://www.glfw.org/docs/3.0/group__input.html).
 */
namespace engine::cb {
    /**
     * @brief Callback function for window resize event.
     *
     * This function is called when the window is resized.
     *
     * @param window The GLFWwindow object.
     * @param width The new width of the window.
     * @param height The new height of the window.
     */
    void onResize(GLFWwindow* window, int width, int height);

    /**
     * @brief Callback function for keyboard action event.
     *
     * This function is called when a keyboard key is pressed or released.
     *
     * @param window The GLFWwindow object.
     * @param key The keyboard key that was pressed or released
     *            (accepts [GLFW key tokens](https://www.glfw.org/docs/3.3/group__keys.html)).
     * @param scancode The scancode of the key.
     * @param action The action taken. See [key actions](https://www.glfw.org/docs/3.3/input_guide.html#input_key).
     * @param mods Bit field describing which modifier keys were held down
     *             See [modifier bits](https://www.glfw.org/docs/3.3/group__mods.html).
     */
    void onKeyAction(GLFWwindow* window, int key, int scancode, int action, int mods);

    /**
     * @brief Callback function for mouse button action event.
     *
     * This function is called when a mouse button is pressed or released.
     *
     * @param window The GLFWwindow object.
     * @param key The keyboard key that was pressed or released
     *            (accepts [GLFW key tokens](https://www.glfw.org/docs/3.3/group__keys.html)).
     * @param scancode The scancode of the key.
     * @param action The action taken. See [key actions](https://www.glfw.org/docs/3.3/input_guide.html#input_key).
     * @param mods Bit field describing which modifier keys were held down.
     *             See [modifier bits](https://www.glfw.org/docs/3.3/group__mods.html).
     */
    void onButtonAction(GLFWwindow* window, int button, int action, int mods);

    /**
     * @brief Callback function for mouse movement event.
     *
     * This function is called when the mouse cursor is moved.
     *
     * @param window The GLFWwindow object.
     * @param xpos The x-coordinate of the cursor.
     * @param ypos The y-coordinate of the cursor.
     */
    void onMouseMove(GLFWwindow* window, double xpos, double ypos);
}

#endif

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

/**
 * @class Engine
 * @brief The main engine for the application.
 *
 * Class follows singleton pattern.
 * There cannot be more than one instance representing Engine in the program.
 * It cannot be instanced like a normal object, if you need access the instance
 * it should be done by calling get() static method.
 *
 * It also utilizes builder pattern.
 * For a convenience every setter method returns the same Engine instance.
 * You can chain setters like this:
 * @code
 * Engine::get()
 *   .setWindowDimensions(800, 800)
 *   .setWindowTitle("Some title")
 *   .setWindowMaximized(true)
 *   .setMouseCapture(true)
 *   .setApp(&someApp)
 *   .setCamera(&someCamera)
 *   .build();
 * @endcode
 *
 * @note Every build operation should end with build() method call!
 */
class Engine {
public:
    /// Available window modes.
    using WindowMode = enum WINDOW_MODE {
        DEFAULT,
        FULLSCREEN
    };

private:
    /**
     * @brief Type definition for key/mouse handler functions.
     */
    using Handler = void (App::*)();

    /**
     * @brief Constructor for the Engine class.
     *
     * It's explicitly marked as private to prevent direct construction call.
     */
    Engine();

    /**
     * @brief Destructor for the Engine class.
     *
     * Terminates window and related objects.
     */
    ~Engine();

    /// Pointer to the application instance.
    App* app { nullptr };

    /// Pointer to the camera instance.
    Camera* camera { nullptr };

    /// Width of the window.
    GLuint windowWidth { 800 };

    /// Height of the window.
    GLuint windowHeight { 600 };

    /// Title of the window.
    const char* windowTitle { nullptr };

    /// Current window mode.
    WindowMode windowMode { DEFAULT };

    /// Pointer to the GLFW window instance.
    GLFWwindow* window { nullptr };

    /// Vector of light objects present in the scene.
    std::vector<Light*> lights {};

    /// Vector of mesh objects present in the scene.
    std::vector<Mesh*> meshes {};

    /// Vector of 2D text objects present in the scene.
    std::vector<Text2D*> texts {};

    /// Current frame time.
    GLdouble currentFrame { 0 };

    /// Last frame time.
    GLdouble lastFrame { 0 };

    /// Delta time between frames.
    GLdouble deltaTime { 0 };

    /// Frame count.
    unsigned long long framesCount { 0 };

    /// Flag indicating if the window is maximized.
    bool maximized { false };

    /// Flag indicating if the window is fullscreen.
    bool fullscreen { false };

    /// Flag indicating if mouse capture is enabled.
    bool mouseCapture { true };

    /// X coordinate of the watched pixel. See watchPixel().
    GLuint pixelX { 0 };

    /// Y coordinate of the watched pixel. See watchPixel().
    GLuint pixelY { 0 };

    /// Information of the watched pixel. See watchPixel().
    PixelInfo pixelInfo { 0 };

    /// Array of key click handlers,
    /// [key token](https://www.glfw.org/docs/3.3/group__keys.html) corresponds to index.
    Handler keyClickHandlers[GLFW_KEY_LAST] = { nullptr };

    /// Array of key release handlers,
    /// [key token](https://www.glfw.org/docs/3.3/group__keys.html) corresponds to index.
    Handler keyReleaseHandlers[GLFW_KEY_LAST] = { nullptr };

    /// Array of mouse click handlers
    /// [mouse button](https://www.glfw.org/docs/3.3/group__buttons.html) corresponds to index.
    Handler mouseClickHandlers[GLFW_MOUSE_BUTTON_LAST] = { nullptr };

    /// Array of mouse release handlers
    /// [mouse button](https://www.glfw.org/docs/3.3/group__buttons.html) corresponds to index.
    Handler mouseReleaseHandlers[GLFW_MOUSE_BUTTON_LAST] = { nullptr };

    /// Mouse move handler
    Handler mouseMoveHandler = nullptr;

    /**
     * @brief Sets the window hints for GLFW.
     *
     * Context version, OpenGL profile, etc.
     */
    void setWindowHints();

    /**
     * @brief Creates the GLFW window.
     */
    void createWindow();

    /**
     * @brief Initializes GLFW.
     */
    void initGlfw();

    /**
     * @brief Initializes GLAD.
     */
    void initGlad();

    /**
     * @brief Initializes the OpenGL text rendering lib.
     */
    void initGlText();

    /**
     * @brief Checks the application state.
     *
     * If an error occurred during initialization, the window is terminated.
     */
    void checkAppState();

    /**
     * @brief Sets the viewport for OpenGL.
     */
    void setViewport();

    /**
     * @brief Sets up the OpenGL context.
     *
     * Bundles all glEnable() calls and other configurations.
     */
    void setupGl();

    /**
     * @brief Updates the delta time between frames.
     */
    void updateDeltaTime();

    /**
     * @brief Sets the callback functions for GLFW.
     */
    void setCallbacks();

    /**
     * @brief Ends the current frame.
     *
     * It consist of swapping buffers, polling input events
     * and incrementing total number of frames.
     */
    void endFrame();

    /**
     * @brief Initializes engine objects.
     *
     * The initialize() method is called for each object present
     * in the meshes vector.
     */
    void initEngineObjects();

    /**
     * @brief Updates engine objects with the given shader.
     * @param shader The shader to use for updating the objects.
     *
     * The update() method is called for light objects and camera,
     * passing given shader as a parameter. It's also calling
     * loop() method from an App object, so actual drawing starts
     * from here.
     */
    void updateEngineObjects(Shader& shader);

    /**
     * @brief Draws engine objects with the given shader.
     * @param shader The shader to use for drawing the objects.
     *
     * The draw() method is called for each object present
     * in the meshes vector, passing given shader as a parameter.
     */
    void drawEngineObjects(Shader& shader);

    /**
     * @brief Draws 2D text on the screen.
     *
     * Draws each text object from the texts vectors.
     */
    void drawText();

    /**
     * @brief Updates the pixel information from the framebuffer.
     * @param fbo The framebuffer object to read from.
     * @param shader The shader to use for reading pixel information.
     */
    void updatePixelInfo(FrameBuffer& fbo, Shader& shader);

    /// App is considered a friend class in order to access handler tables.
    friend class App;

public:
    /**
     * @brief Copy constructor (deleted).
     *
     * Singletons can't be cloneable.
     */
    Engine(const Engine&) = delete;

    /**
     * @brief Assignment operator (deleted).
     *
     * Singletons can't be assignable.
     */
    void operator=(const Engine&) = delete;

    /**
     * @brief Gets the singleton instance of the Engine.
     * @return The singleton instance of the Engine.
     *
     * See the Engine class description.
     */
    static Engine& get();

    /**
     * @brief Sets the window dimensions.
     * @param windowWidth The width of the window.
     * @param windowHeight The height of the window.
     * @return Reference to the Engine instance.
     */
    Engine& setWindowDimensions(int windowWidth, int windowHeight);

    /**
     * @brief Sets the window title.
     * @param title The title of the window.
     * @return Reference to the Engine instance.
     */
    Engine& setWindowTitle(const char* title);

    /**
     * @brief Sets the window mode.
     * @param mode The mode of the window.
     * @return Reference to the Engine instance.
     */
    Engine& setWindowMode(WindowMode mode);

    /**
     * @brief Sets the application instance.
     * @param app The application instance.
     * @return Reference to the Engine instance.
     */
    Engine& setApp(App* app);

    /**
     * @brief Sets the camera instance.
     * @param camera The camera instance.
     * @return Reference to the Engine instance.
     */
    Engine& setCamera(Camera* camera);

    /**
     * @brief Enables or disables mouse capture.
     * @param mouseCapture Whether to enable mouse capture.
     * @return Reference to the Engine instance.
     */
    Engine& setMouseCapture(bool mouseCapture);

    /**
     * @brief Sets the window maximized state.
     * @param maximized Whether the window is maximized.
     * @return Reference to the Engine instance.
     */
    Engine& setWindowMaximized(bool maximized);

    /**
     * @brief Sets the window fullscreen state.
     * @param fullscreen Whether the window is fullscreen.
     * @return Reference to the Engine instance.
     */
    Engine& setWindowFullscreen(bool fullscreen);

    /**
     * @brief Builds the engine.
     *
     * Each builder creation should finalize with this method.
     * See Engine class description.
     *
     * @return True if the engine was built successfully, false otherwise.
     */
    bool build();

    /**
     * @brief Gets the aspect ratio of the window.
     * @return The aspect ratio of the window.
     */
    float getAspectRatio();

    /**
     * @brief Gets the window width.
     * @return The width of the window.
     */
    GLuint getWindowWidth();

    /**
     * @brief Gets the window height.
     * @return The height of the window.
     */
    GLuint getWindowHeight();

    /**
     * @brief Gets the window title.
     * @return The title of the window.
     */
    const char* getWindowTitle();

    /**
     * @brief Gets the window mode.
     * @return The mode of the window.
     */
    WindowMode getWindowMode();

    /**
     * @brief Gets the GLFW window instance.
     * @return Pointer to the GLFW window instance.
     */
    GLFWwindow* getWindow();

    /**
     * @brief Gets the application instance.
     * @return Pointer to the application instance.
     */
    App* getApp();

    /**
     * @brief Gets the camera instance.
     * @return Pointer to the camera instance.
     */
    Camera* getCamera();

    /**
     * @brief Gets the delta time between frames.
     * @return The delta time between frames (in seconds).
     */
    GLdouble getDeltaTime();

    /**
     * @brief Gets the frame count.
     * @return The frame count.
     *
     * It's the total number of frames since the applications has started.
     */
    unsigned long long getFramesCount();

    /**
     * @brief Sets the pixel to watch.
     * @param x The X coordinate of the pixel.
     * @param y The Y coordinate of the pixel.
     *
     * The information about currently watched pixel can be
     * accessed through getPixelInfo() method.
     */
    void watchPixel(GLuint x, GLuint y);

    /**
     * @brief Gets the watched pixel information.
     * @return The watched pixel information.
     */
    PixelInfo getPixelInfo();

    /**
     * @brief Invokes corresponding handler bound to a key.
     * @param key The key code.
     * @param action The key action.
     *
     * See [key input](https://www.glfw.org/docs/3.3/input_guide.html#input_key).
     */
    void handleKeyAction(int key, int action);

    /**
     * @brief Invokes corresponding handler bound to a mouse button.
     * @param button The button code.
     * @param action The button action.
     *
     * See [mouse input](https://www.glfw.org/docs/3.3/input_guide.html#input_mouse_button).
     */
    void handleButtonAction(int button, int action);

    /**
     * @brief Invokes mouse movement handler.
     */
    void handleMouseMove();

    /**
     * @brief Adds a light to the rendering queue.
     * @param light Pointer to the light object.
     */
    void addLight(Light* light);

    /**
     * @brief Adds a mesh to the rendering queue.
     * @param mesh Pointer to the mesh object.
     */
    void addMesh(Mesh* mesh);

    /**
     * @brief Adds 2D text to the rendering queue.
     * @param text Pointer to the 2D text object.
     */
    void addText(Text2D* text);

    /**
     * @brief Checks if the engine is running.
     * @return True if the engine is running, false otherwise.
     */
    bool isRunning();

    /**
     * @brief Closes the engine.
     */
    void close();

    /**
     * @brief Clears the window with the specified RGBA color.
     * @param r Red component of the color.
     * @param g Green component of the color.
     * @param b Blue component of the color.
     * @param a Alpha component of the color.
     *
     * Defaults to black: (0, 0, 0, 1).
     */
    void clearWindow(GLfloat r = 0.0f, GLfloat g = 0.0f, GLfloat b = 0.0f, GLfloat a = 1.0f);

    /**
     * @brief Clears the window framebuffer.
     */
    void clearBuffer();

    /**
     * @brief Resets the frame count.
     */
    void resetFramesCount();

    /**
     * @brief Handles window resize events.
     * @param window Pointer to the GLFW window instance.
     * @param width The new width of the window.
     * @param height The new height of the window.
     *
     * The main purpose of handling resize event is to dynamically
     * change the viewport of the window to prevent stretching.
     */
    void onResize(GLFWwindow* window, int width, int height);
};

#endif

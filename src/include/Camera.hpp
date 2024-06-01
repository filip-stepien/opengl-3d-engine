#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <limits>
#include <cmath>
#include <algorithm>
#include "Updatable.hpp"
#include "Transformable.hpp"

/**
 * @class Camera
 * @brief A camera which makes an eye of the 3D space.
 */
class Camera : public Updatable, public Transformable {
public:
    /// Camera projection types.
    using Projection = enum PROJECTION {
        PERSPECTIVE,
        ORTHO
    };

private:
    /// Current projection type.
    Projection projection { PERSPECTIVE };

    /// Near clipping plane.
    GLfloat near { 0.1f };

    /// Far clipping plane.
    GLfloat far { 100.0f };

    /// Field of view.
    GLfloat fov { 45.0f };

    /// Flag for first mouse interaction.
    bool firstMouse { true };

    /// Current mouse X position.
    GLfloat mouseX { 0 };

    /// Current mouse Y position.
    GLfloat mouseY { 0 };

    /// Last X position of the mouse.
    GLfloat lastX { 0.0f };

    /// Last Y position of the mouse.
    GLfloat lastY { 0.0f };

    /// Flag for enabling camera movement.
    bool movementEnabled { true };

    /// Yaw angle.
    GLfloat yaw { -90.0f };

    /// Pitch angle.
    GLfloat pitch { 0.0f };

    /// Mouse sensitivity.
    GLfloat sensitivity { 0.1f };

    /// Zoom level.
    GLfloat zoom { 45.0f };

    /// Movement speed.
    GLfloat speed { 2.5f };

    /// Initial focus point.
    glm::vec3 initialFocus { 0.0f };

    /// Front vector.
    glm::vec3 front { 0.0f, 0.0f, -1.0f };

    /// Up vector.
    glm::vec3 up { 0.0f, 1.0f, 0.0f };

    /// Right vector.
    glm::vec3 right { 0.0f, 0.0f, 0.0f };

    /// Flag for locking the Y-axis.
    bool yAxisLocked { false };

    /// Restrict movement in X-axis.
    GLfloat restrictX { std::numeric_limits<float>::max() };

    /// Restrict movement in Y-axis.
    GLfloat restrictY { std::numeric_limits<float>::max() };

    /// Restrict movement in Z-axis.
    GLfloat restrictZ { std::numeric_limits<float>::max() };

    /// View matrix used in shader.
    glm::mat4 viewMatrix { glm::mat4(1.0f) };

    /// Projection matrix used in shader.
    glm::mat4 projectionMatrix { glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f) };

    /**
     * @brief Updates the camera's yaw and pitch angles
     * for the initial focus.
     */
    void updateFocus();

    /**
     * @brief Updates the camera's front and right vectors for
     * the next iteration of calculations.
     */
    void updateVectors();

    /**
     * @brief Processes the camera's movement.
     *
     * It checks for pressing WSAD keys and calls processKeyboard()
     * with corresponding direction.
     */
    void processMovement();

    /**
     * @brief Restricts the camera's movement.
     *
     * It clamps camera's position to the restrictX, restrictY,
     * and restrictZ bounding box.
     */
    void restrictMovement();

    /**
     * @brief Resets the mouse position.
     *
     * Prevents camera returning to previous position on mouse move
     * after changing cursor position.
     */
    void resetMousePosition();

public:
    /// Camera movement directions.
    using Direction = enum DIRECTION {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    /**
     * @brief Sets the yaw angle.
     * @param yaw The new yaw angle in degrees.
     */
    void setYaw(GLfloat yaw);

    /**
     * @brief Sets the pitch angle.
     * @param pitch The new pitch angle in degrees.
     */
    void setPitch(GLfloat pitch);

    /**
     * @brief Sets the movement speed.
     * @param speed The new movement speed.
     */
    void setSpeed(GLfloat speed);

    /**
     * @brief Sets the mouse sensitivity.
     * @param sensitivity The new mouse sensitivity.
     */
    void setSensitivity(GLfloat sensitivity);

    /**
     * @brief Sets the zoom level.
     * @param zoom The new zoom level.
     */
    void setZoom(GLfloat zoom);

    /**
     * @brief Enables or disables camera movement.
     * @param enabled Whether movement is enabled.
     */
    void setMovementEnabled(bool enabled);

    /**
     * @brief Sets the initial focus point.
     *
     * It's the point the camera will be looking at the start of the application.
     *
     * @param initalFocus The new initial focus point.
     */
    void setInitialFocus(glm::vec3 initalFocus);

    /**
     * @brief Sets the initial focus point.
     *
     * It's the point the camera will be looking at the start of the application.
     *
     * @param x The X coordinate.
     * @param y The Y coordinate.
     * @param z The Z coordinate.
     */
    void setInitialFocus(GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief Sets the camera projection.
     * @param projection The new projection type.
     * @param near The near clipping plane.
     * @param far The far clipping plane.
     * @param fovDegrees The field of view in degrees.
     */
    void setProjection(Projection projection, GLfloat near, GLfloat far, GLfloat fovDegrees = 45.0f);

    /**
     * @brief Locks or unlocks the Y-axis.
     * @param locked Whether the Y-axis is locked.
     */
    void setYAxisLocked(bool locked);

    /**
     * @brief Sets the movement restriction box dimensions.
     *
     * @param sizeX The X dimension.
     * @param sizeY The Y dimension.
     * @param sizeZ The Z dimension.
     *
     * @note Bounding box is calulated in both directions from the (0, 0, 0) point.
     * For example, if the restrictX is 10.0, the camera's position will be clamped
     * to values from -10.0 to 10.0.
     */
    void setRestrictMovementBox(GLfloat sizeX, GLfloat sizeY, GLfloat sizeZ);

    /**
     * @brief Sets the cursor position.
     * @param x The X position.
     * @param y The Y position.
     */
    void setCursorPosition(GLfloat x, GLfloat y);

    /**
     * @brief Disperses the initial focus.
     *
     * That means the camera will act like a mouse movement was performed.
     */
    void disperseInitialFocus();

    /**
     * @brief Gets the yaw angle.
     * @return The current yaw angle in degrees.
     */
    GLfloat getYaw();

    /**
     * @brief Gets the pitch angle.
     * @return The current pitch angle in degrees.
     */
    GLfloat getPitch();

    /**
     * @brief Gets the movement speed.
     * @return The current movement speed.
     */
    GLfloat getSpeed();

    /**
     * @brief Gets the mouse sensitivity.
     * @return The current mouse sensitivity.
     */
    GLfloat getSensitivity();

    /**
     * @brief Gets the zoom level.
     * @return The current zoom level.
     */
    GLfloat getZoom();

    /**
     * @brief Gets the projection matrix.
     * @return The current projection matrix.
     */
    glm::mat4 getProjectionMatrix();

    /**
     * @brief Gets the view matrix.
     * @return The current view matrix.
     */
    glm::mat4 getViewMatrix();

    /**
     * @brief Gets the initial focus point.
     *
     * It's the point the camera will be looking at the start of the application.
     *
     * @return The current initial focus point.
     */
    glm::vec3 getInitalFocus();

    /**
     * @brief Gets the raycast vector.
     *
     * It's the vector that corresponds to the camera's
     * looking direction.
     *
     * @return The current raycast vector.
     */
    glm::vec3 getRaycast();

    /**
     * @brief Checks if movement is enabled.
     * @return True if movement is enabled, false otherwise.
     */
    bool isMovementEnabled();

    /**
     * @brief Updates camera position based on given direction.
     *
     * @param direction The direction of movement.
     */
    void processKeyboard(Direction direction);

    /**
     * @brief Processes mouse positional parameters.
     * @param offsetX The offset in the X direction.
     * @param offsetY The offset in the Y direction.
     */
    void processMouse(GLfloat offsetX, GLfloat offsetY);

    /**
     * @brief Updates yaw and pitch based on mouse position.
     * @param mouseX The X position of the mouse.
     * @param mouseY The Y position of the mouse.
     */
    void handleMouseMove(double mouseX, double mouseY);

    /**
     * @brief Initializes the camera.
     *
     * It initializes projection and view matrices and camera's vectors.
     */
    void initialize();

    /**
     * @brief Updates the projection matrix.
     */
    void updateProjection();

    /**
     * @brief Updates the camera using the provided shader.
     *
     * It sets the view and projection matrices in the shader.
     *
     * @param shader The shader to use for updating.
     */
    void update(Shader& shader) override;
};

#endif

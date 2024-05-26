#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <limits>
#include <cmath>
#include <algorithm>
#include "Updatable.hpp"
#include "Transformable.hpp"

class Camera : public Updatable, public Transformable {
public:
	using Projection = enum PROJECTION { PERSPECTIVE, ORTHO };

private:
	Projection projection { PERSPECTIVE };

	GLfloat near { 0.1f };
	GLfloat far { 100.0f };
	GLfloat fov { 45.0f };

	bool firstMouse { true };
    GLfloat mouseX = { 0 };
    GLfloat mouseY = { 0 };
	GLfloat lastX { 0.0f };
	GLfloat lastY { 0.0f };

	bool movementEnabled { true };
	GLfloat yaw { -90.0f };
	GLfloat pitch { 0.0f };
	GLfloat sensitivity { 0.1f };
	GLfloat zoom { 45.0f };
    GLfloat speed { 2.5f };

    glm::vec3 initialFocus { 0.0f };
	glm::vec3 front { 0.0f, 0.0f, -1.0f };
	glm::vec3 up { 0.0f, 1.0f, 0.0f };
	glm::vec3 right { 0.0f, 0.0f, 0.0f };

    bool yAxisLocked { false };
    GLfloat restrictX { std::numeric_limits<float>::max() };
    GLfloat restrictY { std::numeric_limits<float>::max() };
    GLfloat restrictZ { std::numeric_limits<float>::max() };

	glm::mat4 viewMatrix { glm::mat4(1.0f) };
	glm::mat4 projectionMatrix { glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f) };

    void updateFocus();
    void updateVectors();
	void processMovement();
    void restrictMovement();
    void resetMousePosition();

public:
	using Direction = enum DIRECTION { FORWARD, BACKWARD, LEFT, RIGHT };

	void setYaw(GLfloat yaw);
	void setPitch(GLfloat pitch);
	void setSpeed(GLfloat speed);
	void setSensitivity(GLfloat sensitivity);
	void setZoom(GLfloat zoom);
	void setMovementEnabled(bool enabled);
	void setInitialFocus(glm::vec3 initalFocus);
	void setInitialFocus(GLfloat x, GLfloat y, GLfloat z);
	void setProjection(Projection projection, GLfloat near, GLfloat far, GLfloat fovDegrees = 45.0f);
    void setYAxisLocked(bool locked);
    void setRestrictMovementBox(GLfloat sizeX, GLfloat sizeY, GLfloat sizeZ);
    void setCursorPosition(GLfloat x, GLfloat y);
    void disperseInitialFocus();

	GLfloat getYaw();
	GLfloat getPitch();
	GLfloat getSpeed();
	GLfloat getSensitivity();
	GLfloat getZoom();
    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();
	glm::vec3 getInitalFocus();
    glm::vec3 getRaycast();
    glm::mat4 getBillboardMatrix(glm::vec3 position);
	bool isMovementEnabled();

	void processKeyboard(Direction direction);
	void processMouse(GLfloat offsetX, GLfloat offsetY);
	void handleMouseMove(double mouseX, double mouseY);

    void initialize();
    void updateProjection();
	void update(Shader& shader) override;
};

#endif
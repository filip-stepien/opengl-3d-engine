#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "EngineObject.hpp"

/**
 * @class Transformable
 * @brief Transformations for objects.
 *
 * @note Every type of transformation have a set method.
 * The difference is the set method will transform object once,
 * while the regular one will perform transformation every frame.
 */
class Transformable : public EngineObject {
protected:
    /// Model matrix for the object.
    glm::mat4 model { 1.0f };

    /// Position of the object.
    glm::vec3 position { 0.0f };

    /// Rotation factor of the object.
    glm::vec3 rotationFactor { 0.0f };

    /// Scale factor of the object.
    glm::vec3 scaleFactor { 1.0f };

    /// Matrix representing the position transformation.
    glm::mat4 positionMatrix { 1.0f };

    /// Matrix representing the rotation transformation.
    glm::mat4 rotationMatrix { 1.0f };

    /// Matrix representing the scale transformation.
    glm::mat4 scaleMatrix { 1.0f };

private:
    /**
     * @brief Applies the transformations to the model matrix.
     */
    void transform();

public:
    /**
     * @brief Gets the position of the object.
     * @return The position of the object.
     */
    glm::vec3 getPosition();

    /**
     * @brief Gets the rotation of the object.
     * @return The rotation of the object.
     */
    glm::vec3 getRotation();

    /**
     * @brief Gets the scale of the object.
     * @return The scale of the object.
     */
    glm::vec3 getScale();

    /**
     * @brief Sets the model matrix of the object.
     * @param model The new model matrix.
     */
    void setModelMatrix(glm::mat4 model);

    /**
     * @brief Sets the position of the object.
     * @param position The new position.
     */
    void setPosition(glm::vec3 position);

    /**
     * @brief Sets the position of the object.
     * @param x The X coordinate of the new position.
     * @param y The Y coordinate of the new position.
     * @param z The Z coordinate of the new position.
     */
    void setPosition(GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief Moves the object by the specified amount.
     * @param x The amount to move in the X direction.
     * @param y The amount to move in the Y direction.
     * @param z The amount to move in the Z direction.
     */
    void move(GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief Moves the object by the specified amount.
     * @param translation The translation vector.
     */
    void move(glm::vec3 translation);

    /**
     * @brief Sets the rotation of the object.
     * @param angleDegrees The angle of rotation in degrees.
     * @param x The X component of the rotation axis.
     * @param y The Y component of the rotation axis.
     * @param z The Z component of the rotation axis.
     */
    void setRotation(GLfloat angleDegrees, GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief Sets the rotation of the object.
     * @param angleDegrees The angle of rotation in degrees.
     * @param origin The rotation axis.
     */
    void setRotation(GLfloat angleDegrees, glm::vec3 origin);

    /**
     * @brief Rotates the object.
     * @param angleDegrees The angle of rotation in degrees.
     * @param x The X component of the rotation axis.
     * @param y The Y component of the rotation axis.
     * @param z The Z component of the rotation axis.
     */
    void rotate(GLfloat angleDegrees, GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief Rotates the object.
     * @param angleDegrees The angle of rotation in degrees.
     * @param origin The rotation axis.
     */
    void rotate(GLfloat angleDegrees, glm::vec3 origin);

    /**
     * @brief Sets the scale of the object.
     * @param x The scale factor in the X direction.
     * @param y The scale factor in the Y direction.
     * @param z The scale factor in the Z direction.
     */
    void setScale(GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief Sets the scale of the object.
     * @param scale The scale vector.
     */
    void setScale(glm::vec3 scale);

    /**
     * @brief Scales the object.
     * @param x The scale factor in the X direction.
     * @param y The scale factor in the Y direction.
     * @param z The scale factor in the Z direction.
     */
    void scale(GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief Scales the object.
     * @param scale The scale vector.
     */
    void scale(glm::vec3 scale);
};

#endif

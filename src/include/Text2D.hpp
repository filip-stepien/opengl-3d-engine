#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLT_IMPLEMENTATION
#include "gltext.h"
#include "EngineObject.hpp"

/**
 * @class Text2D
 * @brief Text rendered on the screen.
 */
class Text2D : public EngineObject {
private:
    /// Pointer to the GLT text object.
    GLTtext* text { nullptr };

    /// The content of the text.
    std::string content {};

    /// The position of the text on the screen.
    glm::vec2 position { 0.0f, 0.0f };

    /// The color of the text.
    glm::vec4 color { 1.0f, 1.0f, 1.0f, 1.0f };

    /// The scale of the text.
    float scale { 1.0f };

    /// Whether the text is centered.
    bool centered { false };

    /// Whether the text is visible.
    bool visible { true };

public:
    /**
     * @brief Constructor for Text2D.
     * Adds text to the rendering queue.
     */
    Text2D();

    /**
     * @brief Sets the content of the text.
     * @param textContent The new content of the text.
     */
    void setContent(std::string textContent);

    /**
     * @brief Sets the position of the text.
     * @param textPosition The new position of the text as a 2D vector.
     */
    void setPosition(glm::vec2 textPosition);

    /**
     * @brief Sets the position of the text.
     * @param x The X coordinate of the new position.
     * @param y The Y coordinate of the new position.
     */
    void setPosition(float x, float y);

    /**
     * @brief Sets the color of the text.
     * @param r The red component of the color.
     * @param g The green component of the color.
     * @param b The blue component of the color.
     * @param a The alpha component of the color.
     */
    void setColor(float r, float g, float b, float a);

    /**
     * @brief Sets the color of the text.
     * @param textColor The new color of the text as a 4D vector (r, g, b, a).
     */
    void setColor(glm::vec4 textColor);

    /**
     * @brief Sets the scale of the text.
     * @param textScale The new scale of the text.
     */
    void setScale(float textScale);

    /**
     * @brief Sets the GLT text object.
     * @param glText The GLT text object.
     */
    void setGLText(GLTtext* glText);

    /**
     * @brief Sets whether the text is centered.
     * @param textCentered Whether the text is centered.
     */
    void setCentered(bool textCentered);

    /**
     * @brief Sets whether the text is visible.
     * @param textVisible Whether the text is visible.
     */
    void setVisible(bool textVisible);

    /**
     * @brief Gets the content of the text.
     * @return The content of the text.
     */
    std::string getContent() const;

    /**
     * @brief Gets the position of the text.
     * @return The position of the text as a 2D vector.
     */
    glm::vec2 getPosition() const;

    /**
     * @brief Gets the color of the text.
     * @return The color of the text as a 4D vector (r, g, b, a).
     */
    glm::vec4 getColor() const;

    /**
     * @brief Gets the scale of the text.
     * @return The scale of the text.
     */
    float getScale() const;

    /**
     * @brief Gets the GLT text object.
     * @return The GLT text object.
     */
    GLTtext* getGLText() const;

    /**
     * @brief Checks if the text is centered.
     * @return True if the text is centered, false otherwise.
     */
    bool isCentered() const;

    /**
     * @brief Checks if the text is visible.
     * @return True if the text is visible, false otherwise.
     */
    bool isVisible() const;
};

#endif

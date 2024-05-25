#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLT_IMPLEMENTATION
#include "gltext.h"

class Text2D {
private:
    GLTtext* text { nullptr };
    std::string content {};
    glm::vec2 position { 200.0f, 200.0f };
    glm::vec4 color { 1.0f, 1.0f, 1.0f, 1.0f };
    float scale { 1.0f };
    bool centered { false };

public:
    Text2D();

    void setContent(std::string textContent);
    void setPosition(glm::vec2 textPosition);
    void setPosition(float x, float y);
    void setColor(float r, float g, float b, float a);
    void setColor(glm::vec4 textColor);
    void setScale(float textScale);
    void setGLText(GLTtext* glText);
    void setCentered(bool textCentered);

    std::string getContent() const;
    glm::vec2 getPosition() const;
    glm::vec4 getColor() const;
    float getScale() const;
    GLTtext* getGLText() const;
    bool isCentered() const;
};

#endif //TEXT_H

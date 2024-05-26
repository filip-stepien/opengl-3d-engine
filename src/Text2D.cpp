#include "Text2D.hpp"
#include "Engine.hpp"

Text2D::Text2D() {
    Engine::get().addText(this);
}

void Text2D::setContent(std::string textContent) {
    content = textContent;
}

void Text2D::setPosition(glm::vec2 textPosition) {
    position = textPosition;
}

void Text2D::setPosition(float x, float y) {
    position = { x, y };
}

void Text2D::setColor(float r, float g, float b, float a) {
    color = { r, g, b, a };
}

void Text2D::setColor(glm::vec4 textColor) {
    color = textColor;
}

void Text2D::setScale(float textScale) {
    scale = textScale;
}

void Text2D::setGLText(GLTtext* glText) {
    text = glText;
}

void Text2D::setCentered(bool textCentered) {
    centered = textCentered;
}

void Text2D::setVisible(bool textVisible) {
    visible = textVisible;
}

std::string Text2D::getContent() const {
    return content;
}

glm::vec2 Text2D::getPosition() const {
    return position;
}

glm::vec4 Text2D::getColor() const {
    return color;
}

float Text2D::getScale() const {
    return scale;
}

GLTtext* Text2D::getGLText() const {
    return text;
}

bool Text2D::isCentered() const {
    return centered;
}

bool Text2D::isVisible() const {
    return visible;
}


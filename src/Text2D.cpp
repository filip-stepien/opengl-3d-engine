#include "Text2D.hpp"

#include <utility>
#include "Engine.hpp"

engine::Text2D::Text2D() {
    Engine::get().addText(this);
}

void engine::Text2D::setContent(std::string textContent) {
    content = std::move(textContent);
}

void engine::Text2D::setPosition(glm::vec2 textPosition) {
    position = textPosition;
}

void engine::Text2D::setPosition(float x, float y) {
    position = { x, y };
}

void engine::Text2D::setColor(float r, float g, float b, float a) {
    color = { r, g, b, a };
}

void engine::Text2D::setColor(glm::vec4 textColor) {
    color = textColor;
}

void engine::Text2D::setScale(float textScale) {
    scale = textScale;
}

void engine::Text2D::setGLText(GLTtext* glText) {
    text = glText;
}

void engine::Text2D::setCentered(bool textCentered) {
    centered = textCentered;
}

void engine::Text2D::setVisible(bool textVisible) {
    visible = textVisible;
}

std::string engine::Text2D::getContent() const {
    return content;
}

glm::vec2 engine::Text2D::getPosition() const {
    return position;
}

glm::vec4 engine::Text2D::getColor() const {
    return color;
}

float engine::Text2D::getScale() const {
    return scale;
}

GLTtext* engine::Text2D::getGLText() const {
    return text;
}

bool engine::Text2D::isCentered() const {
    return centered;
}

bool engine::Text2D::isVisible() const {
    return visible;
}


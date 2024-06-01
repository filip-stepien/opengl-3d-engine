#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Shader.hpp"
#include "EngineObject.hpp"

/**
 * @class Drawable
 * @brief Abstract class representing a drawable object.
 */
class Drawable : public virtual EngineObject {
public:
    /**
     * @brief Draws the object using the provided shader.
     * @param shader The shader to be used for drawing.
     */
    virtual void draw(Shader& shader) {};

    /**
     * @brief Draws the object to a buffer using the provided shader.
     * @param shader The shader to be used for drawing to the buffer.
     */
    virtual void drawToBuffer(Shader& shader) {};
};

#endif

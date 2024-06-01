#pragma once

#include "Shader.hpp"
#include "EngineObject.hpp"

/**
 * @class Updatable
 * @brief Abstract class for updatable object.
 */
class Updatable : public virtual EngineObject {
public:
    /**
     * @brief Updates the object using the provided shader.
     * @param shader The shader to use for updating.
     */
    virtual void update(Shader& shader) {};

    /**
     * @brief Updates the object using the provided shader.
     *
     * When there's a set of elements to update in shader,
     * the index is used.
     *
     * @param shader The shader to use for updating.
     * @param index The index of an object.
     */
    virtual void update(Shader& shader, int index) {};
};

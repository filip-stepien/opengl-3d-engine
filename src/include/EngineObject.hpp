#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H

namespace engine {
    /**
     * @class EngineObject
     * @brief Base class for objects within the engine.
     */
    class EngineObject {
    protected:
        /// Unique identifier for the object.
        unsigned int uid;

        /**
         * @brief Gets the ID counter for generating unique IDs.
         * @return Reference to the static ID counter.
         */
        static unsigned int &getIDCounter();

    public:
        /**
         * @brief Constructor for EngineObject.
         * Initializes the unique identifier.
         */
        EngineObject();

        /**
         * @brief Gets the unique identifier of the object.
         * @return The unique identifier.
         */
        unsigned int getID();
    };
}

#endif

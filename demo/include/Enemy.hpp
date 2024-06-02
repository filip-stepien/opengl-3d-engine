#ifndef ENEMY_H
#define ENEMY_H

#include <glm/glm.hpp>
#include "Level.hpp"
#include "Asset.hpp"
#include "Random.hpp"

namespace demo {
    using namespace engine;

    const int ENEMY_COUNT = 8;
    const float ENEMY_MOV_SPEED = 3.0f;
    const float ENEMY_ROT_SPEED = 0.05f;
    const float ENEMY_TOUCH_RADIUS = 1.5f;

    class Enemy : public Asset {
    private:
        Model model;
        int spawnPosition;

        glm::vec3 const spawnPoints[VENT_COUNT] {
            { LEVEL_RADIUS + 2.0f, 0, 0 },
            { -LEVEL_RADIUS - 2.0f, 0, 0 },
            { 0, 0, LEVEL_RADIUS + 2.0f },
            { 0, 0, -LEVEL_RADIUS - 2.0f }
        };

        glm::vec3 const spawnDirections[VENT_COUNT] {
            { -1.0f, 0.0f, 0.0f },
            { 1.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, -1.0f },
            { 0.0f, 0.0f, 1.0f }
        };

        void updateRotation();
        void updatePosition();
        void setRandomSpawnPos();

    public:
        bool didCollide();
        void setInitialPosition();
        void resetPosition();
        void updateMovement();
        unsigned int getID();
        void create() override;
    };
}

#endif
#ifndef DEMO_H
#define DEMO_H

#include "Engine.hpp"
#include "Enemy.hpp"
#include "Level.hpp"
#include "Random.hpp"
#include "SceneManager.hpp"
#include "Gun.hpp"
#include "Scoreboard.hpp"

namespace demo {
    class Demo : public App {
        Engine& e = Engine::get();
        Scoreboard scoreboard;
        SceneManager sceneManager;
        Enemy enemies[ENEMY_COUNT];
        Level level;
        Gun gun;
        bool gameStarted { false };
        bool playerDead { false };

        void createMenu();
        void createEnemies();
        void updateEnemies();
        void handleInitialSpawn();
        void handleTouchCollision();
        void handleShot();
        void startGame();
        void restartGame();
        void endGame();
        void setup() override;
        void loop() override;
    };
}

#endif
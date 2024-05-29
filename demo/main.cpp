#include "Demo.hpp"

#include <cmath>
#include <random>

using namespace demo;

class Test : public App {
    static constexpr int ENEMY_COUNT = 8;
    static constexpr int VENT_COUNT = 4;
    static constexpr int WALL_COUNT = 4;
    static constexpr int LIGHT_COUNT = 2;
    static constexpr float INITIAL_SPAWN_RADIUS = 5.0f;
    static constexpr float LEVEL_RADIUS = 10.0f;

    static constexpr float ENEMY_MOV_SPEED = 3.0f;
    static constexpr float ENEMY_ROT_SPEED = 0.05f;
    static constexpr float ENEMY_TOUCH_RADIUS = 1.5f;

    Engine& e = Engine::get();
    Model dummyEnemy;
    Model enemies[ENEMY_COUNT];
    Text2D gameTitle;
    Text2D startTitle;
    Text2D scoreboard;
    Level level;
    Gun gun;

    unsigned int score { 0 };
    bool gameStarted { false };
    bool playerDead { false };

    glm::vec3 spawnPoints[VENT_COUNT] {
        { LEVEL_RADIUS + 2.0f, 0, 0 },
        { -LEVEL_RADIUS - 2.0f, 0, 0 },
        { 0, 0, LEVEL_RADIUS + 2.0f },
        { 0, 0, -LEVEL_RADIUS - 2.0f }
    };

    glm::vec3 spawnDirections[VENT_COUNT] {
        { -1.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, -1.0f },
        { 0.0f, 0.0f, 1.0f }
    };

    void createEnemies() {
        for (auto& enemy : enemies) {
            enemy.load("../resources/models/jbs.obj");
            enemy.setDiffuseTexture("../resources/textures/jbs-diffuse.png");
            enemy.setSpecularTexture("../resources/textures/jbs-specular.png");
            enemy.move(2.0f, 0.0f, 2.0f);
        }
    }

    void createScoreBoard() {
        scoreboard.setContent("Score: 0");
        scoreboard.setScale(4.0f);
        scoreboard.setPosition(50.0f, e.getWindowHeight() - 100.0f);
        scoreboard.setVisible(false);
    }

    void updateScore() {
        score++;
        scoreboard.setContent("Score: " + std::to_string(score));
    }

    void resetEnemyPos(unsigned int id) {
        for (int i = 0; i < ENEMY_COUNT; i++) {
            Mesh* mesh = enemies[i].getMeshes().at(0);

            if (mesh->getID() == id)
                mesh->setPosition(spawnPoints[i % VENT_COUNT]);
        }
    }

    void handleInitialSpawn() {
        for (auto& enemy : enemies) {
            enemy.setPosition(
                Random::randomFloat(INITIAL_SPAWN_RADIUS, 9.0f) * Random::randomDir(),
                0,
                Random::randomFloat(INITIAL_SPAWN_RADIUS, 9.0f) * Random::randomDir()
            );
        }
    }

    void updateEnemyRotation() {
        for (auto& enemy : enemies) {
            Mesh* mesh = enemy.getMeshes().at(0);
            glm::vec3 pos = mesh->getPosition();
            glm::vec3 cam = e.getCamera()->getPosition();
            glm::vec3 dist = cam - pos;
            float targetDegrees = glm::degrees(std::atan2(dist.x, dist.z));
            float oldDegrees = mesh->getRotation().y;
            float diff = targetDegrees - oldDegrees - 90.0f;

            if (diff < -180.0f) diff += 360.0f;
            if (diff > 180.0f) diff -= 360.0f;

            float change = std::lerp(0, diff, ENEMY_ROT_SPEED);
            float newDegrees = oldDegrees + change;

            enemy.setRotation(newDegrees, 0.0f, 1.0f, 0.0f);
        }
    }

    void updateEnemyMovement() {
        for (int i = 0; i < ENEMY_COUNT; i++) {
            Mesh* mesh = enemies[i].getMeshes().at(0);
            glm::vec3 pos = mesh->getPosition();
            glm::vec3 dir;

            if ((pos.x > LEVEL_RADIUS - 1.0f || pos.x < -LEVEL_RADIUS + 1.0f) ||
                (pos.z > LEVEL_RADIUS - 1.0f || pos.z < -LEVEL_RADIUS + 1.0f)) {
                dir = spawnDirections[i % VENT_COUNT];
            } else {
                dir = e.getCamera()->getPosition() - pos;
                dir = glm::normalize(dir);
                dir.y = 0.0f;
            }

            dir *= ENEMY_MOV_SPEED * e.getDeltaTime();
            enemies[i].setPosition(pos + dir);
        }
    }

    void handleShot() {
        if (playerDead)
            return;

        gun.setGunShot();

        for (auto& enemy : enemies) {
            unsigned int id = enemy.getMeshes().at(0)->getID();
            if (e.getPixelInfo().idObject == id) {
                resetEnemyPos(id);
                updateScore();
            }
        }
    }

    void handleTouchCollision() {
        for (auto& enemy : enemies) {
            Mesh* mesh = enemy.getMeshes().at(0);
            glm::vec3 camPos = e.getCamera()->getPosition();
            glm::vec3 enemyPos = mesh->getPosition();
            float dist = glm::length(camPos - enemyPos);

            if (dist < ENEMY_TOUCH_RADIUS)
                endGame();
        }
    }

    void createMenu() {
        e.getCamera()->move(-5.0f, 0.0f, 0.0f);

        dummyEnemy.load("../resources/models/jbs.obj");
        dummyEnemy.setDiffuseTexture("../resources/textures/jbs-diffuse.png");
        dummyEnemy.setSpecularTexture("../resources/textures/jbs-specular.png");
        dummyEnemy.setPosition(-8.0f, 0.0f, 0.0f);

        gun.setMenuView();

        gameTitle.setPosition(e.getWindowWidth() / 2, 200.0f);
        gameTitle.setContent("RoboShooter");
        gameTitle.setScale(8.0f);
        gameTitle.setCentered(true);

        startTitle.setPosition(e.getWindowWidth() / 2, e.getWindowHeight() / 2);
        startTitle.setContent("Press SPACE to START");
        startTitle.setScale(3.0f);
        startTitle.setCentered(true);
    }

    void displayMenu() {
        float x = sin(e.getFramesCount() / 500.0f) * e.getDeltaTime() * 0.5f;
        float z = cos(e.getFramesCount() / 500.0f) * e.getDeltaTime() * 0.7f;
        float textY = sin(e.getFramesCount() / 50.0f) * 30.0f;

        startTitle.setPosition(startTitle.getPosition().x, textY + 800.0f);

        if (!playerDead)
            e.getCamera()->move(x, 0.0f, z);
    }

    void restartGame() {
        playerDead = false;

        startTitle.setVisible(false);
        gameTitle.setVisible(false);

        gun.setCrosshairVisible(true);

        scoreboard.setPosition(50.0f, e.getWindowHeight() - 100.0f);
        scoreboard.setCentered(false);

        e.getCamera()->setPosition(0.0f, 1.0f, 0.0f);
        e.getCamera()->setMovementEnabled(true);

        score = -1;
        updateScore();

        handleInitialSpawn();
    }

    void startGame() {
        if (playerDead)
            restartGame();

        if (gameStarted)
            return;

        Camera* cam = e.getCamera();
        cam->setMovementEnabled(true);
        cam->setPosition(0.0f, 1.0f, 0.0f);
        cam->disperseInitialFocus();

        gun.setGameView();

        dummyEnemy.move(0.0f, 10.0f, 0.0f);

        startTitle.setVisible(false);
        gameTitle.setVisible(false);

        gun.setCrosshairVisible(true);

        scoreboard.setVisible(true);

        gameStarted = true;
        //handleInitialSpawn();
    }

    void endGame() {
        playerDead = true;

        gameTitle.setContent("Game over!");
        gameTitle.setVisible(true);
        startTitle.setVisible(true);
        gun.setCrosshairVisible(false);

        scoreboard.setCentered(true);
        scoreboard.setPosition(e.getWindowWidth() / 2, e.getWindowHeight() / 2);

        e.getCamera()->setMovementEnabled(false);
    }

    void setup() override {
        level.create();
        gun.create();

        createEnemies();
        createScoreBoard();
        createMenu();

        e.watchPixel(e.getWindowWidth() / 2, e.getWindowHeight() / 2);
        onMouseClick(GLFW_MOUSE_BUTTON_1, getHandler(&Test::handleShot));
        onKeyClick(GLFW_KEY_SPACE, getHandler(&Test::startGame));
    }

    void loop() override {
        if (gameStarted && !playerDead) {
            updateEnemyMovement();
            updateEnemyRotation();
            handleTouchCollision();

            gun.handleShotAnimation();
        } else {
            displayMenu();
        }
    }
};

int main() {
    Test app;

	Camera cam;
	cam.setProjection(Camera::PERSPECTIVE, 0.1f, 100.0f);
	cam.setPosition(0.0f, 1.0f, 0.0f);
	cam.setSpeed(2.5f);
	cam.setMovementEnabled(false);
    cam.setYAxisLocked(true);
    //cam.setRestrictMovementBox(19.5f, 19.5f, 19.5f);
    cam.setInitialFocus(-8.0f, 0.5f, 0.0f);

	Engine::get()
	.setWindowDimensions(800, 800)
	.setWindowTitle("RoboShooter")
	.setWindowMaximized(true)
	.setMouseCapture(true)
	.setApp(&app)
	.setCamera(&cam)
	.build();

	return 0;
}
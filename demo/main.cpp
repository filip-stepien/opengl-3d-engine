#include "Demo.hpp"

#include <cmath>
#include <random>

using namespace demo;

class Test : public App {
    Engine& e = Engine::get();
    Model dummyEnemy;
    Text2D gameTitle;
    Text2D startTitle;

    Enemy enemies[ENEMY_COUNT];
    Level level;
    Gun gun;
    Scoreboard scoreboard;

    bool gameStarted { false };
    bool playerDead { false };

    void handleShot() {
        if (playerDead)
            return;

        gun.setGunShot();

        for (auto& enemy : enemies) {
            if (e.getPixelInfo().idObject == enemy.getID()) {
                enemy.resetPosition();
                scoreboard.updateScore();
            }
        }
    }

    void handleTouchCollision() {
        for (auto& enemy : enemies) {
            if (enemy.didCollide())
                endGame();
        }
    }

    void handleInitialSpawn() {
        for (auto& enemy : enemies) {
            enemy.setInitialPosition();
        }
    }

    void createEnemies() {
        for (auto& enemy : enemies) {
            enemy.create();
        }
    }

    void updateEnemies() {
        for (auto& enemy : enemies) {
            enemy.updateMovement();
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

        scoreboard.setDefaultPosition();
        scoreboard.resetScore();

        e.getCamera()->setPosition(0.0f, 1.0f, 0.0f);
        e.getCamera()->setMovementEnabled(true);

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

        handleInitialSpawn();
    }

    void endGame() {
        playerDead = true;

        gameTitle.setContent("Game over!");
        gameTitle.setVisible(true);
        startTitle.setVisible(true);
        gun.setCrosshairVisible(false);

        scoreboard.setEndGamePosition();

        e.getCamera()->setMovementEnabled(false);
    }

    void setup() override {
        level.create();
        gun.create();
        scoreboard.create();
        scoreboard.setVisible(false);

        createEnemies();
        createMenu();

        e.watchPixel(e.getWindowWidth() / 2, e.getWindowHeight() / 2);
        onMouseClick(GLFW_MOUSE_BUTTON_1, getHandler(&Test::handleShot));
        onKeyClick(GLFW_KEY_SPACE, getHandler(&Test::startGame));
    }

    void loop() override {
        if (gameStarted && !playerDead) {
            updateEnemies();
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
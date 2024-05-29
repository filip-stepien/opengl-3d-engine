#include "Demo.hpp"

using namespace demo;

class Test : public App {
private:
    Engine& e = Engine::get();

    Scoreboard scoreboard;
    SceneManager sceneManager;
    Enemy enemies[ENEMY_COUNT];
    Level level;
    Gun gun;

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
        sceneManager.createMenu();
        sceneManager.arrangeAssetsOnMenu(gun);
    }

    void restartGame() {
        playerDead = false;
        sceneManager.arrangeAssetsOnRestart(gun, scoreboard);
        handleInitialSpawn();
    }

    void startGame() {
        if (playerDead)
            restartGame();

        if (gameStarted)
            return;

        gameStarted = true;
        sceneManager.arrangeAssetsOnStart(gun, scoreboard);
        handleInitialSpawn();
    }

    void endGame() {
        playerDead = true;
        sceneManager.arrangeAssetsOnEnd(gun, scoreboard);
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
            sceneManager.displayMenu(playerDead);
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
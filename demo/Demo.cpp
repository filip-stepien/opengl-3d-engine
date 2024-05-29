#include "Demo.hpp"

void demo::Demo::createMenu() {
    sceneManager.createMenu();
    sceneManager.arrangeAssetsOnMenu(gun);
}

void demo::Demo::createEnemies() {
    for (auto& enemy : enemies)
        enemy.create();
}

void demo::Demo::updateEnemies() {
    for (auto& enemy : enemies)
        enemy.updateMovement();
}

void demo::Demo::handleInitialSpawn() {
    for (auto& enemy : enemies)
        enemy.setInitialPosition();
}

void demo::Demo::handleTouchCollision() {
    for (auto& enemy : enemies)
        if (enemy.didCollide())
            endGame();
}

void demo::Demo::handleShot() {
    if (playerDead)
        return;

    gun.setGunShot();

    for (auto& enemy : enemies)
        if (e.getPixelInfo().idObject == enemy.getID()) {
            enemy.resetPosition();
            scoreboard.updateScore();
        }
}

void demo::Demo::startGame() {
    if (playerDead)
        restartGame();

    if (gameStarted)
        return;

    gameStarted = true;
    sceneManager.arrangeAssetsOnStart(gun, scoreboard);

    handleInitialSpawn();
}

void demo::Demo::restartGame() {
    playerDead = false;
    sceneManager.arrangeAssetsOnRestart(gun, scoreboard);

    handleInitialSpawn();
}

void demo::Demo::endGame() {
    playerDead = true;
    sceneManager.arrangeAssetsOnEnd(gun, scoreboard);
}

void demo::Demo::setup() {
    level.create();
    gun.create();
    scoreboard.create();

    createEnemies();
    createMenu();

    e.watchPixel(e.getWindowWidth() / 2, e.getWindowHeight() / 2);

    onMouseClick(GLFW_MOUSE_BUTTON_1, getHandler(&Demo::handleShot));
    onKeyClick(GLFW_KEY_SPACE, getHandler(&Demo::startGame));
}

void demo::Demo::loop() {
    if (gameStarted && !playerDead) {
        updateEnemies();
        handleTouchCollision();
        gun.handleShotAnimation();
    } else {
        sceneManager.displayMenu(playerDead);
    }
}

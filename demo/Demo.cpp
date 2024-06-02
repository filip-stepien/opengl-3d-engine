#include "Demo.hpp"

void demo::Demo::createMenu() {
    sceneManager.create();
    sceneManager.arrangeAssetsOnMenu(gun);
    soundPlayer.playMenuSound();
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
    if (playerDead || !gameStarted)
        return;

    gun.setGunShot();
    soundPlayer.playGunSound();

    for (auto& enemy : enemies) {
        if (e.getPixelInfo().idObject == enemy.getID()) {
            enemy.resetPosition();
            scoreboard.updateScore();
        }
    }
}

void demo::Demo::updateEnemySounds() {
    for (int i = 0; i < ENEMY_COUNT; i++)
        soundPlayer.updateSoundEmitter(i, enemies[i].getPosition());
}

void demo::Demo::startGame() {
    if (playerDead)
        restartGame();

    if (gameStarted)
        return;

    gameStarted = true;
    sceneManager.arrangeAssetsOnStart(gun, scoreboard);

    soundPlayer.stopSounds();
    soundPlayer.playGameSound();
    soundPlayer.playEnemySounds();

    handleInitialSpawn();
}

void demo::Demo::restartGame() {
    playerDead = false;
    sceneManager.arrangeAssetsOnRestart(gun, scoreboard);

    soundPlayer.playGameSound();
    soundPlayer.playEnemySounds();

    handleInitialSpawn();
}

void demo::Demo::endGame() {
    playerDead = true;
    sceneManager.arrangeAssetsOnEnd(gun, scoreboard);

    soundPlayer.stopSounds();
    soundPlayer.playEndSound();
}

void demo::Demo::setup() {
    level.create();
    gun.create();
    scoreboard.create();
    soundPlayer.create();

    createEnemies();
    createMenu();

    e.watchPixel(e.getWindowWidth() / 2, e.getWindowHeight() / 2);

    onMouseClick(GLFW_MOUSE_BUTTON_1, getHandler(&Demo::handleShot));
    onKeyClick(GLFW_KEY_SPACE, getHandler(&Demo::startGame));
}

void demo::Demo::loop() {
    if (gameStarted && !playerDead) {
        gun.handleShotAnimation();
        soundPlayer.updateSoundListener();
        handleTouchCollision();
        updateEnemies();
        updateEnemySounds();
    } else {
        sceneManager.displayMenu(playerDead);
    }
}

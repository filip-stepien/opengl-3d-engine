#include "SceneManager.hpp"
#include "Engine.hpp"

void demo::SceneManager::createDummyEnemy() {
    dummyEnemy.load("../resources/models/jbs.obj");
    dummyEnemy.setDiffuseTexture("../resources/textures/jbs-diffuse.png");
    dummyEnemy.setSpecularTexture("../resources/textures/jbs-specular.png");
    dummyEnemy.setPosition(-8.0f, 0.0f, 0.0f);
}

void demo::SceneManager::createTitles() {
    unsigned int width = Engine::get().getWindowWidth();
    unsigned int height = Engine::get().getWindowHeight();

    gameTitle.setPosition(width / 2, 200.0f);
    gameTitle.setContent("RoboShooter");
    gameTitle.setScale(8.0f);
    gameTitle.setCentered(true);

    startTitle.setPosition(width / 2, height / 2);
    startTitle.setContent("Press SPACE to START");
    startTitle.setScale(3.0f);
    startTitle.setCentered(true);
}

void demo::SceneManager::displayMenu(bool playerDead) {
    unsigned long long framesCount = Engine::get().getFramesCount();
    double deltaTime = Engine::get().getDeltaTime();

    float x = sin(framesCount / 500.0f) * deltaTime * 0.5f;
    float z = cos(framesCount / 500.0f) * deltaTime * 0.7f;
    float textY = sin(framesCount / 50.0f) * 30.0f;

    startTitle.setPosition(startTitle.getPosition().x, textY + 800.0f);

    if (!playerDead)
        Engine::get().getCamera()->move(x, 0.0f, z);
}

void demo::SceneManager::arrangeAssetsOnMenu(Gun& gun) {
    gun.setMenuView();
    Engine::get().getCamera()->move(-5.0f, 0.0f, 0.0f);
}

void demo::SceneManager::arrangeAssetsOnStart(Gun& gun, Scoreboard& scoreboard) {
    Camera* cam = Engine::get().getCamera();
    cam->setMovementEnabled(true);
    cam->setPosition(0.0f, 1.0f, 0.0f);
    cam->disperseInitialFocus();

    gun.setGameView();

    dummyEnemy.move(0.0f, 10.0f, 0.0f);

    startTitle.setVisible(false);
    gameTitle.setVisible(false);

    gun.setCrosshairVisible(true);
    scoreboard.setVisible(true);
}

void demo::SceneManager::arrangeAssetsOnRestart(Gun& gun, Scoreboard& scoreboard) {
    startTitle.setVisible(false);
    gameTitle.setVisible(false);

    gun.setCrosshairVisible(true);

    scoreboard.setDefaultPosition();
    scoreboard.resetScore();

    Engine::get().getCamera()->setPosition(0.0f, 1.0f, 0.0f);
    Engine::get().getCamera()->setMovementEnabled(true);
}

void demo::SceneManager::arrangeAssetsOnEnd(Gun& gun, Scoreboard& scoreboard) {
    gameTitle.setContent("Game over!");
    gameTitle.setVisible(true);
    startTitle.setVisible(true);

    gun.setCrosshairVisible(false);

    scoreboard.setEndGamePosition();

    Engine::get().getCamera()->setMovementEnabled(false);
}

void demo::SceneManager::createMenu() {
    createDummyEnemy();
    createTitles();
}

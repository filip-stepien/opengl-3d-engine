#include "Gun.hpp"
#include "Engine.hpp"

void demo::Gun::createGun() {
    gun.load("../resources/models/doublebarrel.obj");
    gun.setDiffuseTexture("../resources/textures/doublebarrel_diffuse.png");
    gun.setSpecularTexture("../resources/textures/doublebarrel_specular.png");

    gun.setOnForeground(true);
    gun.setPosition(-8.0f, 0.5f, 0.47f);
    gun.setScale(0.2f, 0.2f, 0.2f);
    gun.setRotation(-90.0f, 0.3f, 0.0f, 1.0f);
}

void demo::Gun::createCrosshair() {
    unsigned int width = Engine::get().getWindowWidth();
    unsigned int height = Engine::get().getWindowHeight();

    crosshair.setContent("+");
    crosshair.setPosition(width / 2 - 6.0f, height / 2 + 1.0f);
    crosshair.setVisible(false);
}

void demo::Gun::setMenuView() {
    gun.setViewIndependent(false);
    gun.setPosition(-8.0f, 0.5f, 0.47f);
    gun.setScale(0.2f, 0.2f, 0.2f);
    gun.setRotation(-90.0f, 0.3f, 0.0f, 1.0f);
}

void demo::Gun::setGameView() {
    gun.setViewIndependent(true);
    gun.setPosition(0.65f, -0.55f, -1.3f);
    gun.setScale(0.6f, 0.6f, 0.6f);
    gun.setRotation(-95.0f, 0.0f, 1.0f, 0.0f);
}

void demo::Gun::setGunShot() {
    gunHasShot = true;
}

void demo::Gun::handleShotAnimation() {
    if (!gunHasShot)
        return;

    Mesh* mesh = gun.getMeshes().at(0);
    float rotation = mesh->getRotation().z;

    if (rotation <= -recoilAngle)
        recoilDirection = 1.0f;

    if (rotation > 0) {
        gunHasShot = false;
        recoilDirection = -1.0f;
        gun.rotate(-rotation, 0.0f, 0.0f, 1.0f);
        return;
    }

    gun.rotate(2.0f * recoilDirection, 0.0f, 0.0f, 1.0f);
}

void demo::Gun::setCrosshairVisible(bool visible) {
    crosshair.setVisible(visible);
}

void demo::Gun::create() {
    createGun();
    createCrosshair();
}
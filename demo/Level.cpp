#include "Level.hpp"

void demo::Level::createVents() {
    float rotation = 0.0f;
    float r = LEVEL_RADIUS + 0.5f;
    float vr = LEVEL_RADIUS - 0.1f;
    float y = 0.8f;

    for (int i = 0; i < VENT_COUNT; i++) {
        vents[i].load("../resources/models/vent.obj");

        switch (i) {
            case 0:
                vents[i].setPosition(-r, y, 0);
                ventPlanes[i].setPosition(-vr, y, 0);
                break;
            case 1:
                vents[i].setPosition(0, y, r);
                ventPlanes[i].setPosition(0, y, vr);
                break;
            case 2:
                vents[i].setPosition(r, y, 0);
                ventPlanes[i].setPosition(vr, y, 0);
                break;
            default:
                vents[i].setPosition(0, y, -r);
                ventPlanes[i].setPosition(0, y, -vr);
                break;
        }

        vents[i].rotate(rotation, 0.0f, 1.0f, 0.0f);
        vents[i].rotate(90.0f, 1.0f, 0.0f, 0.0f);
        vents[i].setDiffuseTexture("../resources/textures/vent_diffuse.png");
        vents[i].setSpecularTexture("../resources/textures/vent_specular.png");
        vents[i].scale(0.8f, 0.8f, 0.8f);

        ventPlanes[i].setScale(0.79f, 0.79f, 0.79f);
        ventPlanes[i].setRotation(rotation + 90.0f, 0.0f, 1.0f, 0.0f);
        ventPlanes[i].setDiffuseTexture("../resources/textures/black.png");
        ventPlanes[i].setIgnoreLight(true);

        rotation += 90.0f;
    }
}

void demo::Level::createLight(int i, float x, float z) {
    light[i].setPosition(x, 2.0f, z);
    light[i].setAmbient(0.15f, 0.15f, 0.15f);
    light[i].setDiffuse(0.7f, 0.7f, 0.7f);

    lightSource[i].setIgnoreLight(true);
    lightSource[i].setRotation(90.0f, 1.0f, 0.0f, 0.0f);
    lightSource[i].setPosition(x, 2.99f, z);
    lightSource[i].setScale(0.5f, 0.5f, 0.5f);
}

void demo::Level::createWalls() {
    for (int i = 0; i < WALL_COUNT; i++) {
        walls[i].rotate(90.0f * i, 0.0f, 1.0f, 0.0f);
        walls[i].scale(LEVEL_RADIUS, 1.5f, 1.0f);
        walls[i].move(0.0f, 1.0f, -LEVEL_RADIUS);

        walls[i].setTextureScale(10.0f, 2.0f);
        walls[i].setDiffuseTexture("../resources/textures/wall_diffuse.png");
        walls[i].setSpecularTexture("../resources/textures/wall_specular.png");
        walls[i].setShininess(20.0f);
    }
}

void demo::Level::createFloor() {
    floor.rotate(270.0f, 1.0f, 0.0f, 0.0f);
    floor.scale(LEVEL_RADIUS, LEVEL_RADIUS, 1.0f);

    floor.setTextureScale(2.0f, 2.0f);
    floor.setDiffuseTexture("../resources/textures/concrete_diffuse.png");
    floor.setSpecularTexture("../resources/textures/concrete_specular.png");
}

void demo::Level::createRoof() {
    roof.rotate(90.0f, 1.0f, 0.0f, 0.0f);
    roof.move(0.0f, 0.0f, -3.0f);
    roof.scale(LEVEL_RADIUS, LEVEL_RADIUS, 1.0f);

    roof.setTextureScale(2.0f, 2.0f);
    roof.setDiffuseTexture("../resources/textures/wall_diffuse.png");
    roof.setSpecularTexture("../resources/textures/wall_specular.png");
    roof.setShininess(1.0f);
}

void demo::Level::create() {
    createWalls();
    createFloor();
    createRoof();
    createVents();
    createLight(0, LEVEL_RADIUS / 2, LEVEL_RADIUS / 2);
    createLight(1, -LEVEL_RADIUS / 2, -LEVEL_RADIUS / 2);
}

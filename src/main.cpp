#include "Engine.hpp"
#include "Model.hpp"
#include "Plane3D.hpp"

#include <cmath>
#include <random>

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
    Model gun;
    Model dummyEnemy;
    Model enemies[ENEMY_COUNT];
    Model vents[VENT_COUNT];
    Light light[LIGHT_COUNT];
    Plane3D ventPlanes[VENT_COUNT];
    Plane3D floor;
    Plane3D roof;
    Plane3D walls[WALL_COUNT];
    Plane3D lightSource[LIGHT_COUNT];
    Plane3D menuBackground;
    Text2D crosshair;
    Text2D title;

    bool gunHasShot { false };
    float recoilDirection = -1.0f;
    float recoilAngle = 20.0f;

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

    void createVents() {
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
                    vents[i].setPosition(0, y, -r);
                    ventPlanes[i].setPosition(0, y, vr);
                    break;
                case 2:
                    vents[i].setPosition(r, y, 0);
                    ventPlanes[i].setPosition(vr, y, 0);
                    break;
                default:
                    vents[i].setPosition(0, y, r);
                    ventPlanes[i].setPosition(0, y, -vr);
                    break;
            }

            vents[i].setScale(0.8f, 0.8f, 0.8f);
            vents[i].rotate(90.0f, 1.0f, 0.0f, 0.0f);
            vents[i].rotate(rotation, 0.0f, 0.0f, 1.0f);
            vents[i].setDiffuseTexture("../resources/textures/vent_diffuse.png");
            vents[i].setSpecularTexture("../resources/textures/vent_specular.png");

            ventPlanes[i].setScale(0.79f, 0.79f, 0.79f);
            ventPlanes[i].setRotation(rotation + 90.0f, 0.0f, 1.0f, 0.0f);
            ventPlanes[i].setDiffuseTexture("../resources/textures/black.png");
            ventPlanes[i].setIgnoreLight(true);

            rotation += 90.0f;
        }
    }

    void createLight(int i, float x, float z) {
        light[i].setPosition(x, 2.0f, z);
        light[i].setAmbient(0.15f, 0.15f, 0.15f);
        light[i].setDiffuse(0.7f, 0.7f, 0.7f);

        lightSource[i].setIgnoreLight(true);
        lightSource[i].setRotation(90.0f, 1.0f, 0.0f, 0.0f);
        lightSource[i].setPosition(x, 2.99f, z);
        lightSource[i].setScale(0.5f, 0.5f, 0.5f);
    }

    void createWalls() {
        for (int i = 0; i < WALL_COUNT; i++) {
            walls[i].rotate(90.0f * i, 0.0f, 1.0f, 0.0f);
            walls[i].scale(LEVEL_RADIUS, 1.5f, 1.0f);
            walls[i].setTextureScale(10.0f, 2.0f);
            walls[i].move(0.0f, 1.0f, -LEVEL_RADIUS);
            walls[i].setDiffuseTexture("../resources/textures/wall_diffuse.png");
            walls[i].setSpecularTexture("../resources/textures/wall_specular.png");
            walls[i].setShininess(20.0f);
        }
    }

    void createFloor() {
        floor.rotate(270.0f, 1.0f, 0.0f, 0.0f);
        floor.scale(LEVEL_RADIUS, LEVEL_RADIUS, 1.0f);
        floor.setTextureScale(2.0f, 2.0f);
        floor.setDiffuseTexture("../resources/textures/concrete_diffuse.png");
        floor.setSpecularTexture("../resources/textures/concrete_specular.png");
    }

    void createRoof() {
        roof.rotate(90.0f, 1.0f, 0.0f, 0.0f);
        roof.move(0.0f, 0.0f, -3.0f);
        roof.scale(LEVEL_RADIUS, LEVEL_RADIUS, 1.0f);
        roof.setTextureScale(2.0f, 2.0f);
        roof.setDiffuseTexture("../resources/textures/wall_diffuse.png");
        roof.setSpecularTexture("../resources/textures/wall_specular.png");
        roof.setShininess(1.0f);
    }

    void createGun() {
        gun.load("../resources/models/doublebarrel.obj");
        gun.setDiffuseTexture("../resources/textures/doublebarrel_diffuse.png");
        gun.setSpecularTexture("../resources/textures/doublebarrel_specular.png");
        gun.setViewIndependent(true);

        gun.setPosition(0.65f, -0.55f, -1.3f);
        gun.setScale(0.6f, 0.6f, 0.6f);
        gun.setRotation(-95.0f, 0.0f, 1.0f, 0.0f);
    }

    void createCrosshair() {
        crosshair.setContent("+");
        crosshair.setPosition(e.getWindowWidth() / 2 - 6.0f, e.getWindowHeight() / 2 + 1.0f);
    }

    void createEnemies() {
        for (auto& enemy : enemies) {
            enemy.load("../resources/models/jbs.obj");
            enemy.setDiffuseTexture("../resources/textures/jbs-diffuse.png");
            enemy.setSpecularTexture("../resources/textures/jbs-specular.png");
            enemy.move(2.0f, 0.0f, 2.0f);
        }
    }

    void resetEnemyPos(unsigned int id) {
        for (int i = 0; i < ENEMY_COUNT; i++) {
            Mesh* mesh = enemies[i].getMeshes().at(0);

            if (mesh->getID() == id)
                mesh->setPosition(spawnPoints[i % VENT_COUNT]);
        }
    }

    float randomFloat(float min, float max) {
        std::random_device rd;
        std::mt19937 generator { rd() };
        std::uniform_real_distribution<> distrib(min, max);
        return distrib(generator);
    }

    float randomDir() {
        std::random_device rd;
        std::mt19937 generator { rd() };
        std::uniform_int_distribution<> distrib(0, 1);
        return distrib(generator) ? 1.0f : -1.0f;
    }

    void handleInitialSpawn() {
        for (auto& enemy : enemies) {
            enemy.setPosition(
                randomFloat(INITIAL_SPAWN_RADIUS, 9.0f) * randomDir(),
                0,
                randomFloat(INITIAL_SPAWN_RADIUS, 9.0f) * randomDir()
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
        gunHasShot = true;

        for (auto& enemy : enemies) {
            unsigned int id = enemy.getMeshes().at(0)->getID();
            if (e.getPixelInfo().idObject == id) {
                resetEnemyPos(id);
            }
        }
    }

    void handleShotAnimation() {
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

    void handleTouchCollision() {
        for (auto& enemy : enemies) {
            Mesh* mesh = enemy.getMeshes().at(0);
            glm::vec3 camPos = e.getCamera()->getPosition();
            glm::vec3 enemyPos = mesh->getPosition();
            float dist = glm::length(camPos - enemyPos);

            if (dist < ENEMY_TOUCH_RADIUS)
                resetEnemyPos(mesh->getID());
        }
    }

    void createMenu() {
        e.getCamera()->move(-5.0f, 0.0f, 0.0f);
        dummyEnemy.load("../resources/models/jbs.obj");
        dummyEnemy.setDiffuseTexture("../resources/textures/jbs-diffuse.png");
        dummyEnemy.setSpecularTexture("../resources/textures/jbs-specular.png");
        dummyEnemy.setPosition(-8.0f, 0.0f, 0.0f);
        gun.setViewIndependent(false);
        gun.setPosition(-8.0f, 0.5f, 0.47f);
        gun.setScale(0.2f, 0.2f, 0.2f);
        gun.setRotation(-90.0f, 0.3f, 0.0f, 1.0f);
        title.setContent("Press any key to START");
        title.setPosition(e.getWindowWidth() / 2, e.getWindowHeight() / 2);
        title.setCentered(true);
        title.setScale(4.0f);
        menuBackground.setScale(5.0f, 5.0f, 1.0f);
        menuBackground.setPosition(0.0f, 0.0f, -20.0f);
        menuBackground.setDiffuseTexture("../resources/textures/vent_diffuse.png");
        menuBackground.setSpecularTexture("../resources/textures/vent_specular.png");
    }

    void displayMenu() {
        float x = sin(e.getFramesCount() / 500.0f) * e.getDeltaTime() * 0.5f;
        float z = cos(e.getFramesCount() / 500.0f) * e.getDeltaTime() * 0.7f;
        float textY = sin(e.getFramesCount() / 100.0f) * 30.0f;

        title.setPosition(title.getPosition().x, textY + 800.0f);
        e.getCamera()->move(x, 0.0f, z);
    }

    void setup() override {
        createWalls();
        createFloor();
        createRoof();
        createVents();
        createGun();
        //createCrosshair();
        //createEnemies();
        createLight(0, LEVEL_RADIUS / 2, LEVEL_RADIUS / 2);
        createLight(1, -LEVEL_RADIUS / 2, -LEVEL_RADIUS / 2);
        createMenu();
        //handleInitialSpawn();

        e.watchPixel(e.getWindowWidth() / 2, e.getWindowHeight() / 2);
        onMouseClick(GLFW_MOUSE_BUTTON_1, getHandler(&Test::handleShot));
    }

    void loop() override {
        //updateEnemyMovement();
        //updateEnemyRotation();
        //handleTouchCollision();
        //handleShotAnimation();
        displayMenu();
    }
};

int main() {
    Test app;

	Camera cam;
	cam.setProjection(Camera::PERSPECTIVE, 0.1f, 100.0f);
	cam.setPosition(0.0f, 1.0f, 0.0f);
	cam.setSpeed(2.5f);
	cam.setMovementEnabled(true);
    cam.setYAxisLocked(true);
    cam.setRestrictMovementBox(19.5f, 19.5f, 19.5f);
    cam.setInitialFocus(-8.0f, 0.5f, 0.0f);

	Engine::get()
	.setWindowDimensions(800, 800)
	.setWindowTitle("Demo")
	.setWindowMaximized(true)
	.setMouseCapture(true)
	.setApp(&app)
	.setCamera(&cam)
	.build();

	return 0;
}
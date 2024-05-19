#include "Engine.hpp"
#include "Model.hpp"
#include "Plane3D.hpp"

#include <random>
#include <cmath>
#include <iostream>

class Test : public App {
    Engine& e = Engine::get();
    Model gun;
    Model enemy;
    Plane3D floor;
    Plane3D roof;
    Plane3D walls[4];
    Plane3D lightSource[2];
    Light light[2];

    void createLight(int i, float x, float z) {
        light[i].setPosition(x, 2.0f, z);
        light[i].setAmbient(0.15f, 0.15f, 0.15f);
        light[i].setDiffuse(0.7f, 0.7f, 0.7f);

        lightSource[i].setIsLightSource(true);
        lightSource[i].setRotation(90.0f, 1.0f, 0.0f, 0.0f);
        lightSource[i].setPosition(x, 2.99f, z);
        lightSource[i].setScale(0.5f, 0.5f, 0.5f);
    }

    void createWalls() {
        for (int i = 0; i < 4; i++) {
            walls[i].rotate(90.0f * i, 0.0f, 1.0f, 0.0f);
            walls[i].scale(10.0f, 1.5f, 1.0f);
            walls[i].setTextureScale(10.0f, 2.0f);
            walls[i].move(0.0f, 1.0f, -10.0f);
            walls[i].setDiffuseTexture("../resources/textures/wall_diffuse.png");
            walls[i].setSpecularTexture("../resources/textures/wall_specular.png");
            walls[i].setShininess(20.0f);
        }
    }

    void createFloor() {
        floor.rotate(270.0f, 1.0f, 0.0f, 0.0f);
        floor.scale(10.0f, 10.0f, 1.0f);
        floor.setTextureScale(2.0f, 2.0f);
        floor.setDiffuseTexture("../resources/textures/concrete_diffuse.png");
        floor.setSpecularTexture("../resources/textures/concrete_specular.png");
    }

    void createRoof() {
        roof.rotate(90.0f, 1.0f, 0.0f, 0.0f);
        roof.move(0.0f, 0.0f, -3.0f);
        roof.scale(10.0f, 10.0f, 1.0f);
        roof.setTextureScale(2.0f, 2.0f);
        roof.setDiffuseTexture("../resources/textures/wall_diffuse.png");
        roof.setSpecularTexture("../resources/textures/wall_specular.png");
        roof.setShininess(1.0f);
    }

    void createGun() {
        gun.load("../resources/models/gun.obj");

        for (auto mesh : gun.getMeshes()) {
            mesh->setViewIndependant(true);
            mesh->move(0.5f, -0.3f, -1.0f);
            mesh->scale(0.05f, 0.05f, 0.05f);
            mesh->rotate(90.0f, 0.0f, 1.0f, 0.0f);
            mesh->rotate(90.0f, 1.0f, 0.0f, 0.0f);
        }
    }

    float randomFloat(float min, float max) {
        std::random_device rd;
        std::mt19937 generator { rd() };
        std::uniform_real_distribution<> distrib(min, max);
        return distrib(generator);
    }

    void createEnemy() {
        enemy.load("../resources/models/jbs.obj");
        enemy.getMeshes().at(0)->setDiffuseTexture("../resources/textures/jbs-diffuse.png");
        enemy.getMeshes().at(0)->setSpecularTexture("../resources/textures/jbs-specular.png");
        enemy.getMeshes().at(0)->move(2.0f, 0.0f, 2.0f);
    }

    void setEnemyRandomPos() {
        glm::vec3 pos = {
            randomFloat(-9.0f, 9.0f),
            0.0f,
            randomFloat(-9.0f, 9.0f)
        };

        for (auto& mesh : enemy.getMeshes()) {
            mesh->setPosition(pos);
        }
    }

    void updateEnemyRotation(float speed) {
        for (auto& mesh : enemy.getMeshes()) {
            glm::vec3 pos = mesh->getPosition();
            glm::vec3 cam = e.getCamera()->getPosition();
            glm::vec3 dist = cam - pos;
            float targetDegrees = glm::degrees(std::atan2(dist.x, dist.z));
            float oldDegrees = mesh->getRotation().y;
            float diff = targetDegrees - oldDegrees - 90.0f;

            if (diff < -180.0f) diff += 360.0f;
            if (diff > 180.0f) diff -= 360.0f;

            float change = std::lerp(0, diff, speed);
            float newDegrees = oldDegrees + change;

            mesh->setRotation(newDegrees, 0.0f, 1.0f, 0.0f);
        }
    }

    void updateEnemyMovement(float speed) {
        for (auto& mesh : enemy.getMeshes()) {
            glm::vec3 dir = e.getCamera()->getPosition() - mesh->getPosition();
            dir = glm::normalize(dir);
            dir *= speed * e.getDeltaTime();
            dir.y = 0.0f;

            mesh->setPosition(mesh->getPosition() + dir);
        }
    }

    void handleShotCollision() {
        for (auto& mesh : enemy.getMeshes()) {
            if (e.getPixelInfo().idObject == mesh->getID()) {
                setEnemyRandomPos();
            }
        }
    }

    void handleTouchCollision(float maxDist) {
        glm::vec3 camPos = e.getCamera()->getPosition();
        glm::vec3 enemyPos = enemy.getMeshes().at(0)->getPosition();
        float dist = glm::length(camPos - enemyPos);

        if (dist < maxDist)
            setEnemyRandomPos();
    }

    void setup() override {
        createWalls();
        createFloor();
        createRoof();
        createGun();
        createEnemy();
        createLight(0, 5.0f, 5.0f);
        createLight(1, -5.0f, -5.0f);
        setEnemyRandomPos();

        e.watchPixel(e.getWindowWidth() / 2, e.getWindowHeight() / 2);
        onMouseClick(GLFW_MOUSE_BUTTON_1, getHandler(&Test::handleShotCollision));
    }

    void loop() override {
        updateEnemyMovement(3.0f);
        updateEnemyRotation(0.05f);
        handleTouchCollision(1.5f);
    }
};

int main() {
    Test app;

	Camera cam;
	cam.setProjection(Camera::PERSPECTIVE, 0.1f, 100.0f);
	cam.setInitialFocus(0.0f, 0.0f, 0.0f);
	cam.move(1.0f, 1.0f, 1.0f);
	cam.setSpeed(2.5f);
	cam.setMovementEnabled(true);
    cam.setYAxisLocked(true);
    cam.setRestrictMovementBox(19.5f, 19.5f, 19.5f);

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
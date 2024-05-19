#include "Engine.hpp"
#include "Model.hpp"
#include "Plane3D.hpp"

class Test : public App {
    Engine& e = Engine::get();
    Light light;
    Model gun;
    Plane3D floor;
    Plane3D roof;
    Plane3D walls[4];
    Plane3D lightSource;
    std::vector<Model> enemies;

    void createLight() {
        light.move(5.0f, 2.0f, 0.0f);
        light.setAmbient(0.3f, 0.3f, 0.3f);

        lightSource.setIsLightSource(true);
        lightSource.rotate(90.0f, 1.0f, 0.0f, 0.0f);
        lightSource.move(5.0f, 0.0f, -2.99f);
        lightSource.scale(0.5f, 0.5f, 0.5f);
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

    void createEnemy(GLfloat x, GLfloat z) {
        Model model;
        model.load("../resources/models/jbs.obj");
        model.getMeshes().at(0)->setDiffuseTexture("../resources/textures/jbs-diffuse.png");
        model.getMeshes().at(0)->setSpecularTexture("../resources/textures/jbs-specular.png");
        model.getMeshes().at(0)->move(2.0f, 0.0f, 2.0f);

        for (auto& mesh : model.getMeshes()) {
            mesh->move(x, mesh->getPosition().y, z);
        }

        enemies.push_back(model);
    }

    void setup() override {
        createWalls();
        createFloor();
        createRoof();
        createLight();
        createGun();
        e.watchPixel(e.getWindowWidth() / 2, e.getWindowHeight() / 2);
    }

    void loop() override {
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
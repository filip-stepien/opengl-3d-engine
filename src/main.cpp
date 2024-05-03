#include "Engine.hpp"
#include "Model.hpp"
#include "Plane3D.hpp"

class Test : public App {
    Light light;
    Model model;
    Model gun;
    Plane3D floor;
    Plane3D roof;
    Plane3D walls[4];
    Plane3D lightSource;
    Engine& e = Engine::get();

    void setup() override {
        gun.load("../resources/models/gun.obj");
        for (auto mesh : gun.getMeshes()) {
            mesh->setViewIndependant(true);
            mesh->move(0.5f, -0.3f, -1.0f);
            mesh->scale(0.05f, 0.05f, 0.05f);
            mesh->rotate(90.0f, 0.0f, 1.0f, 0.0f);
            mesh->rotate(90.0f, 1.0f, 0.0f, 0.0f);
        }

        model.load("C:/Users/user/Desktop/opengl-3d-engine/resources/models/jbs.obj");
        model.getMeshes().at(0)->setDiffuseTexture("C:/Users/user/Desktop/opengl-3d-engine/resources/textures/jbs-diffuse.png");
        model.getMeshes().at(0)->setSpecularTexture("C:/Users/user/Desktop/opengl-3d-engine/resources/textures/jbs-specular.png");
        model.getMeshes().at(0)->move(2.0f, 0.0f, 2.0f);

        floor.rotate(270.0f, 1.0f, 0.0f, 0.0f);
        floor.scale(10.0f, 10.0f, 1.0f);
        floor.setTextureScale(2.0f, 2.0f);
        floor.setDiffuseTexture("../resources/textures/concrete_diffuse.png");
        floor.setSpecularTexture("../resources/textures/concrete_specular.png");

        roof.rotate(90.0f, 1.0f, 0.0f, 0.0f);
        roof.move(0.0f, 0.0f, -3.0f);
        roof.scale(10.0f, 10.0f, 1.0f);
        roof.setTextureScale(2.0f, 2.0f);
        roof.setDiffuseTexture("../resources/textures/wall_diffuse.png");
        roof.setSpecularTexture("../resources/textures/wall_specular.png");
        roof.setShininess(1.0f);

        for (int i = 0; i < 4; i++) {
            walls[i].rotate(90.0f * i, 0.0f, 1.0f, 0.0f);
            walls[i].scale(10.0f, 1.5f, 1.0f);
            walls[i].setTextureScale(10.0f, 2.0f);
            walls[i].move(0.0f, 1.0f, -10.0f);
            walls[i].setDiffuseTexture("../resources/textures/wall_diffuse.png");
            walls[i].setSpecularTexture("../resources/textures/wall_specular.png");
            walls[i].setShininess(20.0f);
        }

        light.move(5.0f, 2.0f, 0.0f);
        light.setAmbient(0.3f, 0.3f, 0.3f);

        lightSource.setIsLightSource(true);
        lightSource.rotate(90.0f, 1.0f, 0.0f, 0.0f);
        lightSource.move(5.0f, 0.0f, -2.99f);
        lightSource.scale(0.5f, 0.5f, 0.5f);

        e.watchPixel(e.getWindowWidth() / 2, e.getWindowHeight() / 2);
    }

    void loop() override {
        for (Mesh* mesh : model.getMeshes()) {
            if (e.getPixelInfo().idObject == mesh->getID()) {
                mesh->rotate(180.0f * e.getDeltaTime(), 0.0f, 1.0f, 0.0f);
            }
        }
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
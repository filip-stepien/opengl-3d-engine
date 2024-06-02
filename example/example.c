#include "Engine.hpp"

using namespace engine;

class Test : public App {
    Light light;
    Model model;

    void setup() override {
        model.load("../resources/models/jbs.obj");
        model.getMeshes().at(0)->setDiffuseTexture("../resources/textures/jbs-diffuse.png");
        model.getMeshes().at(0)->setSpecularTexture("../resources/textures/jbs-specular.png");

        light.setPosition(5.0f, 5.0f, 2.0f);
    }

    void loop() override {
        double dt = Engine::get().getDeltaTime();
        model.rotate(90.0f * dt, 0.0f, 1.0f, 0.0f);
    }
};

int main() {
    Test app;

    Camera cam;
    cam.setProjection(Camera::PERSPECTIVE, 0.1f, 100.0f);
    cam.setPosition(5.0f, 5.0f, 5.0f);
    cam.setSpeed(2.5f);
    cam.setMovementEnabled(true);

    Engine::get()
    .setWindowDimensions(800, 800)
    .setWindowTitle("Example")
    .setWindowMaximized(true)
    .setMouseCapture(true)
    .setApp(&app)
    .setCamera(&cam)
    .build();

    return 0;
}
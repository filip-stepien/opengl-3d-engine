#include "Engine.hpp"
#include "Model.hpp"

class Test : public App {
    Light light;
    Model model;
    Engine& e = Engine::get();

    void setup() override {
        model.load("C:/Users/user/Desktop/opengl-3d-engine/resources/models/jbs.obj");
        model.getMeshes().at(0)->setDiffuseTexture("C:/Users/user/Desktop/opengl-3d-engine/resources/textures/jbs-diffuse.png");
        model.getMeshes().at(0)->setSpecularTexture("C:/Users/user/Desktop/opengl-3d-engine/resources/textures/jbs-specular.png");
        
        light.move(3.0f, 6.0f, 4.0f);

        e.watchPixel(e.getWindowWidth() / 2, e.getWindowHeight() / 2);
    }

    void loop() override {
        for (Mesh* mesh : model.getMeshes()) {
            if (e.getPixelInfo().idObject == mesh->getID()) {
                mesh->rotate(glm::radians(180.0f * e.getDeltaTime()), 0.0f, 1.0f, 0.0f);
            }
        }
    }
};

int main() {
    Test app;

	Camera cam;
	cam.setProjection(Camera::PERSPECTIVE, 0.1f, 100.0f);
	cam.setInitialFocus(0.0f, 0.0f, 0.0f);
	cam.move(12.0f, 3.0f, 12.0f);
	cam.setSpeed(15.0f);
	cam.setMovementEnabled(true);
    cam.setYAxisLocked(false);

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
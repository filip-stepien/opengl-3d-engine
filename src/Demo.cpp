#include "Demo.hpp"
#include "Engine.hpp"

void Demo::close() {
	Engine::get().close();
}

void Demo::switchLight() {
	switch (lightType % 4) {
	case 0:
		light[0].setDiffuse(0.0f, 0.0f, 0.0f);
		light[0].setAmbient(0.0f, 0.0f, 0.0f);
		light[0].setSpecular(0.0f, 0.0f, 0.0f);
		light[1].setDiffuse(1.0f, 1.0f, 1.0f);
		light[1].setAmbient(0.1f, 0.1f, 0.1f);
		light[1].setSpecular(1.0f, 1.0f, 1.0f);
		break;
	case 1:
		light[1].setDiffuse(0.0f, 0.8f, 0.0f);
		light[1].setAmbient(0.0f, 0.1f, 0.0f);
		light[1].setSpecular(0.0f, 0.8f, 0.0f);
		break;
	case 2:
		light[1].setDiffuse(0.0f, 0.8f, 0.8f);
		light[1].setAmbient(0.15f, 0.0f, 0.0f);
		light[1].setSpecular(1.0f, 1.0f, 0.0f);
		break;
	case 3:
		light[0].setDiffuse(0.0f, 0.0f, 0.8f);
		light[0].setAmbient(0.0f, 0.0f, 0.1f);
		light[0].setSpecular(0.0f, 0.0f, 0.8f);
		light[1].setDiffuse(0.8f, 0.0f, 0.0f);
		light[1].setAmbient(0.1f, 0.0f, 0.0f);
		light[1].setSpecular(0.8f, 0.0f, 0.0f);
		break;
	}
	lightType++;
}

void Demo::setup() {
	onKeyClick(GLFW_KEY_SPACE, getHandler(&Demo::switchLight));
	onKeyClick(GLFW_KEY_ESCAPE, getHandler(&Demo::close));

	lowPolySphere.move(7.0f, 0.0f, 25.0f);

	light[0].setDiffuse(0.0f, 0.0f, 0.0f);
	light[0].setAmbient(0.0f, 0.0f, 0.0f);
	light[0].setSpecular(0.0f, 0.0f, 0.0f);
	light[1].setDiffuse(1.0f, 1.0f, 1.0f);
	light[1].setAmbient(0.1f, 0.1f, 0.1f);
	light[1].setSpecular(1.0f, 1.0f, 1.0f);

	for (int i = 0; i < 2; i++) {
		sphere[i].move(15.0f + i * 15.0f, 5.0f, 15.0f);
		sphere[i].scale(0.05f, 0.05f, 0.05f);
		light[i].move(15.0f + i * 15.0f, 5.0f, 15.0f);
	}

	for (int i = 0; i < 6; i++) {
		cube[i].move(static_cast<float>(i) * 2.0f + 5.0f * i, 0.0f, 0.0f);
		cube[i].setDiffuseTexture("../resources/textures/debug.png");
		cube[i].setShininess((i + 1) * 15.0f);
	}

	for (int i = 2; i < 5; i++) {
		sphere[i].move(static_cast<float>(i) * 2.0f + 5.0f * i, 0.0f, 25.0f);
		sphere[i].setDiffuseTexture("../resources/textures/debug.png");
		sphere[i].setRadius(1.0f * i);
	}

	for (int i = 0; i < 3; i++) {
		torus[i].move(0.0f, 0.0f, static_cast<float>(i) * 2.0f + 5.0f * (i + 1));
		torus[i].setOuterRadius(static_cast<float>(i + 1));
		torus[i].setInnerRadius(static_cast<float>(i + 1) * 0.3f);
		torus[i].setRings(8 + 8 * i);
		torus[i].setSides(8 + 8 * i);
		torus[i].setDiffuseTexture("../resources/textures/debug.png");
	}

	sphere[2].setDiffuseTexture("../resources/textures/ball.jpg");
	cube[0].setDiffuseTexture("../resources/textures/container.png");
	cube[1].setDiffuseTexture("../resources/textures/container.png");
	cube[1].setSpecularTexture("../resources/textures/container_specular.png");
}

void Demo::loop() {
	float delta = static_cast<float>(Engine::get().getDeltaTime());
	float deltaRad = glm::radians(sin(delta) * 100);
	float scale = 1.0f + direction * delta * 0.5f;

	cube[2].move(0.0f, delta * 2.0f * direction, 0.0f);
	cube[2].rotate(deltaRad, 0.0f, 1.0f, 0.0f);
	sphere[3].move(0.0f, delta * 2.0f * direction, 0.0f);
	sphere[3].rotate(deltaRad, 0.0f, 1.0f, 0.0f);
	torus[2].move(0.0f, delta * 2.0f * direction, 0.0f);

	cube[3].scale(1.0f, 1.0f, scale);
	torus[1].scale(1.0f, 1.0f, scale);

	cube[4].scale(1.0f, 1.0f, scale);
	cube[4].scale(1.0f, scale, scale);

	cube[5].scale(scale, scale, scale);
	cube[5].rotate(deltaRad, 1.0f, 1.0f, 0.0f);

	sphere[4].scale(1.0f, 1.0f, scale);
	sphere[4].rotate(deltaRad, 1.0f, 1.0f, 0.0f);

	if (step > 3.0f || step < -3.0f) {
		direction = -direction;
		step = 0.0f;
	}

	for (int i = 0; i < 3; i++) {
		torus[i].rotate(deltaRad, 0.0f, 1.0f, 0.0f);
	}

	step += delta;
}
#pragma once

#include "App.hpp"
#include "Light.hpp"
#include "Sphere.hpp"
#include "Cube.hpp"
#include "Torus.hpp"

class Demo : public App {
public:
	Light light[2];
	Cube cube[6];
	Sphere sphere[5];
	Torus torus[3];
	Sphere lowPolySphere{ 1.0f, 8, 8 };

	float direction = 1.0f;
	float step = 1.0f;
	float scale = 1.01f;
	int lightType = 1;

	void close();
	void switchLight();
	void setup() override;
	void loop() override;
};
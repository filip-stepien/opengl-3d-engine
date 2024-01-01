#include "Cube.hpp"

void Cube::populateVertices() {
	vertices = {
		{ glm::vec3(-1.0, -1.0,  1.0), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 1.0f) },
		{ glm::vec3( 1.0, -1.0,  1.0), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3( 1.0,  1.0,  1.0), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(-1.0,  1.0,  1.0), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 0.0f) },

		{ glm::vec3(-1.0, -1.0, -1.0), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0,  1.0, -1.0), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3( 1.0,  1.0, -1.0), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3( 1.0, -1.0, -1.0), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 1.0f) },

		{ glm::vec3(-1.0,  1.0, -1.0), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 1.0f) },
		{ glm::vec3(-1.0,  1.0,  1.0), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3( 1.0,  1.0,  1.0), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3( 1.0,  1.0, -1.0), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 1.0f) },

		{ glm::vec3(-1.0, -1.0, -1.0), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3( 1.0, -1.0, -1.0), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 1.0f) },
		{ glm::vec3( 1.0, -1.0,  1.0), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3(-1.0, -1.0,  1.0), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 0.0f) },

		{ glm::vec3( 1.0, -1.0, -1.0), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3( 1.0,  1.0, -1.0), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f) },
		{ glm::vec3( 1.0,  1.0,  1.0), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3( 1.0, -1.0,  1.0), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f) },

		{ glm::vec3(-1.0, -1.0, -1.0), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f) },
		{ glm::vec3(-1.0, -1.0,  1.0), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0,  1.0,  1.0), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3(-1.0,  1.0, -1.0), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f) }
	};
}

void Cube::populateIndices() {
	indices = {
		0,  1,  2,  2,  3,  0,
		4,  5,  6,  6,  7,  4,
		8,  9,  10, 10, 11, 8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20
	};
}

Cube::Cube() : Shape(vertices, indices) {
	populateVertices();
	populateIndices();
	initialize();
}
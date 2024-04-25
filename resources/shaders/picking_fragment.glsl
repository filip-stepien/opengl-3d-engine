#version 330

uniform uint objectIndex;

out uvec3 FragColor;

void main() {
	FragColor = uvec3(objectIndex, 0, 0);
}
#version 330

uniform int objectIndex;

out uvec3 FragColor;

void main() {
	FragColor = uvec3(objectIndex, gl_PrimitiveID, 0);
}
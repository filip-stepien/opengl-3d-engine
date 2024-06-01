#include "Light.hpp"
#include "Engine.hpp"

Light::Light() {
	Engine::get().addLight(this);
}

void Light::setAmbient(glm::vec3 ambient) {
	this->ambient = ambient;
}

void Light::setDiffuse(glm::vec3 diffuse) {
	this->diffuse = diffuse;
}

void Light::setSpecular(glm::vec3 specular) {
	this->specular = specular;
}

void Light::setAmbient(GLfloat r, GLfloat g, GLfloat b) {
	this->ambient = glm::vec3(r, g, b);
}

void Light::setDiffuse(GLfloat r, GLfloat g, GLfloat b) {
	this->diffuse = glm::vec3(r, g, b);
}

void Light::setSpecular(GLfloat r, GLfloat g, GLfloat b) {
	this->specular = glm::vec3(r, g, b);
}

glm::vec3 Light::getAmbient() {
	return this->ambient;
}

glm::vec3 Light::getDiffuse() {
	return this->diffuse;
}

glm::vec3 Light::getSpecular() {
	return this->specular;
}

void Light::update(Shader& shader, int index) {
	if (index > MAX_LIGHTS || index < 0) {
		std::cout << "SHADER ERROR" << std::endl;
		std::cout << "Light index out of range.";
        std::cout << "This value should be between 0 and ";
        std::cout << MAX_LIGHTS << std::endl;
		return;
	}

	std::string lightName = "light[" + std::to_string(index) + "]";

	shader.use();
	shader.setVec3(lightName + ".position", position);
	shader.setVec3(lightName + ".ambient", ambient);
	shader.setVec3(lightName + ".diffuse", diffuse);
	shader.setVec3(lightName + ".specular", specular);
}
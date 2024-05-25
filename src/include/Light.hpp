#ifndef LIGHT_H
#define LIGHT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

#include "Transformable.hpp"
#include "Updatable.hpp"
#include "Shader.hpp"

class Light : public Updatable, public Transformable {
private:
	glm::vec3 ambient { 0.2f };
	glm::vec3 diffuse { 1.0f };
	glm::vec3 specular { 1.0f };

public:
	Light();

	void setAmbient(glm::vec3 ambient);
	void setDiffuse(glm::vec3 diffuse);
	void setSpecular(glm::vec3 specular);
	void setAmbient(GLfloat r, GLfloat g, GLfloat b);
	void setDiffuse(GLfloat r, GLfloat g, GLfloat b);
	void setSpecular(GLfloat r, GLfloat g, GLfloat b);

	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();

	void update(Shader& shader, int index);
};

#endif
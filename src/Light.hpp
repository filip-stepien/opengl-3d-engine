#ifndef LIGHT_H
#define LIGHT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

#include "Movable.hpp"
#include "Updatable.hpp"
#include "Shader.hpp"

class Light : public Updatable, public Movable {
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

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
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Mesh.hpp"
#include "VertexArray.hpp"

#include <glm/glm.hpp>
#include <vector>

class Shape : public Mesh {
private:
	glm::vec3 color;

protected:
	virtual void populateVertices(std::vector<Vertex> vertices);
	virtual void populateInidces(std::vector<GLuint> indices);

public:
	Shape();

	void setColor(glm::vec3 color);
	void setColor(GLfloat r, GLfloat g, GLfloat b);
	
	glm::vec3 getColor();
};
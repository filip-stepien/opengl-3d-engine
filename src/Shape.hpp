#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Mesh.hpp"
#include "VertexArray.hpp"

#include <glm/glm.hpp>
#include <vector>

class Shape : public Mesh {
protected:
	glm::vec3 color;

	virtual void populateVertices();
	virtual void populateIndices();

public:
	Shape(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, const char* texturePath = nullptr);

	void setColor(glm::vec3 color);
	void setColor(GLfloat r, GLfloat g, GLfloat b);
	
	glm::vec3 getColor();
};
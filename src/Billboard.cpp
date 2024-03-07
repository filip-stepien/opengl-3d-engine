#include "Billboard.hpp"

Billboard::Billboard() : Mesh() {
    vertices = {
        { {-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
        { { 1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f} },
        { { 1.0f,  1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f} },
        { {-1.0f,  1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} }
    };

    indices = { 0, 1, 2, 2, 3, 0 };
}

void Billboard::draw(Shader &shader, glm::vec3 cam) {
    glm::vec3 up = { 0.0f, 1.0f, 0.0f };
    glm::vec3 front = glm::normalize(cam - position);
    glm::vec3 right = glm::normalize(glm::cross(up, front));
    glm::vec3 newUp = glm::cross(front, right);

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix[0] = glm::vec4(right, 0.0f);
    modelMatrix[1] = glm::vec4(newUp, 0.0f);
    modelMatrix[2] = glm::vec4(-front, 0.0f);
    modelMatrix[3] = glm::vec4(position, 1.0f);

    model = modelMatrix;

    Mesh::draw(shader);
}

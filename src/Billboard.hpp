#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "Texture.hpp"
#include "Drawable.hpp"
#include "Mesh.hpp"

class Billboard : public Mesh {
public:
    Billboard();
    void draw(Shader& shader, glm::vec3 cam);
};


#endif

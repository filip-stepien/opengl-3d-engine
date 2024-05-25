#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float textureScaleX;
uniform float textureScaleY;
uniform bool viewIndependent;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    TexCoord = vec2(aTexCoord.x * textureScaleX, aTexCoord.y * textureScaleY);

    gl_Position = viewIndependent ? projection * vec4(FragPos, 1.0) : projection * view * vec4(FragPos, 1.0);
}
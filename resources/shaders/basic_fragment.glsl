#version 330 core
out vec4 FragColor;

#define MAX_LIGHTS 8

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoord;
  
uniform sampler2D tex;

uniform vec3 viewPos; 
uniform vec3 objectColor;

struct Light {
    vec3 position;
    vec3 color;        
    float ambientStrength;
    float specularStrength;
};

uniform Light light[MAX_LIGHTS];

vec3 calcLight(Light light, vec3 fragPos, vec3 normal, vec3 viewDir) {
    vec3 ambient = light.ambientStrength * light.color;
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.specularStrength * spec * light.color;

    return (ambient + diffuse + specular);
}

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 texColor = texture(tex, TexCoord).rgb;

    vec3 lightResult = vec3(0.0);
    for(int i = 0; i < MAX_LIGHTS; i++)
        lightResult += calcLight(light[i], FragPos, norm, viewDir);

    vec3 result = lightResult * texColor * objectColor;
    FragColor = vec4(result, 1.0);
} 
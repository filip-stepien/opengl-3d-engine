#include "Enemy.hpp"

void demo::Enemy::setRandomSpawnPos() {
    spawnPosition = Random::randomInt(0, VENT_COUNT - 1);
}

void demo::Enemy::create() {
    model.load("../resources/models/jbs.obj");
    model.setDiffuseTexture("../resources/textures/jbs-diffuse.png");
    model.setSpecularTexture("../resources/textures/jbs-specular.png");
    model.move(2.0f, 0.0f, 2.0f);

    setRandomSpawnPos();
}

void demo::Enemy::setInitialPosition() {
    model.setPosition(
        Random::randomFloat(INITIAL_SPAWN_RADIUS, 9.0f) * Random::randomDir(),
        0,
        Random::randomFloat(INITIAL_SPAWN_RADIUS, 9.0f) * Random::randomDir()
    );
}

void demo::Enemy::updateRotation() {
    Mesh* mesh = model.getMeshes().at(0);
    glm::vec3 pos = mesh->getPosition();
    glm::vec3 cam = Engine::get().getCamera()->getPosition();
    glm::vec3 dist = cam - pos;
    float targetDegrees = glm::degrees(std::atan2(dist.x, dist.z));
    float oldDegrees = mesh->getRotation().y;
    float diff = targetDegrees - oldDegrees - 90.0f;

    if (diff < -180.0f) diff += 360.0f;
    if (diff > 180.0f) diff -= 360.0f;

    float change = std::lerp(0, diff, ENEMY_ROT_SPEED);
    float newDegrees = oldDegrees + change;

    model.setRotation(newDegrees, 0.0f, 1.0f, 0.0f);
}

void demo::Enemy::updatePosition() {
    Mesh* mesh = model.getMeshes().at(0);
    glm::vec3 pos = mesh->getPosition();
    glm::vec3 dir;

    if ((pos.x > LEVEL_RADIUS - 1.0f || pos.x < -LEVEL_RADIUS + 1.0f) ||
        (pos.z > LEVEL_RADIUS - 1.0f || pos.z < -LEVEL_RADIUS + 1.0f)) {
        dir = spawnDirections[spawnPosition];
    } else {
        dir = Engine::get().getCamera()->getPosition() - pos;
        dir = glm::normalize(dir);
        dir.y = 0.0f;
    }

    dir *= ENEMY_MOV_SPEED * Engine::get().getDeltaTime();
    model.setPosition(pos + dir);
}

void demo::Enemy::resetPosition() {
    setRandomSpawnPos();
    model.setPosition(spawnPoints[spawnPosition]);
}

bool demo::Enemy::didCollide() {
    Mesh* mesh = model.getMeshes().at(0);
    glm::vec3 camPos = Engine::get().getCamera()->getPosition();
    glm::vec3 enemyPos = mesh->getPosition();
    float dist = glm::length(camPos - enemyPos);

    return dist < ENEMY_TOUCH_RADIUS;
}

unsigned int demo::Enemy::getID() {
    return model.getMeshes().at(0)->getID();
}

void demo::Enemy::updateMovement() {
    updateRotation();
    updatePosition();
}
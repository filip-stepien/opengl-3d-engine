#include "SoundPlayer.hpp"

void demo::SoundPlayer::create() {
    menuSrc = player->addSoundSourceFromFile("../resources/sounds/menu.mp3", ESM_AUTO_DETECT, true);
    endSrc = player->addSoundSourceFromFile("../resources/sounds/end.mp3", ESM_AUTO_DETECT, true);
    gunSrc = player->addSoundSourceFromFile("../resources/sounds/shot.mp3", ESM_AUTO_DETECT, true);
    gameSrc = player->addSoundSourceFromFile("../resources/sounds/game.mp3", ESM_AUTO_DETECT, true);
    enemySrc = player->addSoundSourceFromFile("../resources/sounds/enemy.mp3", ESM_AUTO_DETECT, true);

    menuSrc->setDefaultVolume(MENU_VOLUME);
    endSrc->setDefaultVolume(END_VOLUME);
    gunSrc->setDefaultVolume(GUN_VOLUME);
    gameSrc->setDefaultVolume(GAME_VOLUME);
    enemySrc->setDefaultVolume(ENEMY_VOLUME);
    enemySrc->setDefaultMinDistance(ENEMY_MIN_DIST);
}

void demo::SoundPlayer::playGunSound() {
    player->play2D(gunSrc);
}

void demo::SoundPlayer::playEndSound() {
    player->play2D(endSrc);
}

void demo::SoundPlayer::playMenuSound() {
    player->play2D(menuSrc, true);
}

void demo::SoundPlayer::playEnemySounds() {
    for (int i = 0; i < ENEMY_COUNT; i++)
        enemiesSound[i] = player->play3D(enemySrc, { 0.0f, 0.0f, 0.0f }, true, false, true);
}

void demo::SoundPlayer::playGameSound() {
    gameSound = player->play2D(gameSrc, true, false, true);
}

void demo::SoundPlayer::stopSounds() {
    player->stopAllSounds();
}

void demo::SoundPlayer::updateSoundListener() {
    glm::vec3 camPos = Engine::get().getCamera()->getPosition();
    glm::vec3 ray = Engine::get().getCamera()->getRaycast();

    player->setListenerPosition(
        { camPos.x, camPos.y, camPos.z },
        { ray.x, ray.y, ray.z }
    );
}

void demo::SoundPlayer::updateSoundEmitter(int index, glm::vec3 pos) {
    enemiesSound[index]->setPosition({ pos.x, pos.y, pos.z });
}

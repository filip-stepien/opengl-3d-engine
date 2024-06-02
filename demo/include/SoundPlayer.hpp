#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H

#include "Engine.hpp"
#include "Enemy.hpp"

namespace demo {
    class SoundPlayer : public Asset {
    private:
        const float MENU_VOLUME = 0.25f;
        const float GAME_VOLUME = 0.05f;
        const float END_VOLUME = 0.07f;
        const float GUN_VOLUME = 0.2f;
        const float ENEMY_VOLUME = 1.0f;
        const float ENEMY_MIN_DIST = 1.0f;

        ISoundEngine* player { Engine::get().getSoundPlayer() };
        ISoundSource* enemySrc { nullptr };
        ISoundSource* gunSrc { nullptr };
        ISoundSource* gameSrc { nullptr };
        ISoundSource* endSrc { nullptr };
        ISoundSource* menuSrc { nullptr };

        ISound* enemiesSound[ENEMY_COUNT] = { nullptr };
        ISound* gameSound { nullptr };

    public:
        void create() override;
        void playGunSound();
        void playEndSound();
        void playMenuSound();
        void playEnemySounds();
        void playGameSound();
        void stopSounds();
        void updateSoundListener();
        void updateSoundEmitter(int index, glm::vec3 pos);
    };
}

#endif
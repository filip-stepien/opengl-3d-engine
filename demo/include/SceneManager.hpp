#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Model.hpp"
#include "Text2D.hpp"
#include "Gun.hpp"
#include "Scoreboard.hpp"

namespace demo {
    class SceneManager {
    private:
        Model dummyEnemy;
        Text2D gameTitle;
        Text2D startTitle;

        void createDummyEnemy();
        void createTitles();

    public:
        void displayMenu(bool playerDead);
        void arrangeAssetsOnMenu(Gun& gunToMove);
        void arrangeAssetsOnStart(Gun& gun, Scoreboard& scoreboard);
        void arrangeAssetsOnRestart(Gun& gun, Scoreboard& scoreboard);
        void arrangeAssetsOnEnd(Gun& gun, Scoreboard& scoreboard);
        void createMenu();
    };
}

#endif
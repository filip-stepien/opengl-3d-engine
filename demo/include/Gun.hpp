#ifndef GUN_H
#define GUN_H

#include "Model.hpp"
#include "Asset.hpp"
#include "Text2D.hpp"

namespace demo {
    using namespace engine;

    class Gun : public Asset {
    private:
        Model gun;
        Text2D crosshair;
        bool gunHasShot { false };
        float recoilDirection { -1.0f };
        float recoilAngle { 20.0f };

    public:
        void createGun();
        void createCrosshair();
        void setMenuView();
        void setGameView();
        void setGunShot();
        void setCrosshairVisible(bool visible);
        void handleShotAnimation();
        void create() override;
    };
}

#endif
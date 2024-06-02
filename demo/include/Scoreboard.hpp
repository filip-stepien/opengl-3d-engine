#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "Text2D.hpp"
#include "Asset.hpp"

namespace demo {
    using namespace engine;

    class Scoreboard : public Asset {
    private:
        Text2D scoreboard;
        unsigned int score { 0 };

        void setContent();

    public:
        void updateScore();
        void resetScore();
        void setDefaultPosition();
        void setEndGamePosition();
        void setVisible(bool visible);
        void create() override;
    };
}

#endif

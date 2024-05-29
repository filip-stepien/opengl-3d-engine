#include "Scoreboard.hpp"
#include "Engine.hpp"

void demo::Scoreboard::setContent() {
    scoreboard.setContent("Score: " + std::to_string(score));
}

void demo::Scoreboard::updateScore() {
    score++;
    setContent();
}

void demo::Scoreboard::resetScore() {
    score = 0;
    setContent();
}

void demo::Scoreboard::setDefaultPosition() {
    scoreboard.setCentered(false);
    scoreboard.setPosition(50.0f, Engine::get().getWindowHeight() - 100.0f);
}

void demo::Scoreboard::setEndGamePosition() {
    scoreboard.setCentered(true);
    scoreboard.setPosition(Engine::get().getWindowWidth() / 2, Engine::get().getWindowHeight() / 2);
}

void demo::Scoreboard::setVisible(bool visible) {
    scoreboard.setVisible(visible);
}

void demo::Scoreboard::create() {
    scoreboard.setContent("Score: 0");
    scoreboard.setScale(4.0f);
    setDefaultPosition();
}

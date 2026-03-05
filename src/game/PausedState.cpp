#include "PausedState.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"

void PausedState::enter() {
    sdlutils().virtualTimer().pause();
}

void PausedState::leave() {
    sdlutils().virtualTimer().resume();
}

void PausedState::update() {

    sdlutils().msgs().at("press any key to resume the game").render(200, 300);

    if (ih().keyDownEvent()) {
        Game::Instance()->setState(Game::RUNNING);
    }
}

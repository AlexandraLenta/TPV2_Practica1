#include "PausedState.h"
#include "Game.h"

void PausedState::enter() {
    sdlutils().virtualTimer().pause();
}

void PausedState::leave() {
    sdlutils().virtualTimer().resume();
}

void PausedState::update() {

    sdlutils().msgs().at("press any key to resume the game") ->render(sdlutils().renderer(), 200, 300);

    if (ihdlr.keyDownEvent()) {
        Game::Instance()->setState(Game::RUNNING);
    }
}

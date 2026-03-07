#include "PausedState.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"

void PausedState::enter() {
    sdlutils().virtualTimer().pause();
    _tex = &sdlutils().msgs().at("pause");
}

void PausedState::leave() {
    sdlutils().virtualTimer().resume();
}

void PausedState::update() {
    _tex->render((sdlutils().width() - _tex->width()) / 2, (sdlutils().height() - _tex->height()) / 2);

    if (ih().keyDownEvent()) {
        Game::Instance()->setState(Game::RUNNING);
    }
}

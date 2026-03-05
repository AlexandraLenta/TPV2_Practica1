#include "NewGameState.h"
#include "Game.h"
#include "FighterUtils.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

void NewGameState::enter() {
    // nada especial
}

void NewGameState::leave() {
    // nada especial
}

void NewGameState::update() {

    sdlutils().msgs().at("press any key to start a new game").render(200, 300);

    if (ih().keyDownEvent()) { //PERO PQ NO FUNCIONA 
        _fighterUtils -> reset_lives();
        Game::Instance()->setState(Game::NEWROUND);
    }
}

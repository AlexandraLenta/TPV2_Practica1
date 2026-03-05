#include "NewGameState.h"
#include "Game.h"
#include "FighterUtils.h"
#include "../sdlutils/SDLUtils.h"

void NewGameState::enter() {
    // nada especial
}

void NewGameState::leave() {
    // nada especial
}

void NewGameState::update() {

    SDLUtils::sdlutils().msgs().at("press any key to start a new game")->render(sdlutils().renderer(), 200, 300);

    if (ihdlr.keyDownEvent()) { //PERO PQ NO FUNCIONA 
        _fighterUtils -> reset_lives();
        Game::Instance()->setState(Game::NEWROUND);
    }
}

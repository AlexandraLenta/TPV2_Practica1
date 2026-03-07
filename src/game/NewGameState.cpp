#include "NewGameState.h"
#include "Game.h"
#include "FighterUtils.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

NewGameState::NewGameState() {
    _tex = &sdlutils().msgs().at("game_start");
}

void NewGameState::enter() {
    std::cout << "NEW\n";
}

void NewGameState::leave() {
    Game::Instance()->getFighterUtils()->reset_lives();
}

void NewGameState::update() {
    assert(_tex != nullptr);

    _tex->render((sdlutils().width() - _tex->width())/2, (sdlutils().height() - _tex->height())/2);

    if (ih().keyDownEvent()) { 
        Game::Instance()->setState(Game::NEWROUND);
    }
}
#include "NewRoundState.h"
#include "FighterUtils.h"
#include "AsteroidsFacade.h"
#include "AsteroidsUtils.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"

NewRoundState::NewRoundState() {
    _tex = &sdlutils().msgs().at("round_start");
}

void NewRoundState::enter() {}

void NewRoundState::leave() {
    Game::Instance()->getFighterUtils()->reset_fighter();
    Game::Instance()->getAsteroidUtils()->remove_all_asteroids();
    Game::Instance()->getAsteroidUtils()->create_asteroids(10);
}

void NewRoundState::update() {
    assert(_tex != nullptr);

    _tex->render(sdlutils().width()/2 - _tex->width()/2, sdlutils().height()/2 - _tex->height()/2);

    if (ih().isKeyDown(SDL_SCANCODE_RETURN)) {
        Game::Instance()->setState(Game::RUNNING);
    }
}

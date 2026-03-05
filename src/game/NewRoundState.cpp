#include "NewRoundState.h"
#include "FighterUtils.h"
#include "AsteroidsFacade.h"
#include "AsteroidsUtils.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"


void NewRoundState::enter() {}

void NewRoundState::leave() {}

void NewRoundState::update() {

    sdlutils().msgs().at("press ENTER to start the round").render(200, 300);

    if (ih().isKeyDown(SDL_SCANCODE_RETURN)) {
        _fighterFacade->reset_fighter();
        _asteroidsUtils->remove_all_asteroids();
        _asteroidsUtils->create_asteroids(10);

        Game::Instance()->setState(Game::RUNNING);
    }
}

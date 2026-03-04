#include "NewRoundState.h"
#include "FighterUtils.h"
#include "AsteroidsFacade.h"
#include "AsteroidsUtils.h"
#include "Game.h"
#include <SDL.h>

void NewRoundState::enter() {}

void NewRoundState::leave() {}

void NewRoundState::update() {

    auto& ih = ihdlr();

    sdlutils().msgs().at("press ENTER to start the round") ->render(sdlutils().renderer(), 200, 300);

    if (ih.isKeyDown(SDL_SCANCODE_RETURN)) {

        FighterFacade()->reset_fighter();
        AsteroidsUtils::Instance()->remove_all_asteroids(); 
        AsteroidsUtils::Instance()->create_asteroids(10);

        Game::Instance()->setState(Game::RUNNING);
    }
}

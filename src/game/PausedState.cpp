#include "PausedState.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "../ecs/EntityManager.h"
#include "../sdlutils/SDLUtils.h"

void PausedState::enter() {
    sdlutils().virtualTimer().pause(); // pause
    
    _tex = &sdlutils().msgs().at("pause"); // get pause text

    int asteroidNr = Game::Instance()->getMngr()->getEntities(ecs::grp::ASTEROIDS).size(); // get asteroid number
    std::string statTex = "Asteroids remaining: " + std::to_string(asteroidNr); // create asteroid text 

    // create texture from asteroid text
    _statTex = new Texture(sdlutils().renderer(), statTex, sdlutils().fonts().at("ARIAL24"), SDL_Color{ 255, 255, 255, 255 });
}

void PausedState::leave() {
    sdlutils().virtualTimer().resume();
    delete _statTex;
    _statTex = nullptr;
}

void PausedState::update() {
    _tex->render((sdlutils().width() - _tex->width()) / 2, (sdlutils().height() - _tex->height()) / 2);

    _statTex->render((sdlutils().width() - _statTex->width()) / 2, (sdlutils().height() - _statTex->height()) / 3);
    
    if (ih().keyDownEvent()) {
        Game::Instance()->setState(Game::RUNNING);
    }
}

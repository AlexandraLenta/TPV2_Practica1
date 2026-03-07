#include "PausedState.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "../ecs/EntityManager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Health.h"

void PausedState::enter() {
    sdlutils().virtualTimer().pause(); // pause
    
    _tex = &sdlutils().msgs().at("pause"); // get pause text

    int asteroidNr = Game::Instance()->getMngr()->getEntities(ecs::grp::ASTEROIDS).size(); // get asteroid number
    std::string statTex = "Asteroids remaining: " + std::to_string(asteroidNr); // create asteroid text 

    // create health text
    int health = Game::Instance()->getMngr()->getHandler(ecs::hdlr::FIGHTER)->getComponent<Health>()->getHP(); // get asteroid number
    std::string hpText = "Health left: " + std::to_string(health); // create asteroid text 

    // create texture from asteroid text
    _statTex = new Texture(sdlutils().renderer(), statTex, sdlutils().fonts().at("ARIAL24"), SDL_Color{ 255, 255, 255, 255 });

    // create texture from health text
    _healthTex = new Texture(sdlutils().renderer(), hpText, sdlutils().fonts().at("ARIAL24"), SDL_Color{ 255, 255, 255, 255 });
}

void PausedState::leave() {
    sdlutils().virtualTimer().resume();
    delete _statTex;
    _statTex = nullptr;

    delete _healthTex;
    _healthTex = nullptr;
}

void PausedState::update() {
    _tex->render((sdlutils().width() - _tex->width()) / 2, (sdlutils().height() - _tex->height()) / 2);

    _statTex->render((sdlutils().width() - _statTex->width()) / 2, (sdlutils().height() - _statTex->height()) / 3);
    _healthTex->render((sdlutils().width() - _healthTex->width()) / 2, 2*(sdlutils().height() - _healthTex->height()) / 3);
    
    if (ih().keyDownEvent()) {
        Game::Instance()->setState(Game::RUNNING);
    }
}

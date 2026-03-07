#include "PausedState.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "../ecs/EntityManager.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Health.h"
#include "../components/Transform.h"
#include <limits>

void PausedState::enter() {
    sdlutils().virtualTimer().pause(); // pause
    
    _tex = &sdlutils().msgs().at("pause"); // get pause text

    //create asteroid text
    int asteroidNr = Game::Instance()->getMngr()->getEntities(ecs::grp::ASTEROIDS).size(); // get asteroid number
    std::string statTex = "Asteroids remaining: " + std::to_string(asteroidNr); // create asteroid text 

    // create health text
    int health = Game::Instance()->getMngr()->getHandler(ecs::hdlr::FIGHTER)->getComponent<Health>()->getHP(); // get asteroid number
    std::string hpText = "Health left: " + std::to_string(health); // create asteroid text 

    // create distance text
    int minDistance = calculateMinDistanceToFighter();
    std::string distanceText = "Min distance to asteroids: " + std::to_string(minDistance);

    // create texture from asteroid text
    _statTex = new Texture(sdlutils().renderer(), statTex, sdlutils().fonts().at("ARIAL24"), SDL_Color{ 255, 255, 255, 255 });

    // create texture from health text
    _healthTex = new Texture(sdlutils().renderer(), hpText, sdlutils().fonts().at("ARIAL24"), SDL_Color{ 255, 255, 255, 255 });

    _distanceTex = new Texture(sdlutils().renderer(), distanceText,sdlutils().fonts().at("ARIAL24"), SDL_Color{ 255, 255, 255, 255 });
}

void PausedState::leave() {
    sdlutils().virtualTimer().resume();
    delete _statTex;
    _statTex = nullptr;

    delete _healthTex;
    _healthTex = nullptr;

    delete _distanceTex;
    _distanceTex = nullptr;
}

void PausedState::update() {
    _tex->render((sdlutils().width() - _tex->width()) / 2, (sdlutils().height() - _tex->height()) / 2);

    _statTex->render((sdlutils().width() - _statTex->width()) / 2, (sdlutils().height() - _statTex->height()) / 3);
    _healthTex->render((sdlutils().width() - _healthTex->width()) / 2, 2*(sdlutils().height() - _healthTex->height()) / 3);
    _distanceTex->render((sdlutils().width() - _distanceTex->width()) / 2, 2.5 * (sdlutils().height() - _distanceTex->height()) / 3);
    
    if (ih().keyDownEvent()) {
        Game::Instance()->setState(Game::RUNNING);
    }
}

int PausedState::calculateMinDistanceToFighter() const {

    auto fighterTr = Game::Instance()->getMngr()->getHandler(ecs::hdlr::FIGHTER)->getComponent<Transform>();
    auto asteroids = Game::Instance()->getMngr()->getEntities(ecs::grp::ASTEROIDS);

    if (asteroids.empty()) 
    {
        return 0;
    }

    // initialize with max value of distance
    float minDist = std::numeric_limits<float>::max();

    for (auto asteroid : asteroids) {
        if (!asteroid->isAlive()) continue;

        auto astTr = asteroid->getComponent<Transform>();

        // distance between fighter and asteroid
        float dist = (fighterTr->getPos() - astTr->getPos()).magnitude();

        if (dist < minDist) {
            minDist = dist;
        }
    }

    return minDist;
}

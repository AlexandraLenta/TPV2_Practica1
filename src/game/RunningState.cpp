#include "RunningState.h"
#include "Game.h"
#include "AsteroidsUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/Collisions.h"
#include "../ecs/EntityManager.h"
#include "../components/Transform.h"
#include "../components/Gun.h"
#include "../components/Health.h"
#include "../components/Image.h"
#include "../components/ImageWithFrames.h"
#include "../sdlutils/Texture.h"

RunningState::RunningState(): _lastAsteroidTime(0)
{
}

void RunningState::enter() {
    _lastAsteroidTime = sdlutils().virtualTimer().currTime();
}

void RunningState::leave() {}

void RunningState::update() {
    auto& ihdlr = ih();

    auto mngr = Game::Instance()->getMngr();
    auto asteroidUtils = Game::Instance()->getAsteroidUtils();
    auto fighterUtils = Game::Instance()->getFighterUtils();

    //a. if there are no asteroids, GameOver
    //if (Game::Instance()->getAsteroidUtils()->nrOfAsteroids() <= 0) {
    //    Game::Instance()->setState(Game::GAMEOVER);
    //}

    auto asteroids = Game::Instance()->getMngr()->getEntities(ecs::grp::ASTEROIDS);
    if (asteroids.empty()) 
    {
        Game::Instance()->setState(Game::GAMEOVER);
        return;
    }

    //b. if press P, pause
    if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_P)) {
        Game::Instance()->setState(Game::PAUSED);
        return;
    }

    //c. Update entities
    Game::Instance()->getMngr()->update();
    Game::Instance()->getMngr()->flush();

    //d. Collisions
        // if fighter -> asteroid, remove health
            // if 0 health, game over
            // if > 0 health, new round

    auto* fighter = Game::Instance()->getMngr()->getHandler(ecs::hdlr::FIGHTER);
    auto* fighterTr = fighter->getComponent<Transform>();
    auto fighterImg = fighter->getComponent<ImageWithFrames>();

    auto& asteroids = Game::Instance()->getMngr()->getEntities(ecs::grp::ASTEROIDS);
    auto gun = Game::Instance()->getMngr()->getHandler(ecs::hdlr::FIGHTER)->getComponent<Gun>();
    auto health = Game::Instance()->getMngr()->getHandler(ecs::hdlr::FIGHTER)->getComponent<Health>();

    for (size_t i = 0; i < asteroids.size(); i++) {
        auto asteroid = asteroids[i];

        if (!asteroid->isAlive()) continue; //if asteroid not alive, we skipe it

        auto astImg = asteroid->getComponent<ImageWithFrames>();
        auto astTr = asteroid->getComponent<Transform>();

        //fighter vs asteroide
        if (Collisions::collidesWithRotation(fighterTr->getPos(), fighterTr->getRot(), fighterTr->getWidth(), fighterTr->getHeight(),
            astTr->getPos(), astTr->getRot(), astTr->getWidth(), astTr->getHeight())) { //huh

            // Quitar una vida al caza
            health->removeHealth(1);

            if (health->getHP() > 0) 
            {
                // Si quedan vidas nueva ronda
                Game::Instance()->setState(Game::NEWROUND);
            }
            else {
                // Si no quedan vidas game over
                Game::Instance()->setState(Game::GAMEOVER);
            }
            return; // salir cuando hay colition con caza
        }
                // if bullet -> asteroid, split asteroid, mark bullet as unused
        for (auto& bullet : *gun) {
            if (!bullet.used) continue;

            SDL_Rect bulletRect = {(int)bullet.pos.getX(),(int)bullet.pos.getY(),bullet.width,bullet.height};
            SDL_Rect asteroidRect = {(int)astTr->getPos().getX(),(int)astTr->getPos().getY(),astTr->getWidth(),astTr->getHeight() };

            if (Collisions::collidesWithRotation (bullet.pos, bullet.rot,bullet.width, bullet.height, astTr->getPos(), astTr->getRot(), astTr->getWidth(), astTr->getHeight())) {
                Game::Instance()->getAsteroidUtils()->split_asteroid(asteroid);

                // arcar bala como no usadas
                bullet.used = false;

                break;  // Salir del bucle de balas para este asteroide
            }
        }
    }

    //e. render entities
    Game::Instance()->getMngr()->render();

    //f. remove dead entities
    Game::Instance()->getMngr()->refresh();

    //g. add asteroid if it's been 5 seconds since the last one
    if (sdlutils().virtualTimer().currRealTime() - _lastAsteroidTime > 5000) {
        Game::Instance()->getAsteroidUtils()->create_asteroids(1);
        _lastAsteroidTime = sdlutils().virtualTimer().currTime();
    }
}
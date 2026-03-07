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
    std::cout << "RUNNIGN\n";
}

void RunningState::leave() {}

void RunningState::update() {
    //a. Update entities (first because we need to add the new entities at the start of the loop)
    //      otherwise the game will detect game over
    updateEntities();

    //b. if there are no asteroids, GameOver
    checkGameOver();

    //c. if press P, pause
    checkPause();

    //d. Collisions
    checkCollisions();

    //e. render entities
    Game::Instance()->getMngr()->render();

    //f. remove dead entities
    Game::Instance()->getMngr()->refresh();

    //g. add asteroid if it's been 5 seconds since the last one
    checkAddAsteroid();
}

void
RunningState::checkGameOver() {
    auto asteroids = Game::Instance()->getMngr()->getEntities(ecs::grp::ASTEROIDS);
    if (asteroids.empty())
    {
        std::cout << "asteroids empty\n";
        Game::Instance()->setState(Game::GAMEOVER);
        return;
    }
}

void
RunningState::checkPause() {
    if (ih().keyDownEvent() && ih().isKeyDown(SDL_SCANCODE_P)) {
        Game::Instance()->setState(Game::PAUSED);
        return;
    }
}

void
RunningState::updateEntities() {
    Game::Instance()->getMngr()->update();
    Game::Instance()->getMngr()->flush();
}

void
RunningState::checkCollisions() {
    auto* fighter = Game::Instance()->getMngr()->getHandler(ecs::hdlr::FIGHTER);
    auto* fighterTr = fighter->getComponent<Transform>();
    auto fighterGun = Game::Instance()->getMngr()->getHandler(ecs::hdlr::FIGHTER)->getComponent<Gun>();
    auto fighterHealth = Game::Instance()->getMngr()->getHandler(ecs::hdlr::FIGHTER)->getComponent<Health>();

    auto& asteroids = Game::Instance()->getMngr()->getEntities(ecs::grp::ASTEROIDS);

    for (size_t i = 0; i < asteroids.size(); i++) {
        auto asteroid = asteroids[i];

        if (!asteroid->isAlive()) continue; // if asteroid not alive, we skip it

        auto astTr = asteroid->getComponent<Transform>();

        // fighter vs asteroid
        if (Collisions::collidesWithRotation(fighterTr->getPos(), fighterTr->getWidth(), fighterTr->getHeight(), fighterTr->getRot(),
            astTr->getPos(), astTr->getWidth(), astTr->getHeight(), astTr->getRot())) {

            std::cout << "FIGHTER & ASTEROID\n";

            // remove 1 hp from fighter
            fighterHealth->removeHealth(1);

            if (fighterHealth->getHP() > 0)
            {
                // if alive, start new round
                Game::Instance()->setState(Game::NEWROUND);
            }
            else {
                // if dead, game over
                Game::Instance()->setState(Game::GAMEOVER);
            }
            return; // if fighter collided with asteroid, dont check for more
        }

        // bullet vs asteroid
        for (auto& bullet : *fighterGun) {
            if (!bullet.used) continue; // if bullet isn't used, don't check

            if (Collisions::collidesWithRotation(bullet.pos, bullet.width, bullet.height, bullet.rot, astTr->getPos(), astTr->getWidth(), astTr->getHeight(), astTr->getRot())) {
                Game::Instance()->getAsteroidUtils()->split_asteroid(asteroid); // if they collided, split the asteroid

                std::cout << "BULLET & ASTEROID\n";
                // mark bullet as unused
                bullet.used = false;

                break;  // don't check mroe collisions for this asteroid
            }
        }
    }
}

void RunningState::checkAddAsteroid() {
    if (sdlutils().virtualTimer().currRealTime() - _lastAsteroidTime > 5000) {
        Game::Instance()->getAsteroidUtils()->create_asteroids(1);
        _lastAsteroidTime = sdlutils().virtualTimer().currTime();
    }
}
#include "RunningState.h"
#include "Game.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/EntityManager.h"

RunningState::RunningState(): _lastAsteroidTime(0)
{
}

void RunningState::enter() {
    _lastAsteroidTime = sdlutils().virtualTimer().currTime();
}

void RunningState::leave() {}

void RunningState::update() {
    auto& ihdlr = ih();
    //a. if there are no asteroids, GameOver
    //if (Game::Instance()->getAsteroidUtils()->nrOfAsteroids() <= 0) {
    //    Game::Instance()->setState(Game::GAMEOVER);
    //}

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
        // if bullet -> asteroid, split asteroid, mark bullet as unused

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
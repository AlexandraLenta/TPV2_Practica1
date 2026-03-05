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
    //a. Si hay 0 asteroides cambia al estado GameOverState
    

    //b. Si el usuario pulsa la tecla P cambia al estado PauseState
    if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_P)) {
        Game::Instance()->setState(Game::PAUSED);
        return;
    }

    //c. Update entidades
    Game::Instance()->getMngr()->update();//COMO SE COGE ESTOOOOOO

    //d. Colisiones

    //e. render
    Game::Instance()->getMngr()->render(); //COMO SE COGE ESTOOOOOO

    //f. refresh
    Game::Instance()->getMngr()->refresh();

    // g) Aniadir asteroide cada 5 segundos
    if (sdlutils().virtualTimer().currRealTime() - _lastAsteroidTime > 5000) {
        _AsteroidsFacade->create_asteroids(1);
        _lastAsteroidTime = sdlutils().virtualTimer().currTime();
    }
}
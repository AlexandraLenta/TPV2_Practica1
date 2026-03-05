#include "RunningState.h"
#include "Game.h"

RunningState::RunningState(): _lastAsteroidTime(0)
{
}

void RunningState::enter() {
    _lastAsteroidTime = sdlutils().virtualTimer().currTime();
}

void RunningState::leave() {}

void RunningState::update() {

    //a. Si hay 0 asteroides cambia al estado GameOverState
    

    //b. Si el usuario pulsa la tecla P cambia al estado PauseState
    if (ihdlr.keyDownEvent() && ihdlr.isKeyDown(SDL_SCANCODE_P)) {
        Game::Instance()->setState(Game::PAUSED);
        return;
    }

    //c. Update entidades
    _entity->getMngr().update();//COMO SE COGE ESTOOOOOO

    //d. Colisiones

    //e. render
    _entity->getMngr().render(); //COMO SE COGE ESTOOOOOO

    //f. refresh
    _entity-> getMngr().refresh();

    // g) Aniadir asteroide cada 5 segundos
    if (sdlutils().virtualTimer() - _lastAsteroidTime > 5000) {
        _AsteroidsFacade->create_asteroids(1);
        _lastAsteroidTime = sdlutils().virtualTimer().currTime();
    }
}
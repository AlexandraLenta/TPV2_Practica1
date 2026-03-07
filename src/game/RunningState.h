#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "AsteroidsFacade.h"

class RunningState :
    public GameState
{

public:
    RunningState();
    virtual ~RunningState() {}

    void enter() override;
    void leave() override;
    void update() override;

private:
    Uint32 _lastAsteroidTime;

    void checkGameOver();
    void checkPause();
    void updateEntities();
    void checkCollisions();
    void checkAddAsteroid();
};


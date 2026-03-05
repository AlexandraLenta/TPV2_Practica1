#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"

class PausedState :
    public GameState
{
public:
    PausedState();
    virtual ~PausedState() {}

    void enter() override;
    void leave() override;
    void update() override;
};


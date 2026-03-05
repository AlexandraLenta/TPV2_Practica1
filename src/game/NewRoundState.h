#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"

class NewRoundState :
    public GameState
{
public:
    NewRoundState() {}
    virtual ~NewRoundState() {}

    void enter() override;
    void leave() override;
    void update() override;

private:
    AsteroidsUtils* _asteroidsUtils;
    FighterFacade* _fighterFacade;
};


#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"

class AsteroidsUtils;
class FighterFacade;

class NewRoundState :
    public GameState
{
public:
    NewRoundState();
    virtual ~NewRoundState() {}

    void enter() override;
    void leave() override;
    void update() override;

private:
    const Texture* _tex;
};


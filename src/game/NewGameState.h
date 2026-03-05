#pragma once
#include "GameState.h"
#include "../sdlutils/Texture.h"

class FighterUtils;

class NewGameState :public GameState
{
public:
    NewGameState();
    virtual ~NewGameState() {}

    void enter() override;
    void leave() override;
    void update() override;

private:
    const Texture* _tex;
};


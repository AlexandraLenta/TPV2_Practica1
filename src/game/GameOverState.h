#pragma once
#include "GameState.h"
class GameOverState :
    public GameState
{
public:
    GameOverState() {};

    void enter() override;
    void leave() override;
    void update() override;
};


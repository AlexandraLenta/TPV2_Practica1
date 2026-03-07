#pragma once
#include "GameState.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/Font.h"

class PausedState :
    public GameState
{
public:
    PausedState() {}
    virtual ~PausedState() {}

    void enter() override;
    void leave() override;
    void update() override;
    int calculateMinDistanceToFighter() const;

private:
    const Texture* _tex;
    const Texture* _statTex;
    const Texture* _healthTex;
    const Texture* _distanceTex;
};


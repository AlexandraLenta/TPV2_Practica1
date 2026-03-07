#include "TeleportOnExit.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

TeleportOnExit::TeleportOnExit() {
}

TeleportOnExit::~TeleportOnExit() {
}

void TeleportOnExit::initComponent() {
    _tr = _ent->getComponent<Transform>();
    assert(_tr != nullptr);
}

void TeleportOnExit::update() {
    Vector2D& pos = _tr->getPos(); // take pos by reference so we can directly modify it
    
    int w = sdlutils().width();
    int h = sdlutils().height();

    // if exits at any border
    if (pos.getX() + _tr->getWidth() < 0 || pos.getX() > w || pos.getY() + _tr->getHeight() < 0 || pos.getY() > h) 
    {
        int side = rand() % 4; // get random border
        switch (side)
        { // we take into account the height and width of the image when teleporting them, otherwise
            case 0: pos = Vector2D(0, SDL_clamp(rand() % (int)(h - _tr->getHeight()), 0, h - _tr->getHeight())); break; // left border
            case 1: pos = Vector2D(w, SDL_clamp(rand() % (int)(h - _tr->getHeight()), 0, h - _tr->getHeight())); break; // right border
            case 2: pos = Vector2D(SDL_clamp(rand() % (int)(w - _tr->getWidth()), 0, w - _tr->getWidth()), 0); break; // upper border
            case 3: pos = Vector2D(SDL_clamp(rand() % (int)(w - _tr->getWidth()), 0, w - _tr->getWidth()), h); break; // lower border
        }
    }
}
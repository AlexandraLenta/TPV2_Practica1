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

    Vector2D pos = _tr->getPos();
    int w = sdlutils().width();
    int h = sdlutils().height();

    if (pos.getX() < 0 || pos.getX() > w ||pos.getY() < 0 || pos.getY() > h) 
    {

        int side = rand() % 4;

        switch (side) 
        {
        case 0: pos = Vector2D(0, rand() % h); break;
        case 1: pos = Vector2D(w, rand() % h); break;
        case 2: pos = Vector2D(rand() % w, 0); break;
        case 3: pos = Vector2D(rand() % w, h); break;
        }
    }
}
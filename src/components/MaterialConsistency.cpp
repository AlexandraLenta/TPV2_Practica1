#include "MaterialConsistency.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

MaterialConsistency::MaterialConsistency() :_consistency(0), _lastCheck(0) {
}

MaterialConsistency::~MaterialConsistency() {
}

void MaterialConsistency::initComponent() {

    _consistency = 10 + rand() % 91; //number between 10 and 100 
    _lastCheck = sdlutils().currRealTime();
}

void MaterialConsistency::update() {

    Uint32 now = sdlutils().currRealTime(); //obtener actual time

    if (now - _lastCheck > 5000) {

        if (rand() % 10 == 0) {

            _consistency--;

            if (_consistency <= 0) {
                _ent->setAlive(false);
            }
        }

        _lastCheck = now;
    }
}

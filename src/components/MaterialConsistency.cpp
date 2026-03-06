#include "MaterialConsistency.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

MaterialConsistency::MaterialConsistency() :_consistency(0), _lastCheck(0) {
}

MaterialConsistency::~MaterialConsistency() {
}

void MaterialConsistency::initComponent() {

    _consistency = 10 + rand() % 91; // random number between 10 and 100 
    _lastCheck = sdlutils().currTime();
}

void MaterialConsistency::update() {

    Uint32 now = sdlutils().currTime(); // obtain current time

    // if its been more than 5 seconds since the last consistency loss 
    if (now - _lastCheck >= 5000) {

        if (rand() % 10 == 0) { // in 1 of 10 cases loses consistency

            _consistency--;

            if (_consistency <= 0) {
                _ent->setAlive(false);
            }
        }
        _lastCheck = now;
    }
}

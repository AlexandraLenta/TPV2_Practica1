#include "AsteroidsUtils.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/FighterCtrl.h"
#include "../components/DeAcceleration.h"
#include "../components/Gun.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Health.h"
#include "../ecs/EntityManager.h"

AsteroidsUtils::AsteroidsUtils() 
{
}

AsteroidsUtils::~AsteroidsUtils() 
{
}

void AsteroidsUtils::create_asteroids(int n) {
    _nrOfAsteroids += n;
}

void AsteroidsUtils::remove_all_asteroids() {
    _nrOfAsteroids = 0;
}

void AsteroidsUtils::split_asteroid(ecs::Entity a) {

    //auto tr = _entity->addComponent<Transform>();

    //_entity->setAlive(false);
}
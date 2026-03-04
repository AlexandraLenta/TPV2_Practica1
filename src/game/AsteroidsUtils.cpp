#include "AsteroidsUtils.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/FighterCtrl.h"
#include "../components/DeAcceleration.h"
#include "../components/Gun.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Health.h"

AsteroidsUtils::AsteroidsUtils() 
{
}

AsteroidsUtils::~AsteroidsUtils() 
{
}

void AsteroidsUtils::create_asteroids(int n) {

}

void AsteroidsUtils::remove_all_asteroids() {

    auto& mngr = Entity ->getMngr();
    auto& asteroids = mngr.getEntities(ecs::grp::ASTEROIDS);
    for (auto a : asteroids) {
        a->setAlive(false);
    }

    mngr.refresh();
}

void AsteroidsUtils::split_astroid(ecs::entity_t a) {

    //auto tr = _entity->addComponent<Transform>();

    //_entity->setAlive(false);
}




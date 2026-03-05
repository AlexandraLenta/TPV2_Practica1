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

    auto& mngr = _entity ->getMngr();//COMO SE COGE ESTA  MIERDAD

    _mngr->getMngr().refresh();//AAAAAAA
}

void AsteroidsUtils::split_astroid(ecs::entity_t a) {

    //auto tr = _entity->addComponent<Transform>();

    //_entity->setAlive(false);
}




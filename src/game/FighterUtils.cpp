#include "FighterUtils.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/FighterCtrl.h"
#include "../components/DeAcceleration.h"
#include "../components/Gun.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Health.h"

FighterUtils::FighterUtils(ecs::EntityManager* mngr) : FighterFacade(), _mngr(mngr) {
	
}

void
FighterUtils::create_fighter() {
	// create fighter
	auto fighter = _mngr->addEntity();
	_mngr->setHandler(ecs::hdlr::FIGHTER, fighter);

	auto& fighterTexture = sdlutils().images().at("fighter");
	
	// add components
	fighter->addComponent<FighterCtrl>(); // controller

	auto tr = fighter->addComponent<Transform>(); // movement
	auto w = fighterTexture.width();
	auto h = fighterTexture.height();
	auto x = (sdlutils().width() - w) / 2.0f;
	auto y = (sdlutils().height() - h) / 2.0f;
	tr->init(Vector2D(x, y), Vector2D(), w, h, 0.0f);

	fighter->addComponent<DeAcceleration>(0.995f, 0.05f); // deacceleration

	fighter->addComponent<Gun>(&sdlutils().images().at("fire")); // gun

	fighter->addComponent<ShowAtOppositeSide>(); // border control

	fighter->addComponent<Image>(fighterTexture); // image

	fighter->addComponent<Health>(3);
}

void 
FighterUtils::reset_fighter() {

}

void 
FighterUtils::reset_lives() {

}

int
FighterUtils::update_lives(int n) {

}
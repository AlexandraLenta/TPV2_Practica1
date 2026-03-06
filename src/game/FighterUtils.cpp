#include "FighterUtils.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/FighterCtrl.h"
#include "../components/DeAcceleration.h"
#include "../components/Gun.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Health.h"
#include "../game/Game.h"

FighterUtils::FighterUtils() : FighterFacade() {
	
}

void
FighterUtils::create_fighter() {
	auto* mngr = Game::Instance()->getMngr();
	
	// create fighter
	_fighter = mngr->addEntity();
	mngr->setHandler(ecs::hdlr::FIGHTER, _fighter);

	auto& fighterTexture = sdlutils().images().at("fighter");
	auto& fireTexture = sdlutils().images().at("fire");
	
	// add components

	auto w = fighterTexture.width();
	auto h = fighterTexture.height();
	auto x = (sdlutils().width() - w) / 2.0f;
	auto y = (sdlutils().height() - h) / 2.0f;

	_fighter->addComponent<Transform>(Vector2D(x, y), Vector2D(0, 0), w, h, 0.0f);

	_fighter->addComponent<FighterCtrl>(); // controller

	_fighter->addComponent<DeAcceleration>(0.995f, 0.005f); // deacceleration

	_fighter->addComponent<Gun>(&fireTexture); // gun

	_fighter->addComponent<ShowAtOppositeSide>(); // border control

	_fighter->addComponent<Image>(&fighterTexture); // image

	_fighter->addComponent<Health>(3); // health
}

void 
FighterUtils::reset_fighter() {
	auto* tex = _fighter->getComponent<Image>()->getTexture();
	auto w = tex->width();
	auto h = tex->height();
	auto x = (sdlutils().width() - w) / 2.0f;
	auto y = (sdlutils().height() - h) / 2.0f;

	_fighter->getComponent<Transform>()->init(Vector2D(x, y), Vector2D(), w, h, 0.0f);
	_fighter->getComponent<Gun>()->reset();
}

void 
FighterUtils::reset_lives() {
	_fighter->getComponent<Health>()->resetHealth();
}

int
FighterUtils::update_lives(int n) {
	_fighter->getComponent<Health>()->removeHealth(n);
	return _fighter->getComponent<Health>()->getHP();
}
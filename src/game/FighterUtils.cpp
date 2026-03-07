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
#include "../ecs/Entity.h"
#include "../ecs/EntityManager.h"

FighterUtils::FighterUtils() : FighterFacade() {
	
}

void
FighterUtils::create_fighter() {
	auto* mngr = Game::Instance()->getMngr();
	
	// create fighter
	auto* fighter = mngr->addEntity();
	mngr->setHandler(ecs::hdlr::FIGHTER, fighter);

	auto& fighterTexture = sdlutils().images().at("fighter");
	auto& fireTexture = sdlutils().images().at("fire");
	
	// add components

	auto w = fighterTexture.width();
	auto h = fighterTexture.height();
	auto x = (sdlutils().width() - w) / 2.0f;
	auto y = (sdlutils().height() - h) / 2.0f;

	fighter->addComponent<Transform>(Vector2D(x, y), Vector2D(0, 0), w, h, 0.0f);

	fighter->addComponent<FighterCtrl>(); // controller

	fighter->addComponent<DeAcceleration>(0.995f, 0.005f); // deacceleration

	fighter->addComponent<Gun>(&fireTexture); // gun

	fighter->addComponent<ShowAtOppositeSide>(); // border control

	fighter->addComponent<Image>(&fighterTexture); // image

	fighter->addComponent<Health>(3); // health
}

void 
FighterUtils::reset_fighter() {
	auto* fighter = Game::Instance()->getMngr()->getHandler(ecs::hdlr::FIGHTER);
	auto* tex = fighter->getComponent<Image>()->getTexture();
	auto w = tex->width();
	auto h = tex->height();
	auto x = (sdlutils().width() - w) / 2.0f;
	auto y = (sdlutils().height() - h) / 2.0f;

	fighter->getComponent<Transform>()->init(Vector2D(x, y), Vector2D(), w, h, 0.0f);
	fighter->getComponent<Gun>()->reset();
}

void 
FighterUtils::reset_lives() {
	auto* fighter = Game::Instance()->getMngr()->getHandler(ecs::hdlr::FIGHTER);
	fighter->getComponent<Health>()->resetHealth();
}

int
FighterUtils::update_lives(int n) {
	auto* fighter = Game::Instance()->getMngr()->getHandler(ecs::hdlr::FIGHTER);
	fighter->getComponent<Health>()->removeHealth(n);
	return fighter->getComponent<Health>()->getHP();
}
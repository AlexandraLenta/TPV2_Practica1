#include "Follow.h"
#include "../ecs/Entity.h"
#include "../game/Game.h"
#include "../game/FighterFacade.h"
#include "../components/Transform.h"

Follow::Follow() {

}

void
Follow::initComponent() {
	_tr = _ent->getComponent<Transform>();
	assert(_tr != nullptr);

	_fighterTr = Game::Instance()->getFighterUtils()->getFighter()->getComponent<Transform>();
	assert(_fighterTr != nullptr);
}

void
Follow::update() {
	auto& v = _tr->getVel();
	auto& p = _tr->getPos();
	auto& q = _fighterTr->getPos();
	v.rotate(v.angle(q - p) > 0 ? 1.0f : -1.0f);
}
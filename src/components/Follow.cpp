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

	Vector2D dir = (q - p).normalize();
	v = dir * v.magnitude();
}
#include "TowardDestination.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"

TowardDestination::TowardDestination() {}

void
TowardDestination::initComponent() {
	_tr = _ent->getComponent<Transform>();
	assert(_tr != nullptr);

	pickDestination();
}

void
TowardDestination::pickDestination() {
	_destination = Vector2D{(float)(rand() % sdlutils().width()), (float)(rand() % sdlutils().height()) }; // choose random destination

	auto& pos = _tr->getPos();
	auto& vel = _tr->getVel();

	Vector2D dir = (_destination - pos).normalize();
	vel = dir * vel.magnitude();
}

void TowardDestination::update() {
	if ((_destination - _tr->getPos()).magnitude() <= _minDistance) {
		pickDestination();
	}
}
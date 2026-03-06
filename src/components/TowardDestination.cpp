#include "TowardDestination.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"

TowardDestination::TowardDestination() {}

void
TowardDestination::initComponent() {
	_tr = _ent->getComponent<Transform>();
	assert(_tr != nullptr);
}

void
TowardDestination::pickDestination() {
	_destination = Vector2D{(float)(rand() % sdlutils().width()), (float)(rand() % sdlutils().height()) }; // choose random destination

	auto& pos = _tr->getPos();
	auto& vel = _tr->getVel();

	vel.rotate(vel.angle(_destination - pos));
}
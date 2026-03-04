#include "ShowAtOppositeSide.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

ShowAtOppositeSide::ShowAtOppositeSide() {

}

ShowAtOppositeSide::~ShowAtOppositeSide() {

}

void ShowAtOppositeSide::initComponent() {
	_tr = _ent->getComponent<Transform>();
	assert(_tr != nullptr);
}

void ShowAtOppositeSide::update() {
	auto& pos = _tr->getPos();
	if (pos.getX() + _tr->getWidth() < 0) {
		pos.setX(sdlutils().width());
	}
	else if (pos.getX() > sdlutils().width()) {
		pos.setX(-_tr->getWidth());
	}

	if (pos.getY() + _tr->getHeight() < 0) {
		pos.setY(sdlutils().height());
	}
	else if (pos.getY() > sdlutils().height()) {
		pos.setY(-_tr->getHeight());
	}
}
#include "Health.h"

#include "../ecs/Entity.h"
#include "../ecs/EntityManager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

Health::Health() : _hp(MAX_HP) {
	_tex = &sdlutils().images().at("heart");
}

Health::~Health() {}

void
Health::initComponent() {
	_hp = MAX_HP;

	_tr = _ent->getComponent<Transform>();
	assert(_tr != nullptr);
}

void
Health::removeHealth() {
	if (--_hp < 0) _hp = 0;
}

void
Health::resetHealth() {
	_hp = MAX_HP;
}

int
Health::getHP() {
	return _hp;
}

void
Health::render() {
	SDL_FRect dest = build_sdlfrect(_tr->getPos(), _tr->getWidth(),
		_tr->getHeight());

	assert(_tex != nullptr);
	_tex->render(dest, _tr->getRot());
}
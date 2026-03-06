#include "Health.h"

#include "../ecs/Entity.h"
#include "../ecs/EntityManager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"

Health::Health(int hp) : _hp(hp), _maxHp(hp) {
}

Health::~Health() {}

void
Health::initComponent() {
	_hp = _maxHp;
	_tex = &sdlutils().images().at("heart");
}

void
Health::removeHealth(int n) {
	_hp -= n;
	if (_hp < 0) _hp = 0;
}

void
Health::resetHealth() {
	_hp = _maxHp;
}

int
Health::getHP() {
	return _hp;
}

void
Health::render() {
	// TODO: render hp amount of hearts

	assert(_tex != nullptr);
	_tex->render(0,0 );

	//sdlutils().width() - _hp * _tex->width()
}
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
	assert(_tex != nullptr);

	for (int i = 0; i < _hp; i++) {
		SDL_FRect dest = build_sdlfrect(i*_tex->width() * _imgScaleFactor, 0, _tex->width() * _imgScaleFactor, _tex->height() * _imgScaleFactor);
		_tex->render(dest);
	}
}
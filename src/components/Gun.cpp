#include "Gun.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"

Gun::Gun(Texture* tex) : _tex(tex) {}

Gun::~Gun() {}

void Gun::initComponent() {
	_tr = _ent->getComponent<Transform>();
	assert(_tr != nullptr);
}

void 
Gun::reset() {
	for (auto& bullet : _bullets) {
		bullet.used = false;
	}
}

void
Gun::update() {
	for (auto& bullet : _bullets) {
		if (bullet.used) {
			bullet.pos = bullet.pos + bullet.vel;
		}
	}

	auto& ihldr = ih();

	if (ihldr.isKeyDown(SDL_SCANCODE_S)) {
		if (sdlutils().virtualTimer().currRealTime() - _lastShotTime >= _cooldown) {
			_lastShotTime = sdlutils().virtualTimer().currRealTime();

			// play sound
			sdlutils().soundEffects().at("gunshot").play("se");

			int bw = 5;
			int bh = 20;
			Vector2D c = _tr->getPos() + Vector2D(_tr->getWidth() / 2.0f, _tr->getHeight() / 2.0f);
			Vector2D bp = c - Vector2D(bw / 2, _tr->getHeight() / 2.0f + 5.0f + bh).rotate(_tr->getRot()) -
				Vector2D(bw / 2, bh / 2);
			Vector2D bv = Vector2D(0, -1).rotate(_tr->getRot()) * (_tr->getVel().magnitude() + 5.0f);
			float br = Vector2D(0, -1).angle(bv);
			shoot(bp, bv, bw, bh, br);
		}
	}
}

void
Gun::render() {
	for (auto& bullet : _bullets) {
		if (bullet.used) {
			SDL_FRect dest = build_sdlfrect(bullet.pos, bullet.width,
				bullet.height);

			assert(_tex != nullptr);
			_tex->render(dest, bullet.rot);
		}
	}
}

void 
Gun::shoot(Vector2D p, Vector2D v, int width, int height, float r) {
	if (_lastUsedBullet >= _bullets.size() - 1) _lastUsedBullet = -1; // if the last used bullet is in the last position, restart from beginning

	for (int i = ++_lastUsedBullet; i < _bullets.size(); i++) {
		if (!_bullets[i].used) {
			_bullets[i].pos = p;
			_bullets[i].vel = v;
			_bullets[i].rot = r;
			_bullets[i].height = height;
			_bullets[i].width = width;
			_bullets[i].used = true;

			_lastUsedBullet = i;
			break;
		}
	}
}
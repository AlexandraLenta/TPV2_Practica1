#include "Gun.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"

Gun::Gun(const Texture* tex) : _tex(tex) {}

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
	auto& ihldr = ih();
	auto& vT = sdlutils().virtualTimer();

	if (ihldr.isKeyDown(SDL_SCANCODE_S)) {
		Uint64 currTime = vT.currTime();
		if (currTime - _lastShotTime >= _cooldown) {
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

			_lastShotTime = currTime;
		}
	}

	for (auto& bullet : _bullets) {
		if (bullet.used) {
			bullet.pos = bullet.pos + bullet.vel;
			if (bullet.pos.getX() + bullet.width <= 0 || bullet.pos.getX() >= sdlutils().width() ||
				bullet.pos.getY() + bullet.height <= 0 || bullet.pos.getY() >= sdlutils().height()) {
				bullet.used = false;
			}
		}
	}
	
}

void
Gun::render() {
	for (auto& bullet : _bullets) {
		if (bullet.used) {
			SDL_FRect dest = build_sdlfrect(bullet.pos, _tex->width(), _tex->height());

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
			return;
		}
	}
}
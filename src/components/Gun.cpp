#include "Gun.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

Gun::Gun(Texture* tex) : _tex(tex) {}

Gun::~Gun() {}

void
Gun::render() {
	//SDL_FRect dest = build_sdlfrect(_tr->getPos(), _tr->getWidth(),
	//	_tr->getHeight());

	assert(_tex != nullptr);
	_tex->render(dest, _tr->getRot());
}

void 
Gun::update() {
	
	auto& ihldr = ih();

	if (ihldr.isKeyDown(SDL_SCANCODE_S)) {
		if (sdlutils().virtualTimer().currRealTime() - _lastShotTime >= _cooldown) {
			_lastShotTime = sdlutils().virtualTimer().currRealTime();

			// play sound
			sdlutils().soundEffects().at("gunshot").play("se");


			int bw = 5;
			int bh = 20;
			Vector2D c = p + Vector2D(w / 2.0f, h / 2.0f);
			Vector2D bp = c - Vector2D(bw / 2, h / 2.0f + 5.0f + bh).rotate(r) -
				Vector2D(bw / 2, bh / 2);
			Vector2D bv = Vector2D(0, -1).rotate(r) * (v.magnitude() + 5.0f);
			float br = Vector2D(0, -1).angle(bv);
			shoot(bp, bd, bw, bh, br);
		}
	}
}
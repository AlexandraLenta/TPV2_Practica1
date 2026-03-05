#include "FighterCtrl.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../ecs/EntityManager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Image.h"
#include "Transform.h"

FighterCtrl::FighterCtrl() :
	_tr(nullptr) {
}

FighterCtrl::~FighterCtrl() {
}

void FighterCtrl::initComponent() {
	_tr = _ent->getComponent<Transform>();
	assert(_tr != nullptr);
}

void FighterCtrl::update() {
	auto& ihldr = ih();

	auto& vel_ = _tr->getVel();
	auto rot = _tr->getRot();

	if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
		_tr->setRot(rot + 5.0f);

		// also rotate the fighter so it looks in the same
		// direction where it moves
		//
		vel_ = vel_.rotate(5.0f);
	}
	else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
		_tr->setRot(rot - 5.0f);

		// also rotate the fighter so it looks in the same
		// direction where it moves
		//
		vel_ = vel_.rotate(-5.0f);
	}
	else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // increase speed
		Vector2D new_vel = vel_ + Vector2D(0, -1).rotate(rot) * _thrust;

		if (new_vel.magnitude() > _speedLimit) {
			new_vel = new_vel.normalize() * _speedLimit;
		}

		vel_ = new_vel;

		// play sound
		sdlutils().soundEffects().at("thrust").play("se");
	}
}

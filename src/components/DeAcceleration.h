// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"
#include <cassert>

class DeAcceleration : public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::DEACCELERATION)

	DeAcceleration() :
	_amount() {
	}

	DeAcceleration(float da, float l) :
		_amount(da), _limit(l) {
	}

	virtual ~DeAcceleration() {
	}

	void init(float da, float l) {
		_amount = da;
		_limit = l;
		_tr = _ent->getComponent<Transform>();
		assert(_tr != nullptr);
	}

	float getDeaccelerationAmount() {
		return _amount;
	}

	void update() override {
		Vector2D res = _tr->getVel() * _amount;
		if (res.getX() <= _limit && res.getY() <= _limit)
			_tr->setVel({ 0,0 });
		else 
			_tr->setVel(_tr->getVel() * _amount);
	}

private:
	float _amount;
	float _limit;
	Transform* _tr;
};


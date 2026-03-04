#pragma once
#include "../ecs/Component.h"

class Transform;

class FighterCtrl : public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::FIGHTERCTRL)

		FighterCtrl();
	virtual ~FighterCtrl();
	void initComponent() override;
	void update() override;

private:
	Transform* _tr;

	float _thrust = 0.2f;
	float _speedLimit = 3.0f;
};


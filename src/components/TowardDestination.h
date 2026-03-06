#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"

class Transform;

class TowardDestination : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::TOWARDDESTINATION)

		TowardDestination();
	void initComponent() override;

private:
	Vector2D _destination;
	Transform* _tr;

	void pickDestination();
};


#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <cassert>

static const int MAX_HP = 3;

class Health : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::TRANSFORM)

		Health();
	~Health();

	void initComponent() override;

	void resetHealth();
	void removeHealth();

	int getHP();

	void render() override;

private:
	int _hp;
	Transform* _tr;
	const Texture* _tex;
};


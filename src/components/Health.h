#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <cassert>

class Health : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::TRANSFORM)

		Health(int hp);
	~Health();

	void initComponent() override;

	void resetHealth();
	void removeHealth(int n);

	int getHP();

	void render() override;

private:
	int _hp;
	int _maxHp;
	Transform* _tr;
	const Texture* _tex;
};


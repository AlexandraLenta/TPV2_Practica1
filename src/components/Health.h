#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <cassert>
#include "../sdlutils/Texture.h"

class Transform;

class Health : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::cmp::HEALTH)

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
	const Texture* _tex;
	float _imgScaleFactor = 0.3f;
};


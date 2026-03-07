#pragma once
#include "../ecs/Component.h"
#include <array>
#include "../utils/Vector2D.h"
#include "../sdlutils/Texture.h"

class Transform;

class Gun : public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::GUN)
	
	Gun(const Texture* tex);
	void initComponent() override;
	
	void update() override;
	void render() override;

	struct Bullet {
		bool used = false;
		Vector2D pos;
		Vector2D vel;
		int width = 0;
		int height = 0;
		float rot = 0;
	};

	constexpr static uint8_t _max_bullets = 20;
	typedef std::array<Bullet, _max_bullets> bullets_array_t;
	typedef bullets_array_t::iterator iterator;

	void reset();

	iterator begin() {
		return _bullets.begin();
	}
	iterator end() {
		return _bullets.end();
	}

private:
	void shoot(Vector2D p, Vector2D v, int width, int height, float r);
	
	bullets_array_t _bullets;
	float _cooldown = 250.0f;
	float _lastShotTime = 0.0f;

	int _lastUsedBullet = -1;

	const Texture* _tex;
	Transform* _tr;
};


#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../components/Transform.h"
#include <cassert>

class ShowAtOppositeSide : public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::SHOWATOPPOSITE);

	ShowAtOppositeSide();
	~ShowAtOppositeSide();

	void initComponent() override;

	void update() override;

private:
	Transform* _tr;
};
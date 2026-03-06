#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include "../components/Transform.h"

class TeleportOnExit : public ecs::Component {
public:

    __CMPID_DECL__(ecs::cmp::TELEPORTONEXIT);

    TeleportOnExit();
    virtual ~TeleportOnExit();

    void initComponent() override;
    void update() override;

private:
    Transform* _tr;
};


#pragma once
#include "../ecs/Component.h"

class Transform;

class Follow : public ecs::Component
{
public:
    __CMPID_DECL__(ecs::cmp::FOLLOW)

    Follow();
    void initComponent() override;
    void update() override;

private:
    Transform* _tr;
    Transform* _fighterTr;
    float _rotateSpeed;
};


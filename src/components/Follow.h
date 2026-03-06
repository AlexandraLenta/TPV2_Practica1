#pragma once
#include "../ecs/Component.h"
#include "Transform.h"

class Follow : public ecs::Component
{
public:
    __CMPID_DECL__(ecs::cmp::FOLLOW)
    Follow(float turnSpeed = 1.0f);
    void initComponent() override;
    void update() override;

private:
    Transform* _tr;
    Transform* _fighterTr;
    float _rotateSpeed;

};


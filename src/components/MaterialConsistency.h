#pragma once
#include "../ecs/Component.h"

class MaterialConsistency : public ecs::Component {
public:

    __CMPID_DECL__(ecs::cmp::MATERIALCONSISTENCY);

    MaterialConsistency();
    virtual ~MaterialConsistency();

    void initComponent() override;
    void update() override;

private:
    int _consistency;
    Uint32 _lastCheck;
};


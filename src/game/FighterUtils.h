#pragma once
#include "FighterFacade.h"
#include "../ecs/EntityManager.h"
#include "../ecs/Entity.h"

class FighterUtils :
    public FighterFacade
{
public:
    FighterUtils(ecs::EntityManager* mngr);

    void create_fighter() override;
    void reset_fighter() override;
    void reset_lives() override;
    int update_lives(int n) override;

private:
    ecs::EntityManager* _mngr;
    ecs::Entity* _fighter;
};


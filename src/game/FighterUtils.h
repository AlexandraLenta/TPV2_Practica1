#pragma once
#include "FighterFacade.h"
#include "../ecs/EntityManager.h"
#include "../ecs/Entity.h"

class FighterUtils :
    public FighterFacade
{
public:
    FighterUtils();

    void create_fighter() override;
    void reset_fighter() override;
    void reset_lives() override;
    int update_lives(int n) override;
    ecs::Entity* getFighter() override {
        return _fighter;
    }

private:
    ecs::EntityManager* _mngr;
    ecs::Entity* _fighter;
};
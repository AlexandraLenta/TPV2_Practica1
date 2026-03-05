#pragma once
#include "AsteroidsFacade.h"
#include "../ecs/Entity.h"

class AsteroidsUtils : public AsteroidsFacade {
public:
    AsteroidsUtils();
    virtual ~AsteroidsUtils();

    void create_asteroids(int n) override;
    void remove_all_asteroids() override;
    void split_asteroid(ecs::Entity a) override;

private:

    ecs::EntityManager* _mngr;
    ecs::Entity* _entity;

};


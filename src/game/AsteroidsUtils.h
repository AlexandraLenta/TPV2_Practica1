#pragma once
#include "AsteroidsFacade.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"

class AsteroidsUtils : public AsteroidsFacade {
public:
    AsteroidsUtils(ecs::EntityManager* mngr);
    virtual ~AsteroidsUtils();

    void create_asteroids(int n) override;
    void remove_all_asteroids() override;
    void split_asteroid(ecs::Entity a) override;

private:
    ecs::EntityManager* _mngr;
    ecs::Entity* _entity;

    ecs::Entity* spawnAsteroid(const Vector2D& pos,const Vector2D& vel,int generations,
        bool follow,
        bool toward,
        bool teleport,
        bool material,
        int materialValue
    );

};


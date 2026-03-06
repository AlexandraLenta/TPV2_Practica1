#pragma once
#include "AsteroidsFacade.h"
#include "../ecs/Entity.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/Texture.h"

class AsteroidsUtils : public AsteroidsFacade {
public:
    AsteroidsUtils();
    virtual ~AsteroidsUtils();

    void create_asteroids(int n) override;
    void remove_all_asteroids() override;
    void split_asteroid(ecs::Entity* a) override;

private:
    const Texture* _asteroidTex;
    const Texture* _goldAsteroidTex;
    int _rows, _cols;

    ecs::Entity* spawnAsteroid(const Vector2D& pos,const Vector2D& vel,int generations);

};


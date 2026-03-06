#include "AsteroidsUtils.h"
#include "../components/Transform.h"
#include "../components/TeleportOnExit.h"
#include "../components/MaterialConsistency.h"
#include "../components/Follow.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/ImageWithFrames.h"
#include "../components/Generations.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/TowardDestination.h"
#include "../game/Game.h"
#include "../ecs/EntityManager.h"
#include "../ecs/Entity.h"


AsteroidsUtils::AsteroidsUtils() {
    _asteroidTex = &sdlutils().images().at("asteroid");
    _goldAsteroidTex = &sdlutils().images().at("asteroid_gold");
    _rows = 5;
    _cols = 6;
}

AsteroidsUtils::~AsteroidsUtils() 
{

}

void AsteroidsUtils::create_asteroids(int n) {

    auto& rng = sdlutils().rand();
    int width = sdlutils().width();
    int height = sdlutils().height();

    Vector2D screenCenter(width / 2, height / 2);

    for (int i = 0; i < n; ++i) { // for each asteroid

        // --------- TRANSFORM -------------
        int side = rng.nextInt(0, 4); // take border

        Vector2D spawnPos;

        if (side == 0) //left
            spawnPos = { 0.0f, (float)rng.nextInt(0, height) };
        
        else if (side == 1) //right
            spawnPos = { (float)width, (float)rng.nextInt(0, height) };
        
        else if (side == 2) //top
            spawnPos = { (float)rng.nextInt(0, width), 0.0f };
        
        else //bottom
            spawnPos = { (float)rng.nextInt(0, width), (float)height };
        

        Vector2D centerPos = (screenCenter + Vector2D{(float)rng.nextInt(-100, 101), (float)rng.nextInt(-100, 101)}).normalize();

        float speed = rng.nextInt(1, 10)/10.0f;
        Vector2D velocity = (centerPos - spawnPos) * speed; // asteroid speed

        // --------- GENERATIONS -------------

        int generations = rng.nextInt(1, 4); // generate generation

        spawnAsteroid(spawnPos, velocity, generations);
    }
}

void AsteroidsUtils::remove_all_asteroids() {
    auto& asteroids = Game::Instance()->getMngr()->getEntities(ecs::grp::ASTEROIDS);

    for (auto* e : asteroids) {
        e->setAlive(false);
    }
}

ecs::Entity* AsteroidsUtils::spawnAsteroid(const Vector2D& pos, const Vector2D& vel, int generations) {
    auto& rng = sdlutils().rand();

    auto* mngr = Game::Instance()->getMngr();

    // create entity
    ecs::Entity* asteroid = mngr->addEntity();
    mngr->setHandler(ecs::hdlr::ASTEROID, asteroid);

    float w = _asteroidTex->width();
    float h = _asteroidTex->height();

    asteroid->addComponent<Transform>(pos, vel, (w / _cols) * generations/2, (h / _rows) * generations / 2, 0.0f); // transform
    asteroid->addComponent<Generations>(generations); // generations

    if (rng.nextInt(0, 2)) { // decide border behavior, if its 1 (true) add show at opposite side
        asteroid->addComponent<ShowAtOppositeSide>();
    }
    else { // if false (0) add teleport on exit
        asteroid->addComponent<TeleportOnExit>();
    }

    const Texture* texToUse = _asteroidTex;

    int follow = rng.nextInt(0, 3);
    if (!follow) { // decide route. if 0 (false) go towards destination
        asteroid->addComponent<TowardDestination>();
        texToUse = _goldAsteroidTex;
    }
    else if (follow == 1) { // if 1 follow player
        asteroid->addComponent<Follow>();
    } // if 2 (none of the above), dont add anything

    asteroid->addComponent<ImageWithFrames>(texToUse, _rows, _cols); // animation/image & frames

    if (rng.nextInt(0, 2)) { // if 1 (true) add material consistency
        asteroid->addComponent<MaterialConsistency>(10 + rand() % 91); // random number between 10 and 100
    } // else don't add anything

    return asteroid;
}

void AsteroidsUtils::split_asteroid(ecs::Entity* a) {
    const auto& genComp = a->getComponent<Generations>();

    genComp->decreaseGeneration();

    auto generations = genComp->getGenerations();
    
    if (generations <= 0)
        return;

    const auto& tr = a->getComponent<Transform>();
    auto p = tr->getPos();
    auto v = tr->getVel();
    auto w = tr->getWidth();
    auto h = tr->getHeight();

    int r = sdlutils().rand().nextInt(0, 360);
    Vector2D pos = p + v.rotate(r) * 2 * std::max(w, h);
    Vector2D vel = v.rotate(r) * 1.1f;

    ecs::Entity* asteroid = spawnAsteroid(pos, vel, generations);

    if (a->hasComponent<MaterialConsistency>()) {
        asteroid->addComponent<MaterialConsistency>(a->getComponent<MaterialConsistency>()->getConsistency());
    }
    else {
        asteroid->removeComponent<MaterialConsistency>();
    }
}

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


AsteroidsUtils::AsteroidsUtils() {}

AsteroidsUtils::~AsteroidsUtils() 
{
}

void AsteroidsUtils::create_asteroids(int n) {
    //_nrOfAsteroids += n;

    auto& rng = sdlutils().rand();
    int width = sdlutils().width();
    int height = sdlutils().height();

    Vector2D screenCenter(width / 2, height / 2);

    for (int i = 0; i < n; ++i) {
        int side = rng.nextInt(0, 4);// coger borde

        Vector2D spawnPos;

        if (side == 0) //left
        {
            spawnPos = {
            0.0f, (float)rng.nextInt(0, height) 
        };
        }
        else if (side == 1) //right
        {
            spawnPos = { (float)width, (float)rng.nextInt(0, height) };
        }
        else if (side == 2) //top
        {
            spawnPos = { (float)rng.nextInt(0, width), 0.0f };
        }
        else //boton
        {
            spawnPos = { (float)rng.nextInt(0, width), (float)height };
        }
        Vector2D direction = (screenCenter - spawnPos).normalize();// vector pal centro

        float speed = rng.nextInt(1, 6);
        Vector2D velocity = direction * speed;

        int generations = rng.nextInt(1, 4);

        bool follow = rng.nextInt(0, 2) == 0; //50% prob de seguir al caza
        bool toward = (!follow && rng.nextInt(0, 2) == 0); // Si no follow, 50% de toward
        bool teleport = rng.nextInt(0, 2) == 0; // 50% de teletransportarse

        bool material = rng.nextInt(0, 2) == 0;// 50% de tener consistencia
        int materialValue = material ? rng.nextInt(10, 101) : 0;

    }
}

void AsteroidsUtils::remove_all_asteroids() {
    //_nrOfAsteroids = 0;

    auto& asteroids = Game::Instance()->getMngr()->getEntities(ecs::grp::ASTEROIDS);

    for (auto* e : asteroids) {
        e->setAlive(false);
    }
}

void AsteroidsUtils::split_asteroid(ecs::Entity* a) {

    //auto tr = _entity->addComponent<Transform>();
   //_entity->setAlive(false);
    auto* tr = a->getComponent<Transform>();
    auto* g = a->getComponent<Generations>();
    int gen = g->getGenerations();
    
    a->setAlive(false);// asteroid original muere

    Vector2D pos = tr->getPos();
    Vector2D vel = tr->getVel();

    float w = tr->getWidth();
    float h = tr->getHeight();

    bool follow = a->hasComponent<Follow>();
    bool toward = a->hasComponent<TowardDestination>();
    bool teleport = a->hasComponent<TeleportOnExit>();

    bool material = a->hasComponent<MaterialConsistency>();
    int materialValue = 0;

    if (material) 
    {
        materialValue = a->getComponent<MaterialConsistency>()->getConsistency(); //huuh
    }

    auto& rng = sdlutils().rand();

    for (int i = 0; i < 2; ++i) 
    {

        float angle = rng.nextInt(-30, 30); //angel random btween 30 and -30

        Vector2D newVel = vel.rotate(angle) * 1.1f; //rotar aleatoriamente y aumentada un 10%
        Vector2D offset(rng.nextInt(-(int)w, (int)w),rng.nextInt(-(int)h, (int)h)); // offset basado en el tamaño

        Vector2D newPos = pos + offset;

    }

}

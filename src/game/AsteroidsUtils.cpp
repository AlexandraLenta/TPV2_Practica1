#include "AsteroidsUtils.h"
#include "../components/Transform.h"
#include "../components/TeleportOnExit.h"
#include "../components/MaterialConsistency.h"
#include "../components/Follow.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/ImageWithFrames.h"
#include "../components/Generations.h"
#include "../components/ShowAtOppositeSide.h"


AsteroidsUtils::AsteroidsUtils() 
{
}

AsteroidsUtils::~AsteroidsUtils() 
{
}

void AsteroidsUtils::create_asteroids(int n) {
    //_nrOfAsteroids += n;

    auto& rng = sdlutils().rand();
    int width = sdlutils().width();
    int height = sdlutils().height();

    Vector2D screenCenter(width / 2.0f, height / 2.0f);

    for (int i = 0; i < n; ++i) {
        int side = rng.nextInt(0, 4);// coger borde

        Vector2D spawnPos;

        if (side == 0) 
            spawnPos = {
            0.0f, (float)rng.nextInt(0, height) 
        };
        else if (side == 1) 
        {
            spawnPos = { (float)width, (float)rng.nextInt(0, height) };
        }
        else if (side == 2) 
        {
            spawnPos = { (float)rng.nextInt(0, width), 0.0f };
        }
        else 
        {
            spawnPos = { (float)rng.nextInt(0, width), (float)height };
        }
        Vector2D direction = (screenCenter - spawnPos).normalize();// vector pal zona central

        float speed = rng.nextInt(1, 6);
        Vector2D velocity = direction * speed;

        int generations = rng.nextInt(1, 4);

        bool follow = rng.nextInt(0, 2) == 0;
        bool toward = (!follow && rng.nextInt(0, 2) == 0);
        bool teleport = rng.nextInt(0, 2) == 0;

        bool material = rng.nextInt(0, 2) == 0;
        int materialValue = material ? rng.nextInt(10, 101) : 0;

        spawnAsteroid(spawnPos,velocity,generations,follow,toward,teleport,material,materialValue);
    }
}

void AsteroidsUtils::remove_all_asteroids() {
    //_nrOfAsteroids = 0;

}

void AsteroidsUtils::split_asteroid(ecs::Entity a) {

    //auto tr = _entity->addComponent<Transform>();

    //_entity->setAlive(false);
}
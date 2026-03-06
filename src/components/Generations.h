#pragma once
#include "../ecs/Component.h"

class Generations : public ecs::Component {
public:

    __CMPID_DECL__(ecs::cmp::GENERATIONS);

    Generations(int g = 0);
    virtual ~Generations();

    int getGenerations();
    void setGenerations(int g);
    void increaseGeneration();

private:
    int _generations;
};

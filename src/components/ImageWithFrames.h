#pragma once
#include "../ecs/Component.h"
#include "../components/Transform.h"

class ImageWithFrames : public ecs::Component
{
public:

    __CMPID_DECL__(ecs::cmp::IMAGEWITHFRAMES);

    ImageWithFrames(Texture* tex, int rows, int cols);
    virtual ~ImageWithFrames();

    void initComponent() override;

private:

    Transform* _tr;

};


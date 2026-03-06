#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"

class Transform;

const int FRAME_TIME = 50;

class ImageWithFrames : public ecs::Component
{
public:

    __CMPID_DECL__(ecs::cmp::IMAGEWITHFRAMES);

    ImageWithFrames(Texture* tex, int rows, int cols);
    virtual ~ImageWithFrames();

    void initComponent() override;

private:
    int _rows, _cols, _frame, _lastChangeTime;
    Texture* _tex;
    Transform* _tr;

};


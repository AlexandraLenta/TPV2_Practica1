#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include <vector>

class Transform;

const int FRAME_TIME = 50;

class ImageWithFrames : public ecs::Component
{
public:

    __CMPID_DECL__(ecs::cmp::IMAGEWITHFRAMES);

    ImageWithFrames(const Texture* tex, int rows, int cols);
    virtual ~ImageWithFrames();

    void initComponent() override;

    void render() override;
    void update() override;

private:
    int _rows, _cols, _frame, _lastChangeTime = 0;
    const Texture* _tex;
    Transform* _tr;
    std::vector<SDL_FRect> _srcRects;
};


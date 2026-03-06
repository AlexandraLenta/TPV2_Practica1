#include "ImageWithFrames.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

ImageWithFrames::ImageWithFrames(Texture* tex, int rows, int cols) : _tex(tex), _rows(rows),_cols(cols),_frame(0), _lastChangeTime(0)
{
}

ImageWithFrames::~ImageWithFrames() {
}

void
ImageWithFrames::initComponent() {

}
#include "ImageWithFrames.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

ImageWithFrames::ImageWithFrames(Texture* tex, int rows, int cols) :_tr(nullptr),_tex(tex),_rows(rows),_cols(cols),_frame(0),_lastTime(0)
{
}

ImageWithFrames::~ImageWithFrames() {
}

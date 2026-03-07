#include "ImageWithFrames.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"

ImageWithFrames::ImageWithFrames(const Texture* tex, int rows, int cols) : _tex(tex), _rows(rows),_cols(cols), _frame(0)
{
	_frameW = _tex->width() / _cols;
	_frameH = _tex->height() / _rows;

	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {
			_srcRects.push_back(SDL_FRect{i * _frameW, j* _frameH, _frameW, _frameH });
		}
	}
}

ImageWithFrames::~ImageWithFrames() {
}

void
ImageWithFrames::initComponent() {
	_tr = _ent->getComponent<Transform>();
	assert(_tr != nullptr);
}

void
ImageWithFrames::update() {
	if (sdlutils().virtualTimer().currTime() - _lastChangeTime >= FRAME_TIME) {
		// advance frame
		_frame = (_frame + 1) % (_cols * _rows);
		_lastChangeTime = sdlutils().virtualTimer().currTime();
	}
}

void
ImageWithFrames::render() {
	int row = _frame / _cols;
	int col = _frame % _cols;
	SDL_FRect src = build_sdlfrect((float)(col * _frameW), (float)(row * _frameH), _frameW, _frameH);

	// dest rect for the current frame
	SDL_FRect dest = build_sdlfrect(_tr->getPos(), _tr->getWidth(), _tr->getHeight());
	// render the src frame rect to the dest rect
	//_tex->render(_srcRects[_frame], dest);
	_tex->render(src, dest);
}
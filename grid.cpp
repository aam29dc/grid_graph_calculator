#include "grid.hpp"

Grid* Grid::_grid = nullptr;

Grid::Grid() {
	_shiftx = 0.0f;
	_shifty = 0.0f;
	_zoom = -10.0f;
	_scale = 10;
	_iters = 200;

	width = 1920;
	height = 1080;
	window = nullptr;
	renderer = nullptr;
}

Grid* Grid::getGrid(void) {
	if (_grid == nullptr) _grid = new Grid;
	return _grid;
}

void Grid::drawFunction(float(*func)(float x, const float k), const float k) const {
	SDL_FPoint curr = { float((-_scale) + _shiftx), 0.0f};

	float dx = (float)_scale*2.0f/_iters;	//width
	//defines start of x and width of dx for zoom ranges
	if (_zoom > 0) {
		curr.x = float(((-_scale) * _zoom) + _shiftx);
		dx = (_scale * 2.0f * _zoom) / _iters;
	}
	else if (_zoom < 0) {
		curr.x = float((-_scale) / (-_zoom) + _shiftx);
		dx = ((_scale) * 2.0f / (-_zoom)) / _iters;
	}

	curr.y = func(curr.x, k);
	
	SDL_FPoint prev;
	float zoomS = _zoom;	// zoom save _zoom variable, if zoom is 0: use 1, and if negative: use negated reciprocal

	for (unsigned int i = 0; i < _iters; i++) {
		prev = curr;
		curr.x += dx;
		curr.y = func(curr.x, k);

		if (zoomS == 0) {
			zoomS = 1.0f;
		}
		else if (zoomS < 0) {
			zoomS = 1.0f / (-zoomS);
		}

		// grid coordinates to screen coordinates:
		// shiftx/shifty back, then scale back to normal range [-1,1], then scale to width/height of screen, then shift to center of screen
		SDL_RenderDrawLineF(renderer,
			((prev.x - _shiftx) / (_scale * zoomS) * (width / 2.0f)) + (width / 2.0f),
			-((prev.y - _shifty) / (_scale * zoomS) * (height / 2.0f)) + (height / 2.0f),

			((curr.x - _shiftx) / (_scale * zoomS) * (width / 2.0f)) + (width / 2.0f),
			-((curr.y - _shifty) / (_scale * zoomS) * (height / 2.0f)) + (height / 2.0f));
	}
}

void Grid::drawAxises(void) const {
	SDL_FPoint origin = { _shiftx, _shifty };

	float zoomS = _zoom;

	if (zoomS == 0) zoomS = 1.0f;
	else if (zoomS < 0) zoomS = -1.0f / zoomS;

	//draw x axis
	SDL_RenderDrawLineF(renderer,
		0,
		(height / 2.0f) + (_shifty * ((height / 2.0f) / _scale / zoomS)),
		float(width),
		(height / 2.0f) + (_shifty * ((height / 2.0f) / _scale / zoomS))
	);

	//draw y axis
	SDL_RenderDrawLineF(renderer,
		(width / 2.0f) - (_shiftx * ((width / 2.0f) / _scale / zoomS)),
		0,
		(width / 2.0f) - (_shiftx * ((width / 2.0f) / _scale / zoomS)),
		float(height)
	);
}

bool Grid::input(void) {
	SDL_Event e;
	bool quit = false;
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		//User presses a key
		else if (e.type == SDL_KEYDOWN)
		{
			//Select surfaces based on key press
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				_shifty += _scale / 100.0f;
				break;
			case SDLK_DOWN:
				_shifty += -_scale / 100.0f;
				break;
			case SDLK_LEFT:
				_shiftx += _scale / 100.0f;
				break;
			case SDLK_RIGHT:
				_shiftx += -_scale / 100.0f;
				break;
			case SDLK_MINUS: case SDLK_UNDERSCORE:
				_zoom += -_scale / 10.0f;
				break;
			case SDLK_EQUALS: case SDLK_PLUS:
				_zoom += _scale / 10.0f;
				break;
			case SDLK_ESCAPE:
				quit = true;
				break;
			case SDLK_o: case SDLK_0:
				_shiftx = 0.0f;
				_shifty = 0.0f;
				_zoom = -10.0f;
				_scale = 10;
				break;
			default:
				break;
			}
		}
	}

	return quit;
}

unsigned int Grid::getWidth(void) const {
	return width;
}

unsigned int Grid::getHeight(void) const {
	return height;
}
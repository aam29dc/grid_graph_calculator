#include "grid.hpp"

Grid* Grid::_grid = nullptr;
TTF_Font* font;

Grid::Grid() {
	_shiftx = 0.0f;
	_shifty = 0.0f;
	_zoom = 1.0f;
	_iters = 200;

	width = 800;
	height = 600;
	window = nullptr;
	renderer = nullptr;
}

Grid* Grid::getGrid(void) {
	if (_grid == nullptr) _grid = new Grid;
	return _grid;
}

void Grid::drawAxisNumbers(void) {
	displayString(std::to_string((-_zoom) + _shiftx), -1.0f, 0.0f); 	//negative x-axis
	displayString(std::to_string((_zoom) + _shiftx), 0.75f, 0.0f); 		//positive x-axis
	displayString(std::to_string((-_zoom) + _shifty), 0.0f, -0.925f);	//negative y-axis
	displayString(std::to_string((_zoom) + _shifty), 0.0f, 1.0f);		//positive y-axis
}

void Grid::displayString(std::string str, const float xpos, const float ypos) const {
	SDL_Color color = { 255, 255, 255 };

	SDL_Surface* surfaceMsg = TTF_RenderText_Solid(font, str.c_str(), color);
	if (surfaceMsg == NULL)	{
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << "\n";
	}

	SDL_Texture* msg = SDL_CreateTextureFromSurface(renderer, surfaceMsg);
	if (msg == NULL) {
		std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << "\n";
	}

	SDL_FRect msg_rect;
	msg_rect.x = ((xpos+1.0f)/2.0f)*(float)width;
	msg_rect.y = ((-ypos+1.0f)/2.0f)*(float)height;
	msg_rect.w = str.length()*12.0f;
	msg_rect.h = 24.0f;

	SDL_RenderCopyF(renderer, msg, NULL, &msg_rect);

	SDL_FreeSurface(surfaceMsg);
	SDL_DestroyTexture(msg);
}

void Grid::drawFunction(float(*func)(float x, const float k), const float k) const {
	SDL_FPoint curr = { float((-1.0f) + _shiftx), 0.0f};

	//defines start of x and width of dx for zoom ranges
	curr.x = -_zoom + _shiftx;
	float dx = (2.0f * _zoom) / _iters;

	curr.y = func(curr.x, k);
	
	SDL_FPoint prev;

	for (unsigned int i = 0; i < _iters; i++) {
		prev = curr;
		curr.x += dx;
		curr.y = func(curr.x, k);

		// grid coordinates to screen coordinates:
		// shiftx/shifty back, then scale back to normal range [-1,1], then scale to width/height of screen, then shift to center of screen
		SDL_RenderDrawLineF(renderer,
			((prev.x - _shiftx) / _zoom * (width / 2.0f)) + (width / 2.0f),
			-((prev.y - _shifty) / _zoom * (height / 2.0f)) + (height / 2.0f),
			((curr.x - _shiftx) / _zoom * (width / 2.0f)) + (width / 2.0f),
			-((curr.y - _shifty) / _zoom * (height / 2.0f)) + (height / 2.0f));
	}
}

void Grid::drawAxises(void) const {
	SDL_FPoint origin = { _shiftx, _shifty };

	//draw x axis
	SDL_RenderDrawLineF(renderer,
		0,
		(height / 2.0f) + (_shifty * ((height / 2.0f) / _zoom)),
		float(width),
		(height / 2.0f) + (_shifty * ((height / 2.0f) / _zoom))
	);

	//draw y axis
	SDL_RenderDrawLineF(renderer,
		(width / 2.0f) - (_shiftx * ((width / 2.0f) / _zoom)),
		0,
		(width / 2.0f) - (_shiftx * ((width / 2.0f) / _zoom)),
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
				_shifty += 0.1f;
				break;
			case SDLK_DOWN:
				_shifty += -0.1f;
				break;
			case SDLK_LEFT:
				_shiftx += -0.1f;
				break;
			case SDLK_RIGHT:
				_shiftx += 0.1f;
				break;
			case SDLK_MINUS: case SDLK_UNDERSCORE:
				_zoom += -0.1f;
				break;
			case SDLK_EQUALS: case SDLK_PLUS:
				_zoom += 0.1f;
				break;
			case SDLK_ESCAPE:
				quit = true;
				break;
			case SDLK_o: case SDLK_0:
				_shiftx = 0.0f;
				_shifty = 0.0f;
				_zoom = 1.0f;
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

unsigned int Grid::getIters(void) const {
	return _iters;
}

void Grid::setIters(unsigned int val) {
	_iters = val;
}

float Grid::getShiftx(void) const {
	return _shiftx;
}

float Grid::getShifty(void) const {
	return _shifty;
}

float Grid::getZoom(void) const {
	return _zoom;
}
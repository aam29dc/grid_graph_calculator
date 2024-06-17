#ifndef GRID
#define GRID

#include <SDL.h>
#include <iostream>

class Grid {
private:
	float _shiftx;
	float _shifty;
	float _zoom;
	int _scale;
	unsigned int _iters;
	static Grid* _grid;

	unsigned int width;
	unsigned int height;
public:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Grid();
	static Grid* getGrid();
	void drawAxises() const;

	void drawFunction(float(*func)(float x, const float k), const float k) const;

	unsigned int getWidth() const;
	unsigned int getHeight() const;

	float getShiftX(void) const;
	float getShiftY(void) const;
	void setShiftX(const float x);
	void setShiftY(const float y);

	float getZoom(void) const;
	void setZoom(const float x);

	int getScale(void) const;

};

#endif
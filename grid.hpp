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
	static Grid* getGrid(void);
	void drawAxises(void) const;

	void drawFunction(float(*func)(float x, const float k), const float k) const;

	unsigned int getWidth(void) const;
	unsigned int getHeight(void) const;

	constexpr float getShiftX(void) const;
	constexpr float getShiftY(void) const;
	inline void setShiftX(const float x);
	inline void setShiftY(const float y);

	constexpr float getZoom(void) const;
	inline void setZoom(const float x);

	constexpr int getScale(void) const;

	bool input(void);
};

#endif
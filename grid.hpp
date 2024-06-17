#ifndef GRID
#define GRID

#include <SDL.h>
#include <iostream>

class Grid {
private:
	static Grid* _grid;

	float _shiftx;
	float _shifty;
	float _zoom;
	int _scale;
	unsigned int _iters;

	unsigned int width;
	unsigned int height;

public:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Grid();
	static Grid* getGrid(void);

	void drawAxises(void) const;

	/* For linear functions use iters = 1, for smooth curves like a sine wave, use a high iters like 200.
	* \param func takes a function with two float paramaters that returns a float
	* \returns void
	*/
	void drawFunction(float(*func)(float x, const float k), const float k) const;

	unsigned int getWidth(void) const;
	unsigned int getHeight(void) const;

	unsigned int getIters(void) const;
	void setIters(unsigned int val);

	bool input(void);
};

#endif
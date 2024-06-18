#ifndef GRID
#define GRID

#include <SDL.h>
#include <iostream>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>

extern TTF_Font* font;

class Grid {
private:
	static Grid* _grid;

	float _shiftx;
	float _shifty;
	float _zoom;
	unsigned int _iters;

	unsigned int width;
	unsigned int height;

public:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Grid();
	static Grid* getGrid(void);

	/* Draws text on screen.
	* \param str text to display
	* \param xpos [-1,1]
	* \param ypos [-1,1]
	* \returns void
	*/
	void displayString(std::string str, const float xpos, const float ypos) const;

	float getShiftx(void) const;
	float getShifty(void) const;
	float getZoom(void) const;

	void drawAxisNumbers(void);

	void drawAxises(void) const;

	/* Draws a function on a graph, piecewise graph method. Use small iter values for linear functions (1). Use high iter values for non-linear (200).
	* \param func takes a function with two float paramaters that returns a float
	* \returns void
	*/
	void drawFunction(float(*func)(float x, const float k), const float k) const;

	unsigned int getWidth(void) const;
	unsigned int getHeight(void) const;

	unsigned int getIters(void) const;
	/* For linear functions use iters = 1, for smooth curves like a sine wave, use a high iters like 200.
	* \param val number of iterations in drawFunction
	* \returns void
	*/
	void setIters(unsigned int val);

	bool input(void);
};

#endif
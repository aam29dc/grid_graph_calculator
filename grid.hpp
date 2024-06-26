#ifndef GRID_H
#define GRID_H

#include "expression.hpp"
#include <SDL.h>
#include <iostream>
#include <string>
#include <format>

class Grid {
private:
	float _shiftx;			// for graphing functions on a x range
	float _shifty;			// for graphing functions on a y range
	float _zoom;			// level of zoom in a graph
	unsigned int _iters;	// number of iterations on a graph

	unsigned int _width;	// width of grid within a window
	unsigned int _height;	// height

	float _offsetx;			// offset within window
	float _offsety;			// offset within window

	void drawAxisNumbers();
	void drawAxises(SDL_Renderer* renderer) const;
	void drawBorder(SDL_Renderer* renderer) const;
public:
	Grid();

	void displayStats(const Uint32 startTime) const;
	void draw(SDL_Renderer* renderer) const;
	// takes a expression with an 'x' variable, no constants only numbers
	//void drawFunction(std::string expr)

	/* Draws a function on a graph, piecewise graph method. Use small iter values for linear functions (1). Use high iter values for non-linear (200).
	* \param func takes a function with two float paramaters that returns a float
	* \returns void
	*/

	void drawFunction(SDL_Renderer* renderer, const std::string expr) const;
	void drawFunction(SDL_Renderer* renderer, const float(*f)(const float), const float k = 1, const float c = 0) const;
	void drawFunction2(SDL_Renderer* renderer, const float(*f)(const float), const float k = 1, const float c = 0) const;
	void drawFunction3(SDL_Renderer* renderer, const float(*f)(const float), const float k = 1, const float c = 0) const;
	void drawFunction4(SDL_Renderer* renderer, const std::string PFexpr) const;

	float getShiftx() const;
	float getShifty() const;
	float getZoom() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	unsigned int getIters() const;
	/* For linear functions use iters = 1, for smooth curves like a sine wave, use a high iters like 200.
	* \param val number of iterations in drawFunction
	* \returns void
	*/
	void setIters(const unsigned int val);
	void setShiftx(const float val);
	void setShifty(const float val);
	void setZoom(const float val);
};

#endif
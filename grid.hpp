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

	void _drawAxisNumbers();
	void _drawAxises(SDL_Renderer* renderer) const;
	void _drawBorder(SDL_Renderer* renderer) const;
public:
	Grid();

	void displayStats(const Uint32& startTime) const;
	void draw(SDL_Renderer* renderer) const;

	/* Draws a function on a graph, piecewise graph method. Use small iter values for linear functions (1). Use high iter values for non-linear (100).
	* \param func takes a function with two float paramaters that returns a float
	* \returns void
	*/
	void drawFunction(SDL_Renderer* renderer, const std::string& expr) const;

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
	void setIters(const unsigned int& val);
	void setShiftx(const float& val);
	void setShifty(const float& val);
	void setZoom(const float& val);
	void setHeight(const unsigned& val);
	void setWidth(const unsigned& val);
};

#endif
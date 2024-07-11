#include "grid.hpp"

Grid::Grid() {
	_shiftx = 0.0f;
	_shifty = 0.0f;
	_zoom = 1.0f;
	_iters = 100;

	_width = 320;
	_height = 320;

	_offsetx = 0.0f;
	_offsety = 0.0f;
}

void Grid::draw(SDL_Renderer* renderer) const {
	_drawBorder(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	_drawAxises(renderer);
}

void Grid::_drawBorder(SDL_Renderer* renderer) const {
	SDL_FRect rec = { 0 };
	rec.x = _offsetx;
	rec.y = _offsety;
	rec.w = _offsetx + float(_width);
	rec.h = _offsety + float(_height);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRectF(renderer, &rec);
}

void Grid::displayStats(const Uint32& startTime) const {
	/*App::getApp()->drawString("X: " + removeTrailingDigits(std::to_string(_shiftx)), -0.9f, 0.9f);
	App::getApp()->drawString("Y: " + removeTrailingDigits(std::to_string(_shifty)), -0.9f, 0.8f);
	App::getApp()->drawString("Zoom: " + removeTrailingDigits(std::to_string(_zoom)), -0.9f, 0.7f);
	App::getApp()->drawString("FPS: " + std::to_string(int(1.0f / ((SDL_GetTicks() - startTime) / 1000.0f))), 0.7f, 0.9f);*/
}

void Grid::_drawAxisNumbers() {
	/*App::getApp()->drawString(removeTrailingDigits(std::to_string((-_zoom) + _shiftx)), -1.0f, 0.0f); 		//negative x-axis
	App::getApp()->drawString(removeTrailingDigits(std::to_string((_zoom)+_shiftx)), 0.85f, 0.0f); 			//positive x-axis
	App::getApp()->drawString(removeTrailingDigits(std::to_string((-_zoom) + _shifty)), 0.01f, -0.925f);	//negative y-axis
	App::getApp()->drawString(removeTrailingDigits(std::to_string((_zoom)+_shifty)), 0.01f, 1.0f);			//positive y-axis*/
}

void Grid::drawFunction(SDL_Renderer* renderer, const std::string& expr) const {
	std::string exprX = infixToPostfix(convertUnaryToBinary(expr));

	if (expr.find('x') != std::string::npos) {	
		SDL_FPoint pt = { -_zoom + _shiftx, evaluatePostfix(exprX, pt.x) };
		float next_y = evaluatePostfix(exprX, pt.x + ((2.0f * _zoom) / _iters));

		SDL_FPoint pt_s = { 0 }, next_pt_s = { 0 };

		// grid coordinates to screen coordinates:
		// shiftx/shifty back, then scale back to normal range [-1,1], then scale to width/height of screen, then shift to center of screen
		for (unsigned int i = 0; i < _iters; i++) {

			pt_s.x = ((pt.x - _shiftx) / _zoom * (_width / 2.0f)) + (_width / 2.0f) + _offsetx;
			pt_s.y = -((pt.y - _shifty) / _zoom * (_height / 2.0f)) + (_height / 2.0f) + _offsety;
			next_pt_s.x = ((pt.x + ((2.0f * _zoom) / _iters) - _shiftx) / _zoom * (_width / 2.0f)) + (_width / 2.0f) + _offsetx;
			next_pt_s.y = -((next_y - _shifty) / _zoom * (_height / 2.0f)) + (_height / 2.0f) + _offsety;

			if (isfinite(pt_s.y) && isfinite(next_pt_s.y) && (pt_s.y > 0 && pt_s.y < _height) && (next_pt_s.y > 0 && next_pt_s.y < _height)) {
				SDL_RenderDrawLineF(renderer, pt_s.x, pt_s.y, next_pt_s.x, next_pt_s.y);
			}

			pt.x += ((2.0f * _zoom) / _iters);
			pt.y = evaluatePostfix(exprX, pt.x);
			next_y = evaluatePostfix(exprX, pt.x + ((2.0f * _zoom) / _iters));
		}
	}
}

void Grid::_drawAxises(SDL_Renderer* renderer) const {
	//App::getApp()->drawString("x", 0.95f, -0.05f);
	//draw x axis
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	if (_shifty < 1.0f && _shifty > -1.0f) {
		SDL_RenderDrawLineF(renderer,
			_offsetx,
			(_height / 2.0f) + (_shifty * ((_height / 2.0f) / _zoom)) + _offsety,
			float(_width) + _offsetx,
			(_height / 2.0f) + (_shifty * ((_height / 2.0f) / _zoom)) + _offsety
		);
	}
	//App::getApp()->drawString("y", -0.05f, 0.95f);
	//draw y axis
	if (_shiftx < 1.0f && _shiftx > -1.0f) {
		SDL_RenderDrawLineF(renderer,
			(_width / 2.0f) - (_shiftx * ((_width / 2.0f) / _zoom)) + _offsetx,
			_offsety,
			(_width / 2.0f) - (_shiftx * ((_width / 2.0f) / _zoom)) + _offsetx,
			float(_height) + _offsety
		);
	}
}

const unsigned int& Grid::getWidth() const {
	return _width;
}

const unsigned int& Grid::getHeight() const {
	return _height;
}

const unsigned int& Grid::getIters() const {
	return _iters;
}

void Grid::setIters(const unsigned int& val) {
	if (val <= 1) _iters = 1;
	else _iters = val;
}

const float& Grid::getShiftx() const {
	return _shiftx;
}

const float& Grid::getShifty() const {
	return _shifty;
}

const float& Grid::getZoom() const {
	return _zoom;
}

void Grid::setShiftx(const float& val) {
	_shiftx = val;
}

void Grid::setShifty(const float& val) {
	_shifty = val;
}

void Grid::setZoom(const float& val) {
	_zoom = val;
}

void Grid::setHeight(const unsigned& val) {
	_height = val;
}

void Grid::setWidth(const unsigned& val) {
	_width = val;
}

/*
	//if both oob
		//if opposite parity, then it crosses the x-axis
			// if m > 0 => left_y = -1 & right_y = 1
			// if m < 0 => left_y = 1 & right_y = -1
		//if same parity, then it is not seen
	//if left oob
		//if m > 0 => left_y = -1
		//if m < 0 => left_y = 1
	//if right oob
		// if m > 0 => right_y = 1
		// if m < 0 => right_y -1
	//if neither is oob
		// draw
*/
/*
void Grid::drawFunction(SDL_Renderer* renderer, const float(*f)(const float), const float& k, const float& c) const {
	SDL_FPoint pt = { -_zoom + _shiftx, k * f(pt.x) + c };	//current point

	for (unsigned int i = 0; i < _iters; i++) {
		// grid coordinates to screen coordinates:
		// shiftx/shifty back, then scale back to normal range [-1,1], then scale to width/height of screen, then shift to center of screen
		SDL_RenderDrawLineF(renderer,
			((pt.x - _shiftx) / _zoom * (_width / 2.0f)) + (_width / 2.0f) + _offsetx,
			-((pt.y - _shifty) / _zoom * (_height / 2.0f)) + (_height / 2.0f) + _offsety,
			((pt.x + ((2.0f * _zoom) / _iters) - _shiftx) / _zoom * (_width / 2.0f)) + (_width / 2.0f) + _offsetx,
			-((k * f(pt.x + ((2.0f * _zoom) / _iters)) + c - _shifty) / _zoom * (_height / 2.0f)) + (_height / 2.0f) + _offsety
		);

		pt.x += ((2.0f * _zoom) / _iters);
		pt.y = k * f(pt.x) + c;
	}
}

void Grid::drawFunction3(SDL_Renderer* renderer, const float(*f)(const float), const float& k, const float& c) const {
	SDL_FPoint left = { -1, k * f(left.x) + c };
	SDL_FPoint pt = left;
	SDL_FPoint right = { left.x, 0 };

	float slope = 0.0f;

	for (unsigned int i = 0; i < _iters; i++) {
		std::cout << "i: " << i << "\ndx: " << ((2.0f) / _iters) << "\n";
		right.x += ((2.0f) / _iters);
		right.y = k * f(right.x) + c;

		std::cout << "l.x: " << left.x << "\tl.y: " << left.y << "\n";
		std::cout << "r.x: " << right.x << "\tr.y: " << right.y << "\n";

		//if both points are not oob and dont have the same parity, calculate new pts
		if ((left.y > 1 && right.y > 1) || (left.y < -1 && right.y < -1)) {
			std::cout << "OOB\n";
			left = right;
			continue;
		}

		slope = (left.y - right.y) / (left.x - right.x);	//left.x < right.x is always true

		std::cout << "slope: " << slope << "\n";

		if (!(abs(slope) > 0 && abs(slope) < 1)) {
			std::cout << "A\n";
			left.x = (-parity(slope) + (pt.x * slope) - pt.y) / slope;
			right.x = (parity(slope) + (pt.x * slope) - pt.y) / slope;
		}
		//equation is form y=0x+c
		else if (abs(slope) == 0.0f) {
			//std::cout << "B\t";
			left.y = right.y = slope;
		}

		std::cout << "l.x: " << left.x << "\tl.y: " << left.y << "\n";
		std::cout << "r.x: " << right.x << "\tr.y: " << right.y << "\n";

		SDL_RenderDrawLineF(renderer,
			(left.x) * (_width / 2.0f) + (_width / 2.0f),
			(-left.y) * (_height / 2.0f) + (_height / 2.0f),
			(right.x) * (_width / 2.0f) + (_width / 2.0f),
			(-right.y) * (_height / 2.0f) + (_height / 2.0f)
		);
		left = right;
		pt = left;
	}
}

void Grid::drawFunction2(SDL_Renderer* renderer, const float(*f)(const float), const float& k, const float& c) const {
	SDL_FPoint curr = { -_zoom + _shiftx, k * f(curr.x) + c };
	SDL_FPoint prev = curr;

	float slope = 0.0f;

	float x1 = -_zoom + _shiftx, x2 = _zoom + _shiftx;
	float y1 = -_zoom, y2 = _zoom;

	 //We could detect if our function is a linear line here, then set iters to 1, otherwise a high value for smooth curves.
	//For this first we need our evaluate expression string function

	for (unsigned int i = 0; i < _iters; i++) {
		prev = curr;
		curr.x += (2.0f * _zoom) / _iters;
		curr.y = k * f(curr.x) + c;	// call evaluate string here with corresponding x value,
		//since we have not made the parse string module, we use this cheat solution. Therefore we keep in mind of the input to drawFunction.

		slope = (prev.y - curr.y) / -(2.0f*_zoom);

		// if both prev and curr are OOB and have the same parity, then they don't intersect the graph, therefore draw nothing
		if ((prev.y >= _zoom || prev.y <= -_zoom) && (curr.y >= _zoom || curr.y <= -_zoom)
			&& ((prev.y > 0 && curr.y > 0) || (prev.y < 0 && curr.y < 0))) {
			continue;
		}

		// find corresponding x-values (x1 and x2) for which their y values (-1 and 1)
		if (slope != 0) {
			x1 = ((y1 - (prev.y - slope * prev.x)) / slope);
			x2 = ((y2 - (curr.y - slope * curr.x)) / slope);
		}
		// function is constant, y = 0+c (no variable)
		else {
			y1 = c;
			y2 = c;
		}

		// grid coordinates to screen coordinates:
		// shiftx/shifty back, then scale back to normal range [-1,1], then scale to /height of screen, then shift to center of screen
		SDL_RenderDrawLineF(renderer,
			(x1) / _zoom * (_width / 2.0f) + (_width / 2.0f),
			(y1) / _zoom * (_height / 2.0f) + (_height / 2.0f),
			(x2) / _zoom * (_width / 2.0f) + (_width / 2.0f),
			(y2) / _zoom * (_height / 2.0f) + (_height / 2.0f)
		);
	}
}
*/

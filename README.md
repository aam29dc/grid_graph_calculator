# grid_graph_calculator
SDL2 Grid, graph equations, graphics calculator

**Just like a graphing Calculator:**

--Zoom in/out (press minus/plus),
  
--scroll left, right, up, down (press up, down, left, right)

![1](https://github.com/aam29dc/grid_graph_calculator/assets/73267302/bd8b6e00-78dd-4bcf-96ad-53a27f83ebf9)

**fast solution**

--The magic of this program is the function: `drawFunction`, which draws a function like `coef_id` (y=kx) defined as function, taken as a parameter to `drawFunction`.
Each graph is ran 200 iterations (`_iters`) in its corresponding x-interval, so curves can appear to be smooth when zoomed in/out, and no need to check drawing out of bounds.
Basically there are 2 different coordinate systems, `grid coordinates` are normalized; we create the graph here. Then we use grid coords to create `screen coordinates`, which are scaled to uniformly on each axis, then scaled to users resolution, then shifted to origin.
````c++
float coef(float x, const float k) { return k; }
float coef_id(float x, const float k) { return k*x; }
float coef_squ(float x, const float k) { return k * x*x; }

void Grid::drawFunction(float(*func)(float x, const float k), const float k) const {
	SDL_FPoint curr = { float((-_scale) + _shiftx),0.0f};

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

		// grid coordinates to screen coordinates:
		// shiftx/shifty back, then scale back to normal range [-1,1], then scale to width/height of screen, then shift to center of screen

		if (zoomS == 0) {
			zoomS = 1.0f;
		}
		else if (zoomS < 0) {
			zoomS = 1.0f / (-zoomS);
		}

		SDL_RenderDrawLineF(renderer,
			((prev.x - _shiftx) / (_scale * zoomS) * (width / 2.0f)) + (width / 2.0f),
			-((prev.y - _shifty) / (_scale * zoomS) * (height / 2.0f)) + (height / 2.0f),

			((curr.x - _shiftx) / (_scale * zoomS) * (width / 2.0f)) + (width / 2.0f),
			-((curr.y - _shifty) / (_scale * zoomS) * (height / 2.0f)) + (height / 2.0f));
	}
}
````
**To create the picture above:**

--We then run a hundred iterations of the equations `1/k`, `-1/k`, and `(1/k)x` and `(-1/k)x` with k = 1, ..., 100.
````c++
        for (int i = 1; i < 100; i++) {
            Grid::getGrid()->drawFunction(coef_id, 1.0f/i);
            Grid::getGrid()->drawFunction(coef_id, -1.0f/i);
            Grid::getGrid()->drawFunction(coef, 1.0f / i);
            Grid::getGrid()->drawFunction(coef, 1.0f / -i);
        }
````

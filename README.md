# grid_graph_calculator '(caution: ears may ring)'
SDL2 Grid, graph equations, graphics calculator

(Note: this would be the graphics part of a full graphics calculator program, another part would be parsing a string or expression)

**Just like a graphing Calculator:**

--Zoom in/out (press `minus`/`plus`),
  
--scroll left, right, up, down (press `up`, `down`, `left`, `right`)

--press `esc` to scape, and press `o` or `0` to recenter graph, reset settings

![1](https://github.com/aam29dc/grid_graph_calculator/assets/73267302/bd8b6e00-78dd-4bcf-96ad-53a27f83ebf9)

**To create the picture above:**

--We run a hundred iterations of the equations `1/k`, `-1/k`, and `(1/k)x` and `(-1/k)x` with k = 1, ..., 100.
````c++
	Grid::getGrid()->setIters(1);   // since we are drawing linear lines, we set the iters low, since a line only needs two f(x1), and f(x2).
        for (int i = 1; i < 100; i++) {
		Grid::getGrid()->drawFunction(coef_id, 1.0f/i);
		Grid::getGrid()->drawFunction(coef_id, -1.0f/i);
		Grid::getGrid()->drawFunction(coef, 1.0f / i);
		Grid::getGrid()->drawFunction(coef, 1.0f / -i);
        }
````
**A fast solution: `drawFunction`**

--draws a function like `coef_id` (y=kx) defined as function, taken as a parameter to `drawFunction`.
Each graph is ran with 200 x-values (`_iters`) in its corresponding x-interval, so curves can appear to be smooth when zoomed in/out, and no need to check drawing out of bounds. For linear line graphs, `_iters` is set to 1, since we only need 2 points to draw a line.
Basically there are 2 different coordinate systems, `grid coordinates` are normalized; we create the graph here. Then we transform grid coords to `screen coordinates`, which are scaled uniformly on each axis, then scaled to users resolution, then shifted to origin.
````c++
constexpr inline float coef(float x, const float k) { return k; }
constexpr inline float coef_id(float x, const float k) { return k*x; }
constexpr inline float coef_squ(float x, const float k) { return k * x*x; }
inline float coef_sine(float x, const float k) { return k * sinf(x); }

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
````

![3](https://github.com/aam29dc/grid_graph_calculator/assets/73267302/3f7ed499-b9a3-42b9-9e32-8a8692584e51)

** `x`, `x^2`, `x^3` and `sin(x)` drawn on the same graph on the x interval [-1,1] (_scale = 1 && _zoom = 1) **

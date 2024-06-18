# grid_graph_calculator
SDL2 Grid, graph equations, graphics calculator

(Note: this would be the graphics part of a full graphics calculator program, another part would be parsing a string or expression)

**Just like a graphing Calculator:**

--Zoom in/out (press `minus`/`plus`),
  
--scroll left, right, up, down (press `up`, `down`, `left`, `right`)

--press `esc` to scape, and press `o` or `0` to recenter graph, reset settings

![x3](https://github.com/aam29dc/grid_graph_calculator/assets/73267302/653f3e9d-114a-4b78-ad7a-8a6d7da0c4fe)

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
**A fast solution: `drawFunction` (piecewise function method)** 

--draws a function like `coef_id` (y=kx) defined as function, taken as a parameter to `drawFunction`.
Each graph is ran with (`_iters`) number of x-values, so curves can appear to be smooth when zoomed in/out, and no need to check drawing out of bounds. For linear line graphs, set `_iters` to 1 (only need 2 points to draw a line.) before drawing.
Basically there are 2 different coordinate systems, `grid coordinates` are normalized; we create the graph here. Then we transform grid coords to `screen coordinates`, which are scaled uniformly on each axis, then scaled to users resolution, then shifted to origin.

![x1](https://github.com/aam29dc/grid_graph_calculator/assets/73267302/15b1ec97-9d2b-4909-9873-357e3bee2384)

** `x`, `x^2`, `x^3` and `sin(x)` drawn on the same graph on the x interval [-1,1] (_scale = 10 && _zoom = -10) **

![x2](https://github.com/aam29dc/grid_graph_calculator/assets/73267302/d8afa7c9-95f2-4d5e-a5e1-54133f45405e)

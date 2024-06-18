# grid_graph_calculator
SDL2 Grid, graph equations, graphics calculator

(Note: this would be the graphics part of a full graphics calculator program, another part would be parsing a string or expression)

*[0.5] Fixed zoom effect, simplified expressions, zoom starts at 1, removed scale variable, etc; polished code.
Now when you zoom past zero it flips both the axises. (This is like zooming in to infinity, then going on the 'other side' to a mirror universe)*

**Just like a graphing Calculator:**

--Zoom in/out (press `minus`/`plus`),
  
--scroll left, right, up, down (press `up`, `down`, `left`, `right`)

--press `esc` to scape, and press `o` or `0` to recenter graph, reset settings

![4](https://github.com/aam29dc/grid_graph_calculator/assets/73267302/3db4cff1-9809-4218-8b1c-a20c9657fa0f)

**To create the picture above:**

--We run a hundred iterations of the equations `1/k`, `-1/k`, and `(1/k)x` and `(-1/k)x` with k = 1, ..., 100.
````c++
	Grid::getGrid()->setIters(1);   // since we are drawing linear lines,
					// we set the iters low, since a line only needs two f(x1), and f(x2).
        for (int i = 1; i < 100; i++) {
		Grid::getGrid()->drawFunction(coef_id, 1.0f/i);
		Grid::getGrid()->drawFunction(coef_id, -1.0f/i);
		Grid::getGrid()->drawFunction(coef, 1.0f / i);
		Grid::getGrid()->drawFunction(coef, 1.0f / -i);
        }
````
**A fast solution: `drawFunction` (piecewise function method)** 

--draws a function like (y=kx) `coef_id` defined as a function, taken as a parameter to `drawFunction`.
Each graph is ran with (`_iters`) number of x-values, so curves can appear to be smooth when zoomed in/out. For linear line graphs, set `_iters` to 1 (only need 2 points to draw a line.) before drawing.
`grid coordinates` are normalized [-1,1]; we create the graph here. Then we transform grid coords to `screen coordinates` using scaling and shifts.

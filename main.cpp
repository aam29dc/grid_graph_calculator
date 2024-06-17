#include <iostream>
#include <SDL_image.h>
#include "grid.hpp"
#undef main

#include <math.h>

constexpr inline float coef(float x, const float k) { return k; }
constexpr inline float coef_id(float x, const float k) { return k*x; }
constexpr inline float coef_squ(float x, const float k) { return k * x*x; }
constexpr inline float coef_cube(float x, const float k) { return k * x * x * x; }
inline float coef_sine(float x, const float k) { return k * sinf(x); }

auto main() -> int {
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		if (SDL_CreateWindowAndRenderer(Grid::getGrid()->getWidth(), Grid::getGrid()->getHeight(), SDL_WINDOW_FULLSCREEN, &Grid::getGrid()->window, &Grid::getGrid()->renderer)) {

		}
	}

    bool quit = false;

	while (quit == false) {
        SDL_SetRenderDrawColor(Grid::getGrid()->renderer, 0, 0, 0, 255);
        SDL_RenderClear(Grid::getGrid()->renderer);

        quit = Grid::getGrid()->input();

        //projection grid
        SDL_SetRenderDrawColor(Grid::getGrid()->renderer, 255, 0, 0, 255);
		
        Grid::getGrid()->setIters(1);   // since we are drawing linear lines, we set the iters low, since a line only needs two f(x1), and f(x2).
        for (int i = 1; i <= 100; i++) {
            SDL_SetRenderDrawColor(Grid::getGrid()->renderer, 0, 255, 0, 255);
            Grid::getGrid()->drawFunction(coef_id, 1.0f / i);
            SDL_SetRenderDrawColor(Grid::getGrid()->renderer, 255, 0, 0, 255);
            Grid::getGrid()->drawFunction(coef_id, -1.0f / i);

            SDL_SetRenderDrawColor(Grid::getGrid()->renderer, 0, 0, 255, 255);
            Grid::getGrid()->drawFunction(coef, 1.0f / i);
            SDL_SetRenderDrawColor(Grid::getGrid()->renderer, 255, 255, 0, 255);
            Grid::getGrid()->drawFunction(coef, 1.0f / -i);
        }

        SDL_SetRenderDrawColor(Grid::getGrid()->renderer, 255, 255, 255, 255);
        Grid::getGrid()->drawAxises();

        SDL_RenderPresent(Grid::getGrid()->renderer);
	}

    SDL_DestroyRenderer(Grid::getGrid()->renderer);
    SDL_DestroyWindow(Grid::getGrid()->window);
    SDL_Quit();

	return 0;
}

#include <iostream>
#include <SDL_image.h>
#include "grid.hpp"
#undef main

float coef(float x, const float k) { return k; }
float coef_id(float x, const float k) { return k*x; }
float coef_squ(float x, const float k) { return k * x*x; }

auto main() -> int {
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		if (SDL_CreateWindowAndRenderer(Grid::getGrid()->getWidth(), Grid::getGrid()->getHeight(), SDL_WINDOW_FULLSCREEN, &Grid::getGrid()->window, &Grid::getGrid()->renderer)) {

		}
	}

    bool quit = false;
    SDL_Event e;

	while (quit == false) {
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            //User presses a key
            else if (e.type == SDL_KEYDOWN)
            {
                float scale = Grid::getGrid()->getScale()/100.0f;
                //Select surfaces based on key press
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    Grid::getGrid()->setShiftY(Grid::getGrid()->getShiftY() + scale);
                    break;

                case SDLK_DOWN:
                    Grid::getGrid()->setShiftY(Grid::getGrid()->getShiftY() - scale);
                    break;

                case SDLK_LEFT:
                    Grid::getGrid()->setShiftX(Grid::getGrid()->getShiftX() + scale);
                    break;

                case SDLK_RIGHT:
                    Grid::getGrid()->setShiftX(Grid::getGrid()->getShiftX() - scale);
                    break;

                case SDLK_MINUS: case SDLK_UNDERSCORE:
                    Grid::getGrid()->setZoom(Grid::getGrid()->getZoom() - scale*10);
                    break;

                case SDLK_EQUALS: case SDLK_PLUS:
                    Grid::getGrid()->setZoom(Grid::getGrid()->getZoom() + scale*10);
                    break;
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                default:
                    break;
                }
            }
        }

		SDL_SetRenderDrawColor(Grid::getGrid()->renderer, 0, 0, 0, 255);
		SDL_RenderClear(Grid::getGrid()->renderer);

        //projection grid
        for (int i = 1; i < 100; i++) {
            SDL_SetRenderDrawColor(Grid::getGrid()->renderer, 0, 255, 0, 255);
            Grid::getGrid()->drawFunction(coef_id, 1.0f/i);
            SDL_SetRenderDrawColor(Grid::getGrid()->renderer, 255, 0, 0, 255);
            Grid::getGrid()->drawFunction(coef_id, -1.0f/i);

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

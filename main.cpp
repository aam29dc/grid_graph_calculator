#include "grid.hpp"
#undef main

constexpr inline float coef(float x, const float k) { return k; }
constexpr inline float coef_id(float x, const float k) { return k*x; }
constexpr inline float coef_squ(float x, const float k) { return k * x*x; }
constexpr inline float coef_cube(float x, const float k) { return k * x * x * x; }
inline float coef_sine(float x, const float k) { return k * sinf(x); }

auto main() -> int {
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
        Grid::getGrid()->window = SDL_CreateWindow("Grid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Grid::getGrid()->getWidth(), Grid::getGrid()->getHeight(), SDL_WINDOW_SHOWN);
        Grid::getGrid()->renderer = SDL_CreateRenderer(Grid::getGrid()->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            std::cout << "Warning: Linear texture filtering not enabled!" << "\n";
        }

        if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            std::cout << "SDL_image could not initialize! SDL_image Error :" << IMG_GetError() << "\n";
        }

        //Initialize SDL_ttf
        if (TTF_Init() == -1) {
            std::cout << "SDL_ttf could not initialize! SDL_ttf Error:" <<  TTF_GetError() << "\n";
        }

        font = TTF_OpenFont("assets/arial.ttf", 24);
        if (font == NULL) {
            std::cout << "Failed to load lazy font! SDL_ttf Error: \n" <<  TTF_GetError() << "\n";
        }
	}

    bool quit = false;

    Uint32 startTime = 0;

	while (quit == false) {
        startTime = SDL_GetTicks();

        SDL_SetRenderDrawColor(Grid::getGrid()->renderer, 0, 0, 0, 255);
        SDL_RenderClear(Grid::getGrid()->renderer);

        quit = Grid::getGrid()->input();

        Grid::getGrid()->setIters(1);   // since we are drawing linear lines, we set the iters low, since a line only needs two f(x1), and f(x2).
        for (int i = 1; i <= 100; i++) {    //projection grid
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
        Grid::getGrid()->drawAxisNumbers();

        Grid::getGrid()->displayString("X: " + std::to_string(Grid::getGrid()->getShiftx()), -0.9f, 0.9f);
        Grid::getGrid()->displayString("Y: " + std::to_string(Grid::getGrid()->getShifty()), -0.9f, 0.8f);
        Grid::getGrid()->displayString("Zoom: " + std::to_string(Grid::getGrid()->getZoom()), -0.9f, 0.7f);
        Grid::getGrid()->displayString("FPS: " + std::to_string(int(1.0f / ((SDL_GetTicks() - startTime) / 1000.0f))), 0.7f, 0.9f);

        SDL_RenderPresent(Grid::getGrid()->renderer);
	}

    SDL_DestroyRenderer(Grid::getGrid()->renderer);
    SDL_DestroyWindow(Grid::getGrid()->window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

	return 0;
}
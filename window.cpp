#include "window.hpp"

Window* Window::instance = nullptr;

Window::Window(const unsigned width, const unsigned height) {
	_height = SCREEN_HEIGHT;
	_width = SCREEN_WIDTH;
	_mouseFocus = false;
	_keyboardFocus = false;
	_fullScreen = false;
	_minimized = false;
	_quit = false;
	_window = nullptr;
	_renderer = nullptr;

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		_window = SDL_CreateWindow("SDL2 Grapher", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			//std::cout << "Warning: Linear texture filtering not enabled!" << "\n";
		}

		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
			//std::cout << "SDL_image could not initialize! SDL_image Error :" << IMG_GetError() << "\n";
		}

		if (!initFont()) {
			//std::cout << "Init font error SDL_ttf: " << TTF_GetError() << "\n";
		}
		//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
	}
}

Window* Window::getWindow() {
	if (instance == nullptr) instance = new Window();
	return instance;
}

Window::~Window() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Window::handleWindowEvent(SDL_Event& e) {
	if (e.type == SDL_WINDOWEVENT) {
		bool updateCaption = false;

		switch (e.window.event) {
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			_width = e.window.data1;
			_height = e.window.data2;
			SDL_SetWindowSize(_window, _width, _height);
			SDL_RenderPresent(_renderer);
			break;
		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(_renderer);
			break;
		case SDL_WINDOWEVENT_ENTER:
			_mouseFocus = true;
			updateCaption = true;
			break;
		case SDL_WINDOWEVENT_LEAVE:
			_mouseFocus = false;
			updateCaption = true;
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			_keyboardFocus = true;
			updateCaption = true;
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			_keyboardFocus = false;
			updateCaption = true;
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			_minimized = true;
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			_minimized = false;
			break;
		case SDL_WINDOWEVENT_RESTORED:
			_minimized = false;
			break;
		case SDL_WINDOWEVENT_CLOSE:
			_quit = true;
			break;
		}
	}
	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
		if (_fullScreen) {
			SDL_SetWindowFullscreen(_window, 0);
			_fullScreen = false;
		}
		else {
			SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
			_fullScreen = true;
			_minimized = false;
		}
	}
}

unsigned int Window::getWidth() const {
	return _width;
}

unsigned int Window::getHeight() const {
	return _height;
}

bool Window::getMouseFocus() const {
	return _mouseFocus;
}

bool Window::getKeyboardFocus() const {
	return _keyboardFocus;
}

bool Window::getFullscreen() const {
	return _fullScreen;
}

bool Window::getMinimized() const {
	return _minimized;
}

bool Window::getQuit() const {
	return _quit;
}
#ifndef WINDOW_H
#define WINDOW

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "font.hpp"

inline extern const unsigned int SCREEN_WIDTH = 640;
inline extern const unsigned int SCREEN_HEIGHT = 320;

class Window {
private:
	static Window* instance;
public:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	unsigned int _height;
	unsigned int _width;

	bool _mouseFocus;
	bool _keyboardFocus;
	bool _fullScreen;
	bool _minimized;
	bool _quit;

	Window(const unsigned width = SCREEN_WIDTH, const unsigned height = SCREEN_HEIGHT);
	~Window();

	static Window* getWindow();

	void handleWindowEvent(SDL_Event& e);
};

#endif
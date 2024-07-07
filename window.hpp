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
	unsigned int _height;
	unsigned int _width;

	bool _mouseFocus;
	bool _keyboardFocus;
	bool _fullScreen;
	bool _minimized;
	bool _quit;
public:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	unsigned int getWidth() const;
	unsigned int getHeight() const;
	bool getMouseFocus() const;
	bool getKeyboardFocus() const;
	bool getFullscreen() const;
	bool getMinimized() const;
	bool getQuit() const;

	Window(const unsigned width = SCREEN_WIDTH, const unsigned height = SCREEN_HEIGHT);
	~Window();

	static Window* getWindow();

	void handleWindowEvent(SDL_Event& e);
};

#endif
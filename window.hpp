#ifndef WINDOW_H
#define WINDOW

#ifndef DEBUG
	#include <SDL.h>
	#include <SDL_image.h>
	#include <SDL_ttf.h>
#endif // DEBUG

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

	const unsigned int& getWidth() const;
	const unsigned int& getHeight() const;
	const bool& getMouseFocus() const;
	const bool& getKeyboardFocus() const;
	const bool& getFullscreen() const;
	const bool& getMinimized() const;
	const bool& getQuit() const;

	Window(const unsigned width = SCREEN_WIDTH, const unsigned height = SCREEN_HEIGHT);
	~Window();

	static Window* getWindow();

	void handleWindowEvent(SDL_Event& e);
};

#endif
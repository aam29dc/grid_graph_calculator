#ifndef APP_H
#define APP_H

#include "grid.hpp"
#include "expression.hpp"
#include "input.hpp"
#include "button.hpp"
#include "config_parser.hpp"
#include "math_notation.hpp"
#include "font.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

inline extern const unsigned int SCREEN_WIDTH = 640;
inline extern const unsigned int SCREEN_HEIGHT = 320;
inline extern const unsigned int NUM_BUTTONS = 24;
inline extern const unsigned int KEYPAD_OFFSET_X = 320+100;
inline extern const unsigned int KEYPAD_OFFSET_Y = 120;
inline extern const unsigned int KEYPAD_COLS = 4;
inline extern const unsigned int TEXTFIELD_OFFSET_X = (SCREEN_WIDTH/2) + 2;
inline extern const unsigned int TEXTFIELD_OFFSET_Y = 32;
inline extern const unsigned int TEXTFIELD_WIDTH = 320-3;

class App {
private:
	static App* _app;

	class Grid* _grid;

	unsigned int _height;
	unsigned int _width;

	static class Button keypad[NUM_BUTTONS];

	Uint32 _startTime;

	std::string _textInput;
	SDL_Color _textInputColor;

	void drawTextField() const;

	SDL_Color _bgColor;

	std::map<char, int> _keymap;
	void _setupKeypad();
public:
	SDL_Window* window;
	SDL_Renderer* renderer;

	App();
	~App();

	static App* getApp();

	Grid* getGrid() const;

	int init(unsigned int width = SCREEN_WIDTH, unsigned int height = SCREEN_HEIGHT);
	bool handleEvents();
	void update();
	void render();

	void writeScreenshot() const;

	unsigned int getHeight() const;
	unsigned int getWidth() const;
	std::string getTextInput() const;

	void setHeight(const unsigned int val);
	void setWidth(const unsigned int val);
	void setTextInput(std::string text);
};

#endif
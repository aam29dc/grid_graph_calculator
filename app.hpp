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

inline extern const unsigned int NUM_BUTTONS = 24;
inline extern const unsigned int KEYPAD_COLS = 4;

class App {
private:
	static App* _app;

	class Grid* _grid;

	static class Button _keypad[NUM_BUTTONS];

	Uint32 _startTime;

	std::string _inputHistory;
	std::string _textInput;
	SDL_Color _textInputColor;

	unsigned int TEXTFIELD_OFFSET_X;
	unsigned int TEXTFIELD_OFFSET_Y;
	unsigned int TEXTFIELD_WIDTH;
	int KEYPAD_OFFSET_X;
	int KEYPAD_OFFSET_Y;

	void _drawTextField(SDL_Renderer* renderer) const;

	SDL_Color _bgColor;

	std::map<int, char> _keymap;
	int _findKey(const char& ch) const;
	void _setupKeypad();
public:
	App();
	~App();

	static App* getApp();

	Grid* getGrid() const;

	bool handleEvents();
	void update();
	void render(SDL_Renderer* renderer);

	void writeScreenshot(SDL_Renderer* renderer) const;

	std::string getTextInput() const;
	std::string getInputHistory() const;

	void setTextInput(const std::string& text);
	void setInputHistory(const std::string& text);
};

#endif
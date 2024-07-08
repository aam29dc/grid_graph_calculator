#ifndef APP_H
#define APP_H

#include "grid.hpp"
#include "expression.hpp"
#include "input.hpp"
#include "button.hpp"
#include "config_parser.hpp"
#include "math_notation.hpp"
#include "font.hpp"
#include <vector>

#include <SDL.h>

inline extern const unsigned int NUM_BUTTONS = 24;
inline extern const unsigned int KEYPAD_COLS = 4;

class App {
private:
	static App* _app;

	class Grid* _grid;

	static class Button _keypad[NUM_BUTTONS];

	Uint32 _startTime;

	std::vector<std::string> _inputHistory;
	std::string _textInput;
	SDL_Color _textInputColor;

	unsigned int _tf_offset_x;
	unsigned int _tf_offset_y;
	unsigned int _tf_width;
	float _keypad_offset_x;
	float _keypad_offset_y;

	SDL_Color _bgColor;
	unsigned int _funcColor_seq;
	SDL_Color _funcColor;

	std::map<int, char> _keymap;
	int _findKey(const char& ch) const;
	void _setupKeypad();
	void _drawTextField(SDL_Renderer* renderer) const;
	void _nextFuncColor(const unsigned int& seq);
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
	std::vector<std::string> getInputHistory() const;

	void setTextInput(const std::string& text);
	void setInputHistory(const std::string& text, const unsigned int& at);
};

#endif
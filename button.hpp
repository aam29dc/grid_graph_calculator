#ifndef BUTTON_H
#define BUTTON_H

#include "input.hpp"
#include "font.hpp"
#include <string>
#ifndef DEBUG
	#include <SDL.h>
#endif // DEBUG

class Button {
private:
public:
	float _width;
	float _height;

	float _posx;
	float _posy;

	bool _hover;
	bool _click;

	SDL_Color _outlineColor;
	SDL_Color _color;
	SDL_Color _clickColor;
	SDL_Color _hoverColor;
	SDL_Color _textColor;

	std::string _text;

	void(*_callback)(const char& ch);

	Button(const std::string& text = " ", const float& w = 32.0f, const float& h = 32.0f, const float& x = 0, const float& y = 0);
	~Button();

	void draw(SDL_Renderer* renderer, const float& xoffset = 0, const float& yoffset = 0) const;
};

#endif
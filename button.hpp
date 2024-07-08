#ifndef BUTTON_H
#define BUTTON_H

#include "input.hpp"
#include "font.hpp"
#include <string>
#include <SDL.h>

class Button {
private:
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
public:
	Button(const std::string& text = " ", const float& w = 32.0f, const float& h = 32.0f, const float& x = 0, const float& y = 0);
	~Button();

	void draw(SDL_Renderer* renderer, const float& xoffset = 0, const float& yoffset = 0) const;
	void callback() const;

	void setHover(const bool& val);
	void setClick(const bool& val);
	void setCallback(void(*callback)(const char& ch));
	void setText(const std::string& text);
	void setPosX(const float& x);
	void setPosY(const float& y);
	void setHeight(const float& height);
	void setWidth(const float& width);
	float getWidth() const;
	float getHeight() const;
	float getPosX() const;
	float getPosY() const;
	bool getClick() const;
	std::string getText() const;
	SDL_Color getOutlineColor() const;
	SDL_Color getColor() const;
	SDL_Color getClickColor() const;
	SDL_Color getHoverColor() const;
};

#endif
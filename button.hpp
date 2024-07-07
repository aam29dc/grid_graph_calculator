#ifndef BUTTON_H
#define BUTTON_H

#include "input.hpp"
#include "font.hpp"
#include <string>
#include <SDL.h>

class Button {
private:
	int _width;
	int _height;

	int _posx;
	int _posy;

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
	Button(const std::string& text = " ", const int& w = 32, const int& h = 32, const int& x = 0, const int& y = 0);
	~Button();

	void draw(SDL_Renderer* renderer, const int& xoffset = 0, const int& yoffset = 0) const;
	void callback() const;

	void setHover(const bool& val);
	void setClick(const bool& val);
	void setCallback(void(*callback)(const char& ch));
	void setText(const std::string& text);
	void setPosX(const int& x);
	void setPosY(const int& y);
	void setHeight(const int& height);
	void setWidth(const int& width);
	int getWidth() const;
	int getHeight() const;
	int getPosX() const;
	int getPosY() const;
	bool getClick() const;
	std::string getText() const;
	SDL_Color getOutlineColor() const;
	SDL_Color getColor() const;
	SDL_Color getClickColor() const;
	SDL_Color getHoverColor() const;
};

#endif
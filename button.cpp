#include "button.hpp"

Button::Button(const std::string& text, const int& w, const int& h, const int& x, const int& y) {
	_width = w;
	_height = h;
	_posx = x;
	_posy = y;
	_outlineColor = { 0,0,0,255 };
	_color = { 220,220,220,255 };
	_hoverColor = { 155,155,155,255 };
	_clickColor = { 55,55,55,255 };
	_textColor = { 0,0,0,255 };
	_text = text;
	_callback = nullptr;
}

Button::~Button() {
	_callback = nullptr;
}

void Button::setCallback(void(*callback)(const char& ch)) {
	_callback = callback;
}

std::string Button::getText() const {
	return _text;
}

void Button::draw(SDL_Renderer* renderer, const int& xoffset, const int& yoffset) const {
	SDL_FRect rect = { 0 };

	rect.x = (float)(_posx + xoffset);
	rect.y = (float)(_posy + yoffset);
	rect.w = (float)(32);
	rect.h = (float)(32);

	SDL_Color color = {0};

	if (_click && _hover) color = getClickColor();
	else if (_hover && !_click) color = getHoverColor();
	else color = getColor();	//mouse position is outside of button

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRectF(renderer, &rect);

	if (_text != " " && !_text.empty()) {
		drawString(renderer, _text, _posx + xoffset + int(TEXTSIZE / 2.0f), _posy + yoffset + int(TEXTSIZE / 4.0f), _textColor);
	}

	color = getOutlineColor();

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRectF(renderer, &rect);
}

void Button::callback() const {
	_callback(this->getText().front());
}

bool Button::getClick() const {
	return _click;
}

void Button::setText(const std::string& text) {
	_text = text;
}

void Button::setPosX(const int& x) {
	_posx = x;
}

void Button::setPosY(const int& y) {
	_posy = y;
}

SDL_Color Button::getOutlineColor() const {
	return _outlineColor;
}

SDL_Color Button::getColor() const {
	return _color;
}

SDL_Color Button::getClickColor() const {
	return _clickColor;
}

SDL_Color Button::getHoverColor() const {
	return _hoverColor;
}

int Button::getWidth() const {
	return _width;
}

int Button::getHeight() const {
	return _height;
}

int Button::getPosX() const {
	return _posx;
}

int Button::getPosY() const {
	return _posy;
}

void Button::setHover(const bool& val) {
	_hover = val;
}

void Button::setClick(const bool& val) {
	_click = val;
}

void Button::setHeight(const int& height) {
	_height = height;
}

void Button::setWidth(const int& width) {
	_width = width;
}
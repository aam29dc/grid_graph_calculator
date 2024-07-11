#include "button.hpp"

Button::Button(const std::string& text, const float& w, const float& h, const float& x, const float& y) {
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

void Button::draw(SDL_Renderer* renderer, const float& xoffset, const float& yoffset) const {
	SDL_FRect rect = { 0 };

	rect.x = _posx + xoffset;
	rect.y = _posy + yoffset;
	rect.w = _width;
	rect.h = _height;

	SDL_Color color = {0};

	if (_click && _hover) color = _clickColor;
	else if (_hover && !_click) color = _hoverColor;
	else color = _color;	//mouse position is outside of button

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRectF(renderer, &rect);

	if (_text != " " && !_text.empty()) {
		drawString(renderer, _text, _posx + xoffset + int(TEXTSIZE / 2.0f), _posy + yoffset + int(TEXTSIZE / 4.0f), _textColor);
	}

	color = _color;

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRectF(renderer, &rect);
}
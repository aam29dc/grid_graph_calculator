#include "font.hpp"

TTF_Font* font;

bool initFont(const std::string src) {
    if (TTF_Init() == -1) return false;

    font = TTF_OpenFont("assets/RobotoMono-VariableFont_wght.ttf", int(TEXTSIZE));
    if (font == NULL) {
        return false;
    }
    return true;
}

void drawString(SDL_Renderer* renderer, const std::string str, const int xpos, const int ypos, SDL_Color color, const bool limit) {
	if (str.empty()) return;
	SDL_Surface* surfaceMsg = TTF_RenderText_Solid(font, str.c_str(), color);
	if (surfaceMsg == NULL) {
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << "\n";
		return;
	}

	SDL_Texture* msg = SDL_CreateTextureFromSurface(renderer, surfaceMsg);
	if (msg == NULL) {
		std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	SDL_FRect dst_rect = { 0 };
	SDL_Rect src_rect = { 0 };

	dst_rect.x = (float)xpos;
	dst_rect.y = (float)ypos-4;			// the font RobotoMono-VariableFont_wght.ttf is shifted
	dst_rect.w = (float)surfaceMsg->w;
	dst_rect.h = (float)surfaceMsg->h;

	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.w = surfaceMsg->w;
	src_rect.h = surfaceMsg->h;

	if (limit && (str.length() > MAXTEXT)) {
		src_rect.w = FONTWIDTH * MAXTEXT;									// max length
		dst_rect.w = float(src_rect.w);
		src_rect.x = int(str.length() - MAXTEXT) * FONTWIDTH;				// shift
	}

	SDL_RenderCopyF(renderer, msg, &src_rect, &dst_rect);

	SDL_FreeSurface(surfaceMsg);
	SDL_DestroyTexture(msg);
}
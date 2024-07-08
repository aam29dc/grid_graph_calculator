#ifndef FONT_H
#define FONT_H

#include <SDL_ttf.h>
#include <string>
#include <iostream>

inline extern const int TEXTSIZE = 22;
inline extern const int FONTWIDTH = 13;
extern TTF_Font* font;

bool initFont(const std::string& src = "assets/RobotoMono-VariableFont_wght.ttf");

/* Draws text on screen.
* \param str text to display
* \param xpos [-1,1]
* \param ypos [-1,1]
* \returns void
*/
void drawString(SDL_Renderer* renderer, const std::string& str, const float& xpos, const float& ypos, const SDL_Color& color, const unsigned& maxtext = 0, const bool& limit = false);
#endif
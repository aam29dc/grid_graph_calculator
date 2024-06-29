#ifndef FONT_H
#define FONT_H

#include <SDL_ttf.h>
#include <string>
#include <iostream>

inline extern const int TEXTSIZE = 22;
inline extern const int FONTWIDTH = 13;
inline extern const int MAXTEXT = 24;
extern TTF_Font* font;

bool initFont(const std::string src = "assets/RobotoMono-VariableFont_wght.ttf");

/* Draws text on screen.
* \param str text to display
* \param xpos [-1,1]
* \param ypos [-1,1]
* \returns void
*/
void drawString(SDL_Renderer* renderer, const std::string str, const int xpos, const int ypos, SDL_Color color, const bool limit = false);

#endif
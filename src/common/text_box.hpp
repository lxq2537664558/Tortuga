/* Copyright: (c) Kayne Ruse 2013-2015
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source
 * distribution.
*/
#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include <string>
#include <list>

constexpr SDL_Color COLOR_WHITE = {255, 255, 255, 255};

SDL_Texture* renderTextTexture(SDL_Renderer*, TTF_Font*, std::string, SDL_Color color);

//-------------------------

class TextLine {
public:
	TextLine();
	TextLine(SDL_Renderer* r, TTF_Font* f, std::string s, SDL_Color c)
		{ SetText(r, f, s, c); }
	~TextLine();

	void DrawTo(SDL_Renderer*, int posX, int posY);

	void SetText(SDL_Renderer*, TTF_Font*, std::string, SDL_Color color);
	void ClearText();

protected:
	SDL_Texture* texture = nullptr;
};

//-------------------------

class TextBox {
public:
	TextBox();
	~TextBox();

	void DrawTo(SDL_Renderer*, int posX, int posY, int pointSize);

	void PushLine(SDL_Renderer*, TTF_Font*, std::string, SDL_Color color);
	void PopLine(int num = 1);
	void ClearLines();

private:
	std::list<TextLine> lineList;
};
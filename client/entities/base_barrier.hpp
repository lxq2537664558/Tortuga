/* Copyright: (c) Kayne Ruse 2013-2016
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

#include "entity.hpp"

#include "composite_image.hpp"

class BaseBarrier: public Entity {
public:
	BaseBarrier() = default;
	BaseBarrier(Image& baseImage, std::map<std::string, Image>& templateImages);
	virtual ~BaseBarrier();

	void CorrectSprite();
	void Update();
	void DrawTo(SDL_Renderer* const, int camX, int camY);

	int SetStatus(int, int);
	int FindStatus(int);

	int* SetStatusArray(int*);
	int* GetStatusArray();

	CompositeImage<>* GetComposite();

protected:
	//metadata
	int status[8];

	Image baseImage;
	CompositeImage<> composite;
};

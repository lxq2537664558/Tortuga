/* Copyright: (c) Kayne Ruse 2014
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
#ifndef ENEMYDATA_HPP_
#define ENEMYDATA_HPP_

#include "vector2.hpp"
#include "statistics.hpp"

//graphics
#ifdef GRAPHICS
 #include "sprite_sheet.hpp"
#endif

//std namespace
#include <string>

struct EnemyData {
	//metadata
	std::string handle;
	std::string avatar;

	//gameplay
	Statistics stats;

	//TODO: gameplay components: equipment, items, buffs, debuffs, rewards

	//active gameplay members
	//NOTE: these are lost when unloaded
#ifdef GRAPHICS
	SpriteSheet sprite;
	Vector2 origin = {0.0,0.0};
	Vector2 bounds = {0.0,0.0};
#endif
	int tableIndex;
	int atbGauge = 0;
};

#endif
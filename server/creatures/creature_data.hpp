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

#include "creature_defines.hpp"
#include "entity.hpp"

#include "lua.hpp"

#include <map>
#include <string>

/* DOCS: Creature attributes, read more
 *  species (avatar, script)
 *  level
 *  health/mana
 *  permadeath/respawn
*/

class CreatureData: public Entity {
public:
	CreatureData(std::string avatar, int scriptRef);
	~CreatureData() = default;

	virtual int Update(lua_State*);

	//accessors & mutators

	std::string SetAvatar(std::string);
	std::string GetAvatar();

	int SetScriptReference(int);
	int GetScriptReference();

	std::string SetTag(std::string key, std::string value);
	std::string GetTag(std::string key);

private:
	friend class CreatureManager;

	std::string avatar;
	int scriptRef = LUA_NOREF;
	std::map<std::string, std::string> tags;
};

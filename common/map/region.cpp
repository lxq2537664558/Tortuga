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
#include "region.hpp"

#include "utility.hpp"

#include <stdexcept>
#include <cstring>

Region::Region(int argX, int argY): x(argX), y(argY) {
	if (x != snapToBase(REGION_WIDTH, x) || y != snapToBase(REGION_HEIGHT, y)) {
		throw(std::invalid_argument("Region location is off grid"));
	}
	memset(tiles, 0, REGION_WIDTH*REGION_HEIGHT*REGION_DEPTH*sizeof(type_t));
}

Region::Region(Region const& rhs): x(rhs.x), y(rhs.y) {
	memcpy(tiles, rhs.tiles, REGION_WIDTH*REGION_HEIGHT*REGION_DEPTH*sizeof(type_t));
}

Region::type_t Region::SetTile(int x, int y, int z, type_t v) {
	return tiles[x][y][z] = v;
}

Region::type_t Region::GetTile(int x, int y, int z) {
	return tiles[x][y][z];
}
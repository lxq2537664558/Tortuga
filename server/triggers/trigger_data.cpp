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
#include "trigger_data.hpp"

std::string TriggerData::SetHandle(std::string s) {
	return handle = s;
}

std::string TriggerData::GetHandle() const {
	return handle;
}

Vector2 TriggerData::SetOrigin(Vector2 v) {
	return origin = v;
}

Vector2 TriggerData::GetOrigin() {
	return origin;
}

BoundingBox TriggerData::SetBoundingBox(BoundingBox b) {
	return bounds = b;
}

BoundingBox TriggerData::GetBoundingBox() {
	return bounds;
}

int TriggerData::SetScriptReference(int i) {
	return scriptRef = i;
}

int TriggerData::GetScriptReference() {
	return scriptRef;
}

std::list<Entity*>* TriggerData::GetExclusionList() {
	return &exclusionList;
}
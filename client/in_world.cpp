/* Copyright: (c) Kayne Ruse 2013
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
#include "in_world.hpp"

#include <iostream>

using namespace std;

//-------------------------
//Public access members
//-------------------------

InWorld::InWorld() {
#ifdef DEBUG
	cout << "entering InWorld" << endl;
#endif
	cout << "Client Index: " << infoMgr->GetClientIndex() << endl;
	font.SetSurface(surfaceMgr->Get("font"));

	//debugging
	Packet::Packet p;
	p.meta.type = Packet::Type::PLAYER_NEW;
	snprintf(p.playerData.handle, PACKET_STRING_SIZE, "%s", configUtil->CString("handle"));
	snprintf(p.playerData.avatar, PACKET_STRING_SIZE, "%s", configUtil->CString("avatar"));
	p.playerData.position = {0, 50};
	p.playerData.motion = {140, 0};

	netUtil->Send(GAME_CHANNEL, &p, sizeof(Packet::Packet));

	//request a sync
	p.meta.type = Packet::Type::SYNCHRONIZE;
	p.synchronize.clientIndex = infoMgr->GetClientIndex();
	netUtil->Send(GAME_CHANNEL, &p, sizeof(Packet::Packet));
}

InWorld::~InWorld() {
#ifdef DEBUG
	cout << "leaving InWorld" << endl;
#endif
}

//-------------------------
//Frame loop
//-------------------------

void InWorld::FrameStart() {
	//
}

void InWorld::Update(double delta) {
	while(HandlePacket(popNetworkPacket()));

	for (auto& it : playerCharacters) {
		it.second.Update(delta);
	}
}

void InWorld::FrameEnd() {
	//
}

void InWorld::Render(SDL_Surface* const screen) {
	ClockFrameRate();

	for (auto& it : playerCharacters) {
		it.second.DrawTo(screen);
	}

	//since we're using this twice, make a tmp var
	string fps = itos(GetFrameRate());
	font.DrawStringTo(fps, screen, screen->w - fps.size() * font.GetCharW(), 0);
}

//-------------------------
//Event handlers
//-------------------------

void InWorld::QuitEvent() {
	//ensure that the client is disconnected properly
	ExitGame();
	SetNextScene(SceneList::QUIT);
}

void InWorld::MouseMotion(SDL_MouseMotionEvent const& motion) {
	//
}

void InWorld::MouseButtonDown(SDL_MouseButtonEvent const& button) {
	//
}

void InWorld::MouseButtonUp(SDL_MouseButtonEvent const& button) {
	//
}

void InWorld::KeyDown(SDL_KeyboardEvent const& key) {
	switch(key.keysym.sym) {
		case SDLK_ESCAPE:
			ExitGame();
			break;
		case SDLK_w:
			//up
		break;
		case SDLK_s:
			//down
		break;
		case SDLK_a:
			//left
		break;
		case SDLK_d:
			//right
		break;
	}
}

void InWorld::KeyUp(SDL_KeyboardEvent const& key) {
	//reversed
	switch(key.keysym.sym) {
		case SDLK_w:
			//
		break;
		case SDLK_s:
			//
		break;
		case SDLK_a:
			//
		break;
		case SDLK_d:
			//
		break;
	}
}

//-------------------------
//Utilities
//-------------------------

int InWorld::HandlePacket(Packet::Packet p) {
	switch(p.meta.type) {
		case Packet::Type::NONE:
			//DO NOTHING
			return 0;
		break;
		case Packet::Type::PING:
			//quick pong
			p.meta.type = Packet::Type::PONG;
			netUtil->Send(&p.meta.address, &p, sizeof(Packet::Packet));
		break;
		case Packet::Type::PONG:
			//
		break;
//		case Packet::Type::BROADCAST_REQUEST:
//			//
//		break;
//		case Packet::Type::BROADCAST_RESPONSE:
//			//
//		break;
//		case Packet::Type::JOIN_REQUEST:
//			//
//		break;
//		case Packet::Type::JOIN_RESPONSE:
//			//
//		break;
		case Packet::Type::DISCONNECT:
			HandleDisconnection(p.disconnect);
		break;
//		case Packet::Type::SYNCHRONIZE:
//			//
//		break;
		case Packet::Type::PLAYER_NEW:
			AddPlayer(p.playerData);
		break;
		case Packet::Type::PLAYER_DELETE:
			RemovePlayer(p.playerDelete);
		break;
		case Packet::Type::PLAYER_UPDATE:
			UpdatePlayer(p.playerData);
		break;
		default:
			throw(runtime_error("Failed to recognize the packet type: " + itos(int(p.meta.type))));
	}
	return 1;
}

void InWorld::Disconnect() {
	//disconnect
	Packet::Packet p;
	p.meta.type = Packet::Type::DISCONNECT;
	p.disconnect.clientIndex = infoMgr->GetClientIndex();
	netUtil->Send(GAME_CHANNEL, reinterpret_cast<void*>(&p), sizeof(Packet::Packet));
	netUtil->Unbind(GAME_CHANNEL);

	//reset the client
	infoMgr->ResetClientIndex();
}

void InWorld::ExitGame() {
	Disconnect();
	SetNextScene(SceneList::MAINMENU);
	endQueueThread();
	cout << "The game session has ended" << endl;
}

void InWorld::HandleDisconnection(Packet::Disconnect& disconnect) {
	Disconnect();
	SetNextScene(SceneList::MAINMENU);
	endQueueThread();
	cout << "You have been disconnected" << endl;
}

void InWorld::AddPlayer(Packet::PlayerData& p) {
	//sprite
	playerCharacters[p.playerIndex].GetSprite()->SetSurface(surfaceMgr->Get(p.avatar), 32, 48);

	//pos
	playerCharacters[p.playerIndex].SetPosition(p.position);
	playerCharacters[p.playerIndex].SetMotion(p.motion);

	//debugging
	cout << "New player, index " << p.playerIndex << endl;
}

void InWorld::RemovePlayer(Packet::PlayerDelete& p) {
	//
}

void InWorld::UpdatePlayer(Packet::PlayerData& p) {
	if (playerCharacters.find(p.playerIndex) == playerCharacters.end()) {
		AddPlayer(p);
		return;
	}

	playerCharacters[p.playerIndex].SetPosition(p.position);
	playerCharacters[p.playerIndex].SetMotion(p.motion);
}

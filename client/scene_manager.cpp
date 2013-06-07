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
#include "scene_manager.hpp"

#include <stdexcept>
#include <chrono>

//-------------------------
//Scene headers
//-------------------------

//Add the custom scene headers here
#include "in_combat.hpp"
#include "in_world.hpp"
#include "lobby.hpp"
#include "main_menu.hpp"
#include "option_screen.hpp"
#include "splash_screen.hpp"

//-------------------------
//Public access members
//-------------------------

SceneManager::SceneManager() {
	activeScene = nullptr;
}

SceneManager::~SceneManager() {
	UnloadScene();
}

void SceneManager::Init() {
	if (SDL_Init(SDL_INIT_VIDEO))
		throw(std::runtime_error("Failed to initialize SDL"));

	BaseScene::SetScreen(800, 600);
}

void SceneManager::Proc() {
	LoadScene(SceneList::FIRST);

	//prepare the time system
	typedef std::chrono::high_resolution_clock Clock;

	Clock::duration delta(16 * Clock::duration::period::den / std::milli::den);
	Clock::time_point simTime = Clock::now();
	Clock::time_point realTime;

	//The main loop
	while(activeScene->GetNextScene() != SceneList::QUIT) {
		//switch scenes when necessary
		if (activeScene->GetNextScene() != SceneList::CONTINUE) {
			LoadScene(activeScene->GetNextScene());
			continue;
		}

		//update the current time
		realTime = Clock::now();

		//simulate game time
		while (simTime < realTime) {
			//call each user defined function
			activeScene->RunFrame(double(delta.count()) / Clock::duration::period::den);
			simTime += delta;
		}

		//draw the game to the screen
		activeScene->RenderFrame();

		//give the computer a break
		SDL_Delay(10);
	}

	UnloadScene();
}

void SceneManager::Quit() {
	UnloadScene();
	SDL_Quit();
}

//-------------------------
//Private access members
//-------------------------

void SceneManager::LoadScene(SceneList sceneIndex) {
	UnloadScene();

	switch(sceneIndex) {
		//add scene creation calls here
		case SceneList::INCOMBAT:
			activeScene = new InCombat();
		break;
		case SceneList::INWORLD:
			activeScene = new InWorld();
		break;
		case SceneList::LOBBY:
			activeScene = new Lobby();
		break;
		case SceneList::MAINMENU:
			activeScene = new MainMenu();
		break;
		case SceneList::OPTIONSCREEN:
			activeScene = new OptionScreen();
		break;
		case SceneList::FIRST:
		case SceneList::SPLASHSCREEN:
			activeScene = new SplashScreen();
		break;

		default:
			throw(std::logic_error("Failed to recognize the scene index"));
	}
}

void SceneManager::UnloadScene() {
	delete activeScene;
	activeScene = nullptr;
}

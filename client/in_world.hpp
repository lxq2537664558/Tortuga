#ifndef INWORLD_HPP_
#define INWORLD_HPP_

#include "base_scene.hpp"

class InWorld : public BaseScene {
public:
	/* Public access members */
	InWorld();
	~InWorld();

protected:
	/* Frame loop */
	void FrameStart();
	void Update(double delta);
	void FrameEnd();
	void Render(SDL_Surface* const);

	/* Event handlers */
	void MouseMotion(SDL_MouseMotionEvent const&);
	void MouseButtonDown(SDL_MouseButtonEvent const&);
	void MouseButtonUp(SDL_MouseButtonEvent const&);
	void KeyDown(SDL_KeyboardEvent const&);
	void KeyUp(SDL_KeyboardEvent const&);
};

#endif
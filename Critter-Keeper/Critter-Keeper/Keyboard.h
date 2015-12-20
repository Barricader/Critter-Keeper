#pragma once
#include <SDL.h>

class Keyboard {
	private:
		static SDL_Event ev;

	public:
		static bool left, right, up, down;
		//static bool right;
		//static bool up;
		//static bool down;

		Keyboard();

		void static poll();

};
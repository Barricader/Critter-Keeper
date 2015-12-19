#pragma once
#include <SDL.h>

class Keyboard {
	private:
		static SDL_Event ev;

	public:
		static bool keys[255];
		static bool left;
		static bool right;
		static bool up;
		static bool down;

		Keyboard();

		void static poll();

};
#include <iostream>
#include "App.h"
#include "Keyboard.h"

bool Keyboard::left = false, Keyboard::right = false, Keyboard::up = false, Keyboard::down = false;
SDL_Event Keyboard::ev;

Keyboard::Keyboard() {
	left = false;
	right = false;
	up = false;
	down = false;
}

void Keyboard::poll() {
	bool test = true;
	while (test) {
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				test = false;
				App::setRunning(false);
			}

			if (ev.type == SDL_KEYDOWN) {
				switch (ev.key.keysym.sym) {
					case SDLK_a:
						if (!left) {
							left = true;
						}
						break;
					case SDLK_d:
						if (!right) {
							right = true;
						}
						break;
					case SDLK_w:
						if (!up) {
							up = true;
						}
						break;
					case SDLK_s:
						if (!down) {
							down = true;
						}
						break;
					case SDLK_LEFT:
						if (!left) {
							left = true;
						}
						break;
					case SDLK_RIGHT:
						if (!right) {
							right = true;
						}
						break;
					case SDLK_UP:
						if (!up) {
							up = true;
						}
						break;
					case SDLK_DOWN:
						if (!down) {
							down = true;
						}
						break;
				}

				//std::cout << "Key pressed: " << ev.key.keysym.sym << std::endl;
				}

			if (ev.type == SDL_KEYUP) {
				switch (ev.key.keysym.sym) {
					case SDLK_a:
						if (left) {
							left = false;
						}
						break;
					case SDLK_d:
						if (right) {
							right = false;
						}
						break;
					case SDLK_w:
						if (up) {
							up = false;
						}
						break;
					case SDLK_s:
						if (down) {
							down = false;
						}
						break;
					case SDLK_LEFT:
						if (left) {
							left = false;
						}
						break;
					case SDLK_RIGHT:
						if (right) {
							right = false;
						}
						break;
					case SDLK_UP:
						if (up) {
							up = false;
						}
						break;
					case SDLK_DOWN:
						if (down) {
							down = false;
						}
						break;
					case SDLK_ESCAPE:
						test = false;
						App::setRunning(false);
						break;
				}

				//std::cout << "Key unpressed: " << ev.key.keysym.sym << std::endl;
			}
		}
	}
}
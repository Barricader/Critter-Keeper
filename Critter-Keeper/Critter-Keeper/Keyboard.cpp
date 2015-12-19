#include <iostream>
#include "App.h"
#include "Keyboard.h"

bool Keyboard::left = false;
bool Keyboard::right = false;
bool Keyboard::up = false;
bool Keyboard::down = false;
bool Keyboard::keys[255];
SDL_Event Keyboard::ev;

Keyboard::Keyboard() {
	left = false;
	right = false;
	up = false;
	down = false;

	for (int i = 0; i < sizeof(keys); i++) {
		keys[i] = false;
	}
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
				if (ev.key.keysym.sym != SDLK_LEFT && ev.key.keysym.sym != SDLK_RIGHT &&
					ev.key.keysym.sym != SDLK_UP && ev.key.keysym.sym != SDLK_DOWN) {
					keys[ev.key.keysym.sym] = true;
					std::cout << "Key pressed: " << ev.key.keysym.sym << std::endl;
				}
				else {
					switch (ev.key.keysym.sym) {
						case SDLK_LEFT:
							left = true;
							break;
						case SDLK_RIGHT:
							right = true;
							break;
						case SDLK_UP:
							up = true;
							break;
						case SDLK_DOWN:
							down = true;
							break;
					}

					std::cout << "Key pressed: " << ev.key.keysym.sym << std::endl;
				}
			}
			else if (ev.type == SDL_KEYUP) {
				if (ev.key.keysym.sym != SDLK_LEFT && ev.key.keysym.sym != SDLK_RIGHT &&
					ev.key.keysym.sym != SDLK_UP && ev.key.keysym.sym != SDLK_DOWN) {
					keys[ev.key.keysym.sym] = false;
					std::cout << "Key unpressed: " << ev.key.keysym.sym << std::endl;
					if (ev.key.keysym.sym == SDLK_ESCAPE) {
						test = false;
						App::setRunning(false);
					}
				}
				else {
					switch (ev.key.keysym.sym) {
					case SDLK_LEFT:
						left = false;
						break;
					case SDLK_RIGHT:
						right = false;
						break;
					case SDLK_UP:
						up = false;
						break;
					case SDLK_DOWN:
						down = false;
						break;
					}
					std::cout << "Key unpressed: " << ev.key.keysym.sym << std::endl;
				}
			}
		}
	}
}
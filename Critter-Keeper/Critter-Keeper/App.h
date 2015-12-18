#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class App {
	private:
		std::string message;
		bool running;
		SDL_Event ev;
		SDL_Window* window = NULL;
		SDL_Renderer* rend = NULL;
		SDL_Surface* surf = NULL;
		SDL_Surface* hello = NULL;

	public:
		const int WIDTH = 1280;
		const int HEIGHT = 720;

		App(std::string text);

		void init();

		void loadAll();

		void update();

		SDL_Surface* loadImage(std::string path);

		void exit();

		std::string getMessage() {
			return message;
		}

		SDL_Window* getWindow() {
			return window;
		}

		SDL_Surface* getSurf() {
			return surf;
		}

		SDL_Surface* getHello() {
			return hello;
		}
};
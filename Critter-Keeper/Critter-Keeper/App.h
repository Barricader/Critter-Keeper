#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <thread>
#include <iostream>
#include "Keyboard.h"

class App {
	private:
		std::string message;
		static bool running;
		SDL_Event ev;
		SDL_Window* window = NULL;
		SDL_Renderer* rend = NULL;
		SDL_Surface* surf = NULL;
		SDL_Surface* hello = NULL;
		SDL_Texture* curText = NULL;

	public:
		const int WIDTH = 1280;
		const int HEIGHT = 720;

		App(std::string text);

		void init();

		void loadAll();

		void update();

		SDL_Surface* loadImage(std::string path);
		SDL_Texture* loadTexture(std::string path);

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

		static void setRunning(bool running) {
			App::running = running;
		}
};
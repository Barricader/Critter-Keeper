#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <thread>
#include <iostream>
#include <vector>
#include <ctime>
#include "Keyboard.h"
#include "Entity.h"
#include "Player.h"
#include "Map.h"
#include "Tile.h"

class App {
	private:
		static bool running;
		SDL_Event ev;
		SDL_Window* window = NULL;
		static SDL_Renderer* rend;
		SDL_Texture* curText = NULL;
		std::vector<Entity*> entities;
		Player* player;
		Map* curMap;

	public:
		const int WIDTH = 1280;
		const int HEIGHT = 720;

		App();

		void init();

		void loadAll();

		void update();

		SDL_Texture* loadTexture(std::string path);

		void exit();

		SDL_Window* getWindow() {
			return window;
		}

		static SDL_Renderer* getRend() {
			return rend;
		}

		static void setRunning(bool running) {
			App::running = running;
		}
};
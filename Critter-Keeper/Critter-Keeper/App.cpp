#include <iostream>
#include "App.h"

using namespace std;

App::App(std::string text) {
	message = text;
	running = true;
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	cout << "Initialized SDL" << endl;
}

void App::init() {
	// Creating the window object
	window = SDL_CreateWindow("Critter Keeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	// Creating a surface to draw on from the window
	surf = SDL_GetWindowSurface(window);

	// Creating a black background
	SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 200, 200, 200));

	// Update the surface
	SDL_UpdateWindowSurface(window);

	cout << "Initialized window and window surface" << endl;
}

void App::loadAll() {
	hello = loadImage("res\\hello.png");

	cout << "Loaded all required images" << endl;
}

void App::update() {
	while (running) {
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				running = false;
			}
		}

		// Draw all surfaces
		SDL_BlitSurface(hello, NULL, surf, NULL);

		// Update the window surface
		SDL_UpdateWindowSurface(window);
	}
}

SDL_Surface* App::loadImage(std::string path) {
	SDL_Surface* newSurf = NULL;

	SDL_Surface* loaded = IMG_Load(path.c_str());
	if (loaded == NULL) {
		cerr << "Unable to load image " << path.c_str() << "! SDL_Image Error: " << IMG_GetError() << endl;
	}
	else {
		newSurf = SDL_ConvertSurface(loaded, surf->format, NULL);
		SDL_FreeSurface(loaded);
	}

	cout << "Loaded image: " << path << endl;

	return newSurf;
}

void App::exit() {
	SDL_DestroyWindow(window);
	SDL_FreeSurface(surf);
	SDL_FreeSurface(hello);

	SDL_Quit();
	
	cout << "Freeing surfaces and window\nExiting SDL" << endl;
}

int main(int argc, char* argv[]) {
	App myApp = App("Hello");
	myApp.init();
	myApp.loadAll();

	myApp.update();

	cout << myApp.getMessage() << endl;

	//cin.get();
	//cin.ignore();

	myApp.exit();

	return 0;
}
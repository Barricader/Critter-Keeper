#include "App.h"

using namespace std;

std::thread keyThread;
bool App::running = true;

App::App(std::string text) {
	message = text;
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	keyThread = std::thread(&Keyboard::poll);
	cout << "Initialized SDL and keyboard" << endl;
}

void App::init() {
	// Creating the window object
	window = SDL_CreateWindow("Critter Keeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	// Creating renderer
	rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(rend, 200, 200, 200, 255);

	// Creating a surface to draw on from the window
	//surf = SDL_GetWindowSurface(window);

	// Creating a black background
	//SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 200, 200, 200));

	// Update the surface
	SDL_UpdateWindowSurface(window);

	cout << "Initialized window and window surface" << endl;
}

void App::loadAll() {
	curText = loadTexture("res\\hello.png");

	cout << "Loaded all required images" << endl;
}

void App::update() {
	while (running) {
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				running = false;
			}
		}

		if (Keyboard::left) {
			cout << "LEFT" << endl;
		}
		if (Keyboard::right) {
			cout << "RIGHT" << endl;
		}
		if (Keyboard::up) {
			cout << "UP" << endl;
		}
		if (Keyboard::down) {
			cout << "DOWN" << endl;
		}

		SDL_RenderClear(rend);
		int tempW;
		int tempH;
		SDL_QueryTexture(curText, NULL, NULL, &tempW, &tempH);
		SDL_Rect tempRect;
		tempRect.x = 0;
		tempRect.y = 0;
		tempRect.w = tempW;
		tempRect.h = tempH;
		SDL_RenderCopy(rend, curText, NULL, &tempRect);
		SDL_RenderPresent(rend);
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

SDL_Texture* App::loadTexture(std::string path) {
	SDL_Texture* newText = NULL;

	SDL_Surface* loaded = IMG_Load(path.c_str());
	if (loaded == NULL) {
		cerr << "Unable to load image " << path.c_str() << "! SDL_Image Error: " << IMG_GetError() << endl;
	}
	else {
		newText = SDL_CreateTextureFromSurface(rend, loaded);
		SDL_FreeSurface(loaded);
	}

	cout << "Loaded image: " << path << endl;

	return newText;
}

void App::exit() {
	SDL_DestroyTexture(curText);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	SDL_FreeSurface(surf);
	SDL_FreeSurface(hello);

	keyThread.join();

	IMG_Quit();
	SDL_Quit();
	
	cout << "Freeing surfaces and window\nExiting SDL" << endl;
}

int main(int argc, char* argv[]) {
	App myApp = App("Hello");
	myApp.init();
	myApp.loadAll();

	myApp.update();

	//cout << myApp.getMessage() << endl;

	myApp.exit();

	return 0;
}
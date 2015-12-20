#include "App.h"
/**
	@author Jo
	@purpose Actual app and start of game flow
*/

using namespace std;

std::thread keyThread;
bool App::running = true;
SDL_Renderer* App::rend = NULL;

// TODO: clean up all this

App::App() {
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

	// Update the surface
	SDL_UpdateWindowSurface(window);

	cout << "Initialized window and window surface" << endl;

	player = new Player("res\\p.png", 20, 40, 32, 32);
	cout << player->getSprite()->getSize()->w << endl;
	entities.push_back(player);
}

void App::loadAll() {
	curText = loadTexture("res\\hello.png");

	cout << "Loaded all required images" << endl;
}

void App::update() {
	clock_t start = clock();
	while (running) {
		while (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				running = false;
			}
		}

		// update all entities here
		clock_t now = clock();
		if (now - start >= 16.666) {
			start = clock();
			if (Keyboard::left) {
				cout << "l";
				player->move(player->getX() - 2, player->getY());
			}
			if (Keyboard::right) {
				player->move(player->getX() + 2, player->getY());
			}
			if (Keyboard::up) {

				player->move(player->getX(), player->getY() - 2);
			}
			if (Keyboard::down) {

				player->move(player->getX(), player->getY() + 2);
			}
		}

		// Render all entities below
		SDL_RenderClear(rend);

		int tempW;
		int tempH;
		SDL_QueryTexture(curText, NULL, NULL, &tempW, &tempH);
		SDL_Rect tempRect;
		tempRect.x = 30;
		tempRect.y = 30;
		tempRect.w = tempW;
		tempRect.h = tempH;

		SDL_RenderCopy(rend, curText, NULL, &tempRect);

		for (int i = 0; i < entities.size(); i++) {
			int tW;
			int tH;
			SDL_QueryTexture(entities[i]->getSprite()->getTexture(), NULL, NULL, &tW, &tH);
			SDL_Rect tR;
			tR.x = entities[i]->getX();
			tR.y = entities[i]->getY();
			tR.w = tW;
			tR.h = tH;

			SDL_RenderCopy(rend, entities[i]->getSprite()->getTexture(), NULL, &tR);
		}

		// Have a render loop here

		SDL_RenderPresent(rend);
	}
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

	delete player;

	keyThread.join();

	IMG_Quit();
	SDL_Quit();
	
	cout << "Freeing surfaces and window\nExiting SDL" << endl;
}

int main(int argc, char* argv[]) {
	App myApp = App();
	myApp.init();
	myApp.loadAll();

	myApp.update();

	myApp.exit();

	return 0;
}
#include "App.h"
/**
	@author Jo
	@purpose Actual app and start of game flow
*/

using namespace std;

std::thread keyThread;
bool App::running = true;
SDL_Renderer* App::rend = NULL;

// TODO: clean up all this e.g. put into folders, clean up code, use better standards, etc
// TODO: add destructors and start allocating to heap and deleting object once their usage is over
// TODO: remove player class and enable wasd/arrows/mouse to move camera around

App::App() {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	keyThread = std::thread(&Keyboard::poll);
	cout << "Initialized SDL and keyboard" << endl;
}

void App::init() {
	// Creating the window object
	window = SDL_CreateWindow("Critter Keeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	// Creating renderer     ---------> To disable vysnc, remove the right flag and the bitwise or
	rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(rend, 200, 200, 200, 255);

	// Update the surface
	SDL_UpdateWindowSurface(window);

	cout << "Initialized window and window surface" << endl;

	//player = new Player("res\\p.png", 20, 40, 32, 32);
	//cout << player->getSprite()->getSize()->w << endl;
	//entities.push_back(player);
}

void App::loadAll() {
	curText = loadTexture("res\\hello.png");
	curMap = new Map("res\\m2.json");

	cout << "Checking for size of tile vector: " << curMap->getTiles()->size() << endl;

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
				//player->move(player->getPos().dX - 2, player->getPos().dY);
				xOffset -= 3;
			}
			if (Keyboard::right) {
				//player->move(player->getPos().dX + 2, player->getPos().dY);
				xOffset += 3;
			}
			if (Keyboard::up) {
				//player->move(player->getPos().dX, player->getPos().dY - 2);
				yOffset -= 3;
			}
			if (Keyboard::down) {
				//player->move(player->getPos().dX, player->getPos().dY + 2);
				yOffset += 3;
			}
		}

		// Render all entities below
		SDL_RenderClear(rend);

		// get the path from the curMap
		// render each tile here, have the tile sprite based on the state
		// e.g. if state == 2 then draw tile 0,32 on the spritesheet
		for (int i = 0; i < curMap->getTiles()->size(); i++) {
			SDL_Rect tR;
			tR.x = curMap->getTiles()->at(i).getPos().dX - xOffset;
			tR.y = curMap->getTiles()->at(i).getPos().dY - yOffset;
			tR.w = 32;
			tR.h = 32;

			SDL_Rect tR2;
			
			// TODO: change the multiples of 32 and harcode it and just multiply it
			// e.g. curMap->getSheet()->getSpriteSize() * X; WHERE X = like 0, 1, or 2

			if (curMap->getTiles()->at(i).getState() == 1) {
				tR2.x = 0;
				tR2.y = 0;
			}
			if (curMap->getTiles()->at(i).getState() == 2) {
				tR2.x = 32;
				tR2.y = 0;
			}
			if (curMap->getTiles()->at(i).getState() == 3) {
				tR2.x = 64;
				tR2.y = 0;
			}
			if (curMap->getTiles()->at(i).getState() == 4) {
				tR2.x = 0;
				tR2.y = 32;
			}
			if (curMap->getTiles()->at(i).getState() == 5) {
				tR2.x = 32;
				tR2.y = 32;
			}
			if (curMap->getTiles()->at(i).getState() == 6) {
				tR2.x = 64;
				tR2.y = 32;
			}

			tR2.w = 32;
			tR2.h = 32;

			SDL_RenderCopy(rend, curMap->getSheet()->getTexture(), &tR2, &tR);
		}

		// TODO: only draw if the tile is on screen by check the x and ys of the tile and camera

		for (int i = 0; i < entities.size(); i++) {
			int tW;
			int tH;
			SDL_QueryTexture(entities[i]->getSprite()->getTexture(), NULL, NULL, &tW, &tH);
			SDL_Rect tR;
			tR.x = entities[i]->getPos().dX;
			tR.y = entities[i]->getPos().dY;
			tR.w = tW;
			tR.h = tH;

			SDL_RenderCopy(rend, entities[i]->getSprite()->getTexture(), NULL, &tR);
			//SDL_RenderCopy(rend, curMap->getSheet()->getTexture(), NULL, &tR);
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

	/*&	TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
	*
	*	Make sure to free up all the textures and well, basically everything that is on the heap
	*	This should prevent memory leaks and make the program run smoother in the future
	*
	*	TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
	*/

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
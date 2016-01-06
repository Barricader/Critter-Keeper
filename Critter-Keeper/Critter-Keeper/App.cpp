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

// TODO: Decide how to handle tile drawing, we can decide to create a ton of values in the TILE_STATE enum
// or we can decide to create another variable in the tile where it will be a variation of that tile
// like a barracks tile can have a regular wood floor sprite tile, or a bed sprite tile, or table, etc

// TODO: Depending on the size of the room, that will decide on what variation tile will go where
// i.e. if it is a 5x5 room, it might have a bed sprite in the (1, 0) and (3, 0) coords where (0,0) is the
// top left of the room

// In the spritesheet the columns will be seperate tile sprites i.e. dirt tile, barracks tile
// The row of each column will be the variations of each tile sprite

// The variation tiles will probably not have collision to make it easier to build rooms

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

	// TODO: Remove this and the Player class, we do not have a player
	// This is just here to show how to add an entity to the App class
	//player = new Player("res\\p.png", 20, 40, 32, 32);
	//cout << player->getSprite()->getSize()->w << endl;
	//entities.push_back(player);
}

void App::loadAll() {
	curText = loadTexture("res\\hello.png");
	// TODO: fix error where it will send a nullptr exception if the file does not exist
	curMap = new Map("res\\dirtMap.json");

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
				xOffset -= 3;
			}
			if (Keyboard::right) {
				xOffset += 3;
			}
			if (Keyboard::up) {
				yOffset -= 3;
			}
			if (Keyboard::down) {
				yOffset += 3;
			}
		}
		// HI! :-)
		// Render loop
		SDL_RenderClear(rend);

		// get the path from the curMap
		// render each tile here, have the tile sprite based on the state
		// e.g. if state == 2 then draw tile 0,TILESIZE (where TILESIZe is the size of the tile) on the spritesheet
		// We are assuming that the tile width is the same as the tile height   !!Maybe not!!
		
		// TODO: put this someone where it will only be set once to save cycles
		int totalSprites = (curMap->getSheet()->getSize()->w * curMap->getSheet()->getSize()->h) / (curMap->getTiles()->at(0).getSize().w * curMap->getTiles()->at(0).getSize().h);

		for (int i = 0; i < curMap->getTiles()->size(); i++) {
			if (curMap->getTiles()->at(i).getPos().dX - xOffset + curMap->getTiles()->at(i).getSize().w > 0 ||
				curMap->getTiles()->at(i).getPos().dX - xOffset < WIDTH ||
				curMap->getTiles()->at(i).getPos().dY - yOffset + curMap->getTiles()->at(i).getSize().h > 0 ||
				curMap->getTiles()->at(i).getPos().dY - yOffset < HEIGHT) {
				SDL_Rect tR;
				tR.x = curMap->getTiles()->at(i).getPos().dX - xOffset;
				tR.y = curMap->getTiles()->at(i).getPos().dY - yOffset;
				tR.w = curMap->getTiles()->at(i).getSize().w;
				tR.h = curMap->getTiles()->at(i).getSize().w;

				SDL_Rect tR2;

				int tW;
				int tH;
				SDL_QueryTexture(curMap->getSheet()->getTexture(), NULL, NULL, &tW, &tH);

				// Checks the state of a tile and sets the sprite from the spritesheet to use for that tile
				if (curMap->getTiles()->at(i).getState() != 0 && curMap->getTiles()->at(i).getState() <= totalSprites) {
					//cout << (curMap->getTiles()->at(i).getState() - 1) * curMap->getTiles()->at(i).getSize().w << endl;
					tR2.x = ((curMap->getTiles()->at(i).getState() - 1) * curMap->getTiles()->at(i).getSize().w) % curMap->getSheet()->getSize()->w;
					tR2.y = (((curMap->getTiles()->at(i).getState() - 1) * curMap->getTiles()->at(i).getSize().w) / curMap->getSheet()->getSize()->w)  * curMap->getTiles()->at(i).getSize().w;
				}
				else {
					// Give it a null tile sprite
					tR2.x = -curMap->getTiles()->at(i).getSize().w;
					tR2.y = -curMap->getTiles()->at(i).getSize().w;
				}
				
				tR2.w = curMap->getTiles()->at(i).getSize().w;
				tR2.h = curMap->getTiles()->at(i).getSize().w;

				SDL_RenderCopy(rend, curMap->getSheet()->getTexture(), &tR2, &tR);
			}
		}

		// TODO: only draw if the entity is on screen by check the x and ys of the entity and camera -> DONE?

		for (int i = 0; i < entities.size(); i++) {
			if (entities[i]->getPos().dX - xOffset + entities[i]->getSize().w > 0 ||
				entities[i]->getPos().dX - xOffset < WIDTH ||
				entities[i]->getPos().dY - yOffset + entities[i]->getSize().h > 0 ||
				entities[i]->getPos().dY - yOffset < HEIGHT) {
				int tW;
				int tH;
				SDL_QueryTexture(entities[i]->getSprite()->getTexture(), NULL, NULL, &tW, &tH);
				SDL_Rect tR;
				tR.x = entities[i]->getPos().dX;
				tR.y = entities[i]->getPos().dY;
				tR.w = tW;
				tR.h = tH;

				SDL_RenderCopy(rend, entities[i]->getSprite()->getTexture(), NULL, &tR);
			}
		}

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

	/*	TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
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
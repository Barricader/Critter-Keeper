#pragma once
#include "Sprite.h"
#include "dVector.h"

class Tile {
	private:
		//Sprite* sprite;
		int x, y, w, h;
		uint8_t state;	// holds 0 - 255 - used for knowing if it is a dirt tile, sleeping quarters tile, training tile, gold vein wall, unbreakable wall, etc
		uint8_t variation;	// Used for selection a variation of a tile, it will allow a bit more detail

	public:
		Tile();
		Tile(std::string path, int x, int y, int w, int h, uint8_t state);
		Tile(const Tile &obj);
		~Tile();

		dVector getPos() {
			return dVector(x, y);
		}

		SDL_Rect getSize() {
			SDL_Rect temp;
			temp.w = w;
			temp.h = h;
			return temp;
		}

		uint8_t getState() {
			return state;
		}
};


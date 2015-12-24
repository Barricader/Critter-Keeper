#pragma once
#include "Sprite.h"
#include "dVector.h"

class Tile {
	private:
		Sprite* sprite;
		int x, y;
		//bool isWall;
		uint8_t state;	// holds 0 - 255 - used for knowing if it is a sleeping quarters tile, training tile, gold vein wall, unbreakable wlal, etc

	public:
		Tile(std::string path, int x, int y, int w, int h, uint8_t state);

		dVector getPos() {
			return dVector(x, y);;
		}

		//bool getIsWall() {
		//	return isWall;
		//}

		uint8_t getState() {
			return state;
		}
};


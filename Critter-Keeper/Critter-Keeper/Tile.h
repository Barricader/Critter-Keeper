#pragma once
#include "Sprite.h"

class Tile {
	private:
		Sprite* sprite;
		int x, y;

	public:
		Tile(std::string path, int x, int y, int w, int h);
};


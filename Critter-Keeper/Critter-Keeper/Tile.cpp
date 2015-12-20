#include "Tile.h"

Tile::Tile(std::string path, int x, int y, int w, int h) {
	sprite = &Sprite(path, w, h);
	this->x = x;
	this->y = y;
}

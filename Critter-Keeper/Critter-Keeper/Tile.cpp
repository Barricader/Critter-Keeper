#include "Tile.h"

Tile::Tile(std::string path, int x, int y, int w, int h, uint8_t state) {
	//sprite = &Sprite(path, w, h);
	this->x = x;
	this->y = y;
	//this->isWall = isWall;
	this->state = state;
}

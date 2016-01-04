#include "Tile.h"

Tile::Tile() {
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;
	this->state = 0;
}

Tile::Tile(std::string path, int x, int y, int w, int h, uint8_t state) {
	//sprite = &Sprite(path, w, h);
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	//this->isWall = isWall;
	this->state = state;
}

// Copy constructor
Tile::Tile(const Tile &obj) {
	//*sprite = *obj.sprite;
	x = obj.x;
	y = obj.y;
	w = obj.w;
	h = obj.h;
	state = obj.state;
}

Tile::~Tile() {

}
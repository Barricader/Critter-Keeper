#include "Entity.h"

Entity::Entity(std::string path, int x, int y, int w, int h) {
	sprite = new Sprite(path, w, h);
	this->x = x;
	this->y = y;
}

Entity::~Entity() {
	delete sprite;
}

Sprite* Entity::getSprite() {
	return sprite;
}

int Entity::getX() {
	return x;
}

int Entity::getY() {
	return y;
}
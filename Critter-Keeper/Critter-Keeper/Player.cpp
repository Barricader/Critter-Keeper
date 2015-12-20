#include "Player.h"

Player::Player(std::string path, int x, int y, int w, int h) : Entity(path, x, y, w, h) {

}

void Player::render(SDL_Renderer* rend) {
	int tempW;
	int tempH;
	SDL_QueryTexture(sprite->getTexture(), NULL, NULL, &tempW, &tempH);
	SDL_Rect tempRect;
	tempRect.x = 0;
	tempRect.y = 0;
	tempRect.w = tempW;
	tempRect.h = tempH;

	SDL_RenderCopy(rend, sprite->getTexture(), NULL, &tempRect);
}

void Player::move(int x, int y) {
	this->x = x;
	this->y = y;
}
#pragma once
#include "Entity.h"

// We don't need a player, this is just for testing
// It is just here to see a semi-correct implementation of the Entity class
class Player : public Entity {
	private:
		Sprite* sprite;

	public:
		Player(std::string path, int x, int y, int w, int h);

		void render(SDL_Renderer* rend);

		void move(int x, int y);
};


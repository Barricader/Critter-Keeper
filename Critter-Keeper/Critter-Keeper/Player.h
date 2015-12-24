#pragma once
#include "Entity.h"

// We don't need a player, this is just for testing
class Player : public Entity {
	private:
		Sprite* sprite;

	public:
		Player(std::string path, int x, int y, int w, int h);

		void render(SDL_Renderer* rend);

		void move(int x, int y);
};


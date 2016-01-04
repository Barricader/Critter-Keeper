#pragma once
#include "Sprite.h"
#include "dVector.h"

// This should be abstract
class Entity {
	private:

	protected:
		Sprite* sprite;
		int x, y;

	public:
		Entity(std::string path, int x, int y, int w, int h);
		~Entity();

		virtual void render(SDL_Renderer* rend) = 0;
		Sprite* getSprite();

		dVector getPos();
		SDL_Rect getSize();
};

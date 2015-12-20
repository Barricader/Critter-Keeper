#include "Sprite.h"
#include "App.h"

Sprite::Sprite(std::string path, int w, int h) {
	// Load texture from path here
	texture = NULL;

	SDL_Surface* loaded = IMG_Load(path.c_str());
	if (loaded == NULL) {
		std::cerr << "Unable to load image " << path.c_str() << "! SDL_Image Error: " << IMG_GetError() << std::endl;
	}
	else {
		texture = SDL_CreateTextureFromSurface(App::getRend(), loaded);
		SDL_FreeSurface(loaded);
	}

	std::cout << "Loaded image: " << path << std::endl;

	this->w = w;
	this->h = h;
}


SDL_Rect* Sprite::getSize() {
	SDL_Rect temp;
	temp.w = w;
	temp.h = h;

	return &temp;
}

SDL_Texture* Sprite::getTexture() {
	return texture;
}

#pragma once
#include "SDL_image.h"
#include <string>
#include <iostream>

class Sprite {
  private:
    int w, h;
    SDL_Texture* texture;

  public:
    Sprite(std::string path, int w, int h);

	SDL_Rect* getSize();

	SDL_Texture* getTexture();
};

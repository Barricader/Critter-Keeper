#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "Tile.h"
#include "rapidjson/reader.h"
#include "rapidjson/document.h"

class Map {
	private:
		Sprite* spritesheet;
		std::vector<Tile> tiles;

	public:
		Map();
		Map(std::string path);

		void render();
};
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
		//std::vector<Tile>* tiles = new std::vector<Tile>();
		std::vector<Tile>* tiles = nullptr;

	public:
		Map();
		Map(std::string path);
		~Map();

		//void render();

		Sprite* getSheet() {
			return spritesheet;
		}

		std::vector<Tile>* getTiles() {
			return tiles;
		}
};
#include "Map.h"

using namespace rapidjson;
using namespace std;

Map::Map() {
	// Generate a random map

}

Map::~Map() {
	delete tiles;
}

Map::Map(std::string path) {
	// Create a map based on a json file from tiled
	string fileText;
	string line;
	ifstream file(path);
	while (getline(file, line)) {
		fileText += line;
	}

	if (fileText.length() > 0) {
		cout << "Loaded " << path << " successfully" << endl;
	}

	// Create a DOM based object to hold the json data
	Document doc;
	doc.Parse(fileText.c_str());

	// TODO: shorten doc["layers"] to Value l
	// TODO: shorten all the doc stuff

	// A bunch of testing stuff
	assert(doc.IsObject());
	assert(doc.HasMember("layers"));
	assert(doc["layers"].IsArray());
	assert(doc["layers"][0].IsObject());

	// Get values from layers key
	assert(doc["layers"][0].HasMember("width"));
	assert(doc["layers"][0]["width"].IsNumber());
	assert(doc["layers"][0]["width"].IsInt());
	assert(doc["layers"][0].HasMember("height"));
	assert(doc["layers"][0]["height"].IsNumber());
	assert(doc["layers"][0]["height"].IsInt());

	// More stuff
	assert(doc.HasMember("tilesets"));
	assert(doc["tilesets"].IsArray());
	assert(doc["tilesets"][0].IsObject());

	// Get path stuff
	assert(doc["tilesets"][0].HasMember("image"));
	assert(doc["tilesets"][0]["image"].IsString());
	
	string imgPath = doc["tilesets"][0]["image"].GetString();
	spritesheet = new Sprite("res\\" + imgPath, 32, 32);

	// get data value from layers
	assert(doc["layers"][0].HasMember("data"));
	assert(doc["layers"][0]["data"].IsArray());
	const Value& data = doc["layers"][0]["data"];
	assert(data.IsArray());

	// copy stuff
	int size = doc["layers"][0]["width"].GetInt() * doc["layers"][0]["height"].GetInt();
	int* temp = new int[size];

	// Copy the array from json into a temp array
	for (int i = 0; i < size; i++) {
		temp[i] = data[i].GetInt();
		//cout << i << ": " << temp[i] << endl;
	}

	cout << "Loaded " << size << " tiles" << endl;

	// Generate tiles
	// Due to me being super lazy, I will not be using the tilewidth and height from the json
	// You can try if you want, the keys will be in the tilesets value array

	tiles = new std::vector<Tile>();
	//tiles = &vector<Tile>();
	short k = 0;
	for (int i = 0; i < doc["layers"][0]["height"].GetInt(); i++) {
		for (int j = 0; j < doc["layers"][0]["width"].GetInt(); j++) {
			tiles->push_back(Tile(imgPath, j * 32, i * 32, 32, 32, temp[k]));
			k++;
		}
	}

	cout << "test size: " << tiles->size() << endl;

	delete[] temp;
}

struct MyHandler {
	bool Null() { cout << "Null()" << endl; return true; }
	bool Bool(bool b) { cout << "Bool(" << boolalpha << b << ")" << endl; return true; }
	bool Int(int i) { cout << "Int(" << i << ")" << endl; return true; }
	bool Uint(unsigned u) { cout << "Uint(" << u << ")" << endl; return true; }
	bool Int64(int64_t i) { cout << "Int64(" << i << ")" << endl; return true; }
	bool Uint64(uint64_t u) { cout << "Uint64(" << u << ")" << endl; return true; }
	bool Double(double d) { cout << "Double(" << d << ")" << endl; return true; }
	bool String(const char* str, SizeType length, bool copy) {
		cout << "String(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
		return true;
	}
	bool StartObject() { cout << "StartObject()" << endl; return true; }
	bool Key(const char* str, SizeType length, bool copy) {
		cout << "Key(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
		return true;
	}
	bool EndObject(SizeType memberCount) { cout << "EndObject(" << memberCount << ")" << endl; return true; }
	bool StartArray() { cout << "StartArray()" << endl; return true; }
	bool EndArray(SizeType elementCount) { cout << "EndArray(" << elementCount << ")" << endl; return true; }
};
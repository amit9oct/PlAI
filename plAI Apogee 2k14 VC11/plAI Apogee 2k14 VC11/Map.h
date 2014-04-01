#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "Constants.h"

using namespace sf;

enum TileType
{
	UnknownTile, Land, Water
};

struct Tile
{
	TileType type;
	int x, y;
	bool hasFish;
};

typedef Tile* TileRow;

//Encloses an array of tiles
class Map
{

private:
	static void findMeanOfConnectedRegion(Map* map, sf::Image* img, int startX, int startY, sf::Color findColor, sf::Color replaceColor, int* meanX, int* meanY, int* numOfPoints);
	int initialNumberOfFish;
	int width;
	int height;
	Vector2i player1SpawnPoint;
	Vector2i player2SpawnPoint;
	Tile* tiles;

public:
	
	std::list<sf::Vector2i> fishLocations;

	Map();
	Map(int width, int height);
	void createBlank(int width, int height);
	void createFromImage(char* filename);
	Tile* getTile(int x, int y);
	bool checkForFish(int x, int y);
	int getInitialNumberOfFish();
	bool tryCatchFish(int x, int y);
	Vector2i getPlayer1SpawnPoint();
	Vector2i getPlayer2SpawnPoint();
	Vector2i getSize();
	~Map();
};
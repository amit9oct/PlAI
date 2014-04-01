#include "Map.h"
#include "Game.h"
#include <stdio.h>
#include<stdlib.h>
#include <SFML/Graphics.hpp>

using namespace sf;

Map::Map()
{

}

Map::Map(int width, int height)
{
	createBlank(width, height);
}

void Map::createBlank(int width, int height)
{
	this->initialNumberOfFish = 0;
	this->height = height;
	this->width = width;
	this->tiles = (Tile*)malloc(width*height*sizeof(Tile));

	if (this->tiles == NULL) throw std::exception("Unable to allocate memory for map");

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = y*width + x;
			tiles[index].x = x;
			tiles[index].y = y;
			tiles[index].type = TileType::UnknownTile;
			tiles[index].hasFish = false;
		}
	}
}

void Map::createFromImage(char* filename)
{
	initialNumberOfFish = 0;
	player1SpawnPoint = Vector2i(RAFT_RADIUS + 10, RAFT_RADIUS + 10);
	player2SpawnPoint = Vector2i(800 - RAFT_RADIUS - 10, RAFT_RADIUS + 10);

	sf::Image img;
	img.loadFromFile(filename);
	createBlank(img.getSize().x, img.getSize().y);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = y*width + x;

			if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
			{
				tiles[index].type = TileType::Land;
				continue;
			}
			
			Color col = img.getPixel(x, y);
			if (col==Color::Green)
			{
				tiles[index].type = TileType::Land;
			}
			else if (col==Color::White)
			{
				int meanX = 0, meanY = 0, numOfWhitePoints = 0;
				findMeanOfConnectedRegion(this, &img, x, y, Color::White, Color::Blue, &meanX, &meanY, &numOfWhitePoints);
				tiles[meanY*width + meanX].hasFish = true;
				fishLocations.push_back(Vector2i(meanX, meanY));
				initialNumberOfFish++;
			}
			else if (col==Color::Red)
			{
				int meanX = 0, meanY = 0, numOfRedPoints = 0;
				findMeanOfConnectedRegion(this, &img, x, y, Color::Red, Color::Blue, &meanX, &meanY, &numOfRedPoints);
				player1SpawnPoint = Vector2i(meanX, meanY);
			}
			else if (col == Color::Yellow)
			{
				int meanX = 0, meanY = 0, numOfYellowPoints = 0;
				findMeanOfConnectedRegion(this, &img, x, y, Color::Yellow, Color::Blue, &meanX, &meanY, &numOfYellowPoints);
				player2SpawnPoint = Vector2i(meanX, meanY);
			}
			else
			{
				tiles[index].type = TileType::Water;
			}
		}
	}
}

Tile* Map::getTile(int x, int y)
{
	return &tiles[y*this->width + x];
}

bool Map::checkForFish(int x, int y)
{
	return tiles[y*width + x].hasFish;
}

bool Map::tryCatchFish(int x, int y)
{
	if (!checkForFish(x, y)) return false;

	tiles[y*width + x].hasFish = false;

	fishLocations.remove(Vector2i(x, y));

	return true;
}

int Map::getInitialNumberOfFish()
{
	return initialNumberOfFish;
}

Vector2i Map::getPlayer1SpawnPoint()
{
	return player1SpawnPoint;
}

Vector2i Map::getPlayer2SpawnPoint()
{
	return player2SpawnPoint;
}

void Map::findMeanOfConnectedRegion(Map* map, Image* img, int startX, int startY, Color findColor, Color replaceColor, int* meanX, int* meanY, int* numOfPoints)
{
	/**meanX = startX;
	*meanY = startY;
	*numOfPoints = 1;
	map->tiles[startY*map->width + startX].type = TileType::Water;
	img->setPixel(startX, startY, replaceColor);

	for (int deltaY = -1; deltaY <= 1; deltaY++)
	{
		int neighbourY = startY + deltaY;
		if (neighbourY < 0 || neighbourY >= map->height) continue;

		for (int deltaX = -1; deltaX <= 1; deltaX++)
		{
			int neighbourX = startX + deltaX;
			if (neighbourX < 0 || neighbourX >= map->width) continue;

			Color col = img->getPixel(neighbourX, neighbourY);
			if (col != findColor) continue;

			int meanFromNeighbourX = 0;
			int meanFromNeighbourY = 0;
			int numOfPointsFromNeighbour = 0;
			findMeanOfConnectedRegion(map, img, neighbourX, neighbourY, findColor, replaceColor, &meanFromNeighbourX, &meanFromNeighbourY, &numOfPointsFromNeighbour);

			*meanX = ((*meanX)*(*numOfPoints) + meanFromNeighbourX*numOfPointsFromNeighbour) / (*numOfPoints + numOfPointsFromNeighbour);
			*meanY = ((*meanY)*(*numOfPoints) + meanFromNeighbourY*numOfPointsFromNeighbour) / (*numOfPoints + numOfPointsFromNeighbour);
			*numOfPoints += numOfPointsFromNeighbour;
		}
	}*/
	list<Vector2i> fifoList;
	
	fifoList.push_front(Vector2i(startX, startY));
	map->getTile(startX,startY)->type = TileType::Water;
	img->setPixel(startX, startY, replaceColor);
	
	Vector2f mean = Vector2f(0, 0);
	int numberOfPoints = 0;

	while(!fifoList.empty())
	{
		Vector2i point = fifoList.back(); fifoList.pop_back();
		mean = ((float)numberOfPoints * mean + (Vector2f)point) / (float)(numberOfPoints + 1);
		numberOfPoints++;
		

		for (int deltaY = -1; deltaY <= 1; deltaY++)
		{
			int neighbourY = point.y + deltaY;
			if (neighbourY < 0 || neighbourY >= map->height) continue;

			for (int deltaX = -1; deltaX <= 1; deltaX++)
			{
				int neighbourX = point.x + deltaX;
				if (neighbourX < 0 || neighbourX >= map->width) continue;

				Color col = img->getPixel(neighbourX, neighbourY);
				if (col != findColor) continue;

				fifoList.push_front(Vector2i(neighbourX, neighbourY));
				map->getTile(neighbourX,neighbourY)->type = TileType::Water;
				img->setPixel(neighbourX, neighbourY, replaceColor);
			}
		}
	}

	*meanX = (int)mean.x;
	*meanY = (int)mean.y;
	*numOfPoints = numberOfPoints;
}

Vector2i Map::getSize()
{
	return Vector2i(width, height);
}

Map::~Map()
{
	free(tiles);
}

#include "InformationProvider.h"
#include "Game.h"
#include "Constants.h"
#include "VectorOps.h"
#include <list>

using namespace sf;

void InformationProvider::create(Game* game, Raft* raft)
{
	this->game = game;
	this->raft = raft;
}

Vector2f InformationProvider::getRaftPosition()
{
	return raft->getPosition();
}

Vector2f InformationProvider::getRaftVelocity()
{
	return raft->getVelocity();
}

int InformationProvider::getNumberOfCapturedFish()
{
	return raft->getNumberOfFish();
}

int InformationProvider::getRaftHealth()
{
	return raft->getHealth();
}

float InformationProvider::getRemainingGameTime()
{
	return game->remainingTime;
}

int InformationProvider::getMapWidth()
{
	return game->map.getSize().x;
}

int InformationProvider::getMapHeight()
{
	return game->map.getSize().y;
}

char InformationProvider::requestMapPoint(Vector2i point)
{
	if (point.x < 0 || point.x >= game->map.getSize().x || point.y < 0 || point.y >= game->map.getSize().y) return 0;
	if (game->map.getTile(point.x, point.y)->hasFish) return 'F';

	switch (game->map.getTile(point.x, point.y)->type)
	{
	case TileType::Land: return 'L';
	case TileType::Water: return 'W';
	default:
		return 0;
	}
}

int InformationProvider::getAllVisibleFishPositions(sf::Vector2i* positionsArray)
{
	int count = 0;
	for (list<Vector2i>::iterator it = game->map.fishLocations.begin(); it != game->map.fishLocations.end(); it++)
	{
		Vector2i fishPosition = *it;
		if (pointFallsInRaftVisibleRegion(fishPosition))
		{
			positionsArray[count] = fishPosition;
			count++;
		}
	}
	return count;
}

int InformationProvider::getAllVisibleOpponentCannonBallPositions(sf::Vector2f* positionsArray)
{
	int count = 0;
	CannonBallList* cbl = game->cannonBallsManager.registeredCannonBalls;
	while (cbl != NULL)
	{
		Vector2f cannonBallPosition = cbl->cannonBall.position;
		if (pointFallsInRaftVisibleRegion(cannonBallPosition))
		{
			positionsArray[count] = cannonBallPosition;
			count++;
		}
	}
	return count;
}

sf::Vector2f InformationProvider::getOpponentRaftPosition()
{
	Raft* opponentRaft = (raft == &(game->raft1) ? &(game->raft2) : &(game->raft1));
	if (pointFallsInRaftVisibleRegion(opponentRaft->getPosition()))
	{
		return opponentRaft->getPosition();
	}
	else
	{
		return Vector2f(-1.0f, -1.0f);
	}
}

bool InformationProvider::pointFallsInRaftVisibleRegion(sf::Vector2f point)
{
	return VectorOps::MagnitudeSquared(point - raft->getPosition()) <= RAFT_VISIBILITY_RADIUS * RAFT_VISIBILITY_RADIUS;
}

bool InformationProvider::pointFallsInRaftVisibleRegion(sf::Vector2i point)
{
	return pointFallsInRaftVisibleRegion((Vector2f)point);
}

void InformationProvider::getApplicationStartupPath(char path[])
{
	game->getStartupPath(path);
}
#pragma once
#include <SFML\Graphics.hpp>

class Game;
class Raft;

class InformationProvider
{
	Game* game;
	Raft* raft;

public:

	//for passing the game's and the player'r raft's reference, from which this object can extract information.
	//IT IS FOR THE GAME'S INTERNAL PURPOSES AND IT SHOULD NOT TO BE CALLED BY THE PLAYER.
	void create(Game* game, Raft* raft);

	//Returns global position of the player's raft. Screen's top left is (0,0). Bottom right is (mapWidth, mapHeight).
	sf::Vector2f getRaftPosition();

	//Returns velocity of the player's raft
	sf::Vector2f getRaftVelocity();

	//Returns number of fish the player has captured so for
	int getNumberOfCapturedFish();

	//Returns current health of the player's raft on a scale of 0 to 100. 100 = Full health.
	int getRaftHealth();

	//Returns the remaining game time in seconds.
	float getRemainingGameTime();

	//Returns the map's width
	int getMapWidth();

	//Returns the map's height
	int getMapHeight();

	//returns what is on the map at the point passed (in global coordinates) as argument.
	//returns 'W' if it is a water point.
	//returns 'L' if it is a land point.
	//returns 'F' if there is a fish at that point. i.e. if the passed parameter equals center point of the fish.
	//returns '\0' (= 0 = zero = NULL) if the requested point does not fall within the raft's visibility region or it is
	//an invalid point.
	char requestMapPoint(sf::Vector2i point);

	//This method copies positions of all fish, which fall within the raft's visibility region, into the passed array.
	//The passed array should be of sufficient size
	//Return value = number of fish found within the visibility region.
	int getAllVisibleFishPositions(sf::Vector2i* positionsArray);

	//This method copies positions of all cannon balls, which were fired at you and 
	//which fall within the raft's visibility region, into the passed array.
	//The passed array should be of sufficient size
	//Return value = number of such cannon balls.
	int getAllVisibleOpponentCannonBallPositions(sf::Vector2f* positionsArray);

	//Returns the position of opponent raft if it happens to fall within the player's raft's visibility radius.
	//Returns (-1, -1) otherwise.
	sf::Vector2f getOpponentRaftPosition();

	//A utility function to determine whether the point passed in the argument falls within the raft's visibility region
	bool pointFallsInRaftVisibleRegion(sf::Vector2f point);

	//A utility function to determine whether the point passed in the argument falls within the raft's visibility region
	bool pointFallsInRaftVisibleRegion(sf::Vector2i point);

	//Can be used to obtain the absolute path of the folder from which the executable was started. The last backslah is included.
	//Make sure to pass a big enough array.
	void getApplicationStartupPath(char path[]);
};


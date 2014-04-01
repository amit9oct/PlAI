#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Map;
class Raft;
class Game;

struct CannonBall
{
	sf::Vector2f position;
	sf::Vector2f direction;
	Raft* ownerRaft;
};

bool operator ==(const CannonBall& left, const CannonBall& right);

struct CannonBallList
{
	CannonBallList* up;
	CannonBallList* down;
	CannonBall cannonBall;

	static CannonBallList* push(CannonBallList* cbl, CannonBall cb);
	static CannonBallList* deleteNode(CannonBallList* cbl);

};

class CannonBallsManager
{
	Game* game;

public:

	CannonBallList* registeredCannonBalls;

	void create(Game* game);
	void initialise();
	void RegisterCannonBall(CannonBall cannonBall);
	void update(sf::Time elapsedTime);
};


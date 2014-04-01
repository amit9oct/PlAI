#pragma once
#include "Constants.h"
#include <SFML\Graphics.hpp>

class Game;

struct RaftControls
{
	sf::Vector2f thrust;
	bool brake;
	sf::Vector2f canonDirection;
	RaftControls();
	RaftControls(sf::Vector2f thrust, bool brake, sf::Vector2f canonDirection);
};

class Raft
{

private:

	Game* game;
	Raft* opponentRaft;
	
	sf::Vector2f position;
	sf::Vector2f velocity;
	int health;
	int fishCount;

	sf::Vector2f previousPosition;
	sf::Clock lastCannonBallFiredAt;

	sf::Vector2f collisionPoints[RAFT_NUMBER_OF_COLLISION_POINTS];

	void resolveCollisions();
	void catchFish();
	void fireCannonBall(sf::Vector2f direction);
	void validateControls();
	sf::Vector2f getCollisionPoint(int i);

public:
	RaftControls controls;

	float remainingTimeAtWhichLastFishCollected;

	void create(Game* game, Raft* opponentRaft);
	void initialise(sf::Vector2f spawnPosition);
	void update(sf::Time elapsedTime);
	
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	int getNumberOfFish();
	int getHealth();

	void faceDamage(int damage);
};
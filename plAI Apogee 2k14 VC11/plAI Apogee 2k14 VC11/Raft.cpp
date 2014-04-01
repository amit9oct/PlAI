#include <SFML\Graphics.hpp>
#include "Raft.h"
#include "VectorOps.h"
#include "Map.h"
#include "Game.h"

using namespace sf;

RaftControls::RaftControls(sf::Vector2f thrust, bool brake, sf::Vector2f canonDirection)
{
	this->thrust = thrust;
	this->brake = brake;
	this->canonDirection = canonDirection;
}

RaftControls::RaftControls()
{
	this->thrust = Vector2f(0, 0);
	this->brake = false;
	this->canonDirection = Vector2f(0, 0);
}

void Raft::create(Game* game, Raft* opponent)
{
	this->game = game;
	this->opponentRaft = opponent;
}

void Raft::initialise(Vector2f spawnPosition)
{
	this->velocity = Vector2f(0,0);
	this->position = spawnPosition;
	this->health = RAFT_MAX_HEALTH;
	this->fishCount = 0;
	this->previousPosition = this->position;
	this->controls = RaftControls(Vector2f(0, 0), false, Vector2f(0, 0));
	this->lastCannonBallFiredAt.restart();
	this->remainingTimeAtWhichLastFishCollected = game->remainingTime;

	for (int i = 0; i < RAFT_NUMBER_OF_COLLISION_POINTS; i++)
	{
		collisionPoints[i] = (float)RAFT_RADIUS * VectorOps::RotateAnticlockwise(Vector2f(0,-1), i*(2 * PI / RAFT_NUMBER_OF_COLLISION_POINTS));
	}
}

void Raft::update(Time elapsedTime)
{
	float dt = elapsedTime.asSeconds();

	validateControls();

	int brake = controls.brake ? 1 : 0;
	Vector2f totalForce = RAFT_ENGINE_FORCE * controls.thrust - (RAFT_DRAG_REGULAR + brake * RAFT_DRAG_BRAKE) * VectorOps::Magnitude(velocity) * velocity;

	velocity += totalForce*dt / RAFT_MASS;

	//stopping condition:
	if (controls.thrust.x == 0 && controls.thrust.y == 0 && VectorOps::Magnitude(velocity) < 12) velocity = Vector2f(0,0);

	previousPosition = position;
	position += velocity * dt;

	resolveCollisions();
	if(health==0)
	{
		position=Vector2f(-1000,-1000);
		return;
	}

	catchFish();

	if (controls.canonDirection != Vector2f(0, 0) && lastCannonBallFiredAt.getElapsedTime().asSeconds() > CANNONBALL_FIRE_MIN_LAG) 
	{
		fireCannonBall(controls.canonDirection);
		lastCannonBallFiredAt.restart();
	}
}

Vector2f Raft::getPosition()
{
	return position;
}

Vector2f Raft::getVelocity()
{
	return velocity;
}

int Raft::getNumberOfFish()
{
	return fishCount;
}

int Raft::getHealth()
{
	return health;
}

void Raft::faceDamage(int damage)
{
	if(health <= 0) return;
	health -= damage;
	if(health <= 0) 
	{
		health = 0;
		position = Vector2f(-1000,-1000);
	}
}

void Raft::resolveCollisions()
{
	int collidedPoints = 0;
	Vector2f meanOfCollidedPoints = Vector2f(0,0);
	for (int i = 0; i < RAFT_NUMBER_OF_COLLISION_POINTS; i++)
	{
		Vector2f pt = getCollisionPoint(i);
		if (pt.x < 0 || pt.x >= game->map.getSize().x ||
			pt.y < 0 || pt.y >= game->map.getSize().y ||
			game->map.getTile((int)pt.x, (int)pt.y)->type == TileType::Land)
		{
			collidedPoints++;
			meanOfCollidedPoints = ((float)(collidedPoints - 1)*meanOfCollidedPoints + pt) / (float)collidedPoints;
		}
	}

	if (collidedPoints>0)
	{
		Vector2f impulseDir = VectorOps::Normalise(position - meanOfCollidedPoints);
		Vector2f unAffectedDir = VectorOps::RotateAnticlockwise(impulseDir, PI / 2);
		float unAffectedDirSpeedCompo = VectorOps::Dot(velocity, unAffectedDir);
		float unAffectedDirPosiCompo = VectorOps::Dot(position, unAffectedDir);
		float affectedSpeedComp = VectorOps::Dot(velocity, -impulseDir);
		float oldPosiAlongAffectedDir = VectorOps::Dot(previousPosition, -impulseDir);
		if (affectedSpeedComp > 0)
		{
			game->gameSounds.playLandCollisionSound = true;
			faceDamage((int)affectedSpeedComp / 10);
			affectedSpeedComp *= RAFT_COEFF_RESTITUTION;
			velocity = unAffectedDirSpeedCompo*unAffectedDir + affectedSpeedComp*impulseDir;
			position = unAffectedDirPosiCompo*unAffectedDir - oldPosiAlongAffectedDir*impulseDir;
		}
	}

	//all analysis from frame of this raft:
	Vector2f seperationVector = this->position - opponentRaft->position;
	if (VectorOps::MagnitudeSquared(seperationVector) <= 4 * RAFT_RADIUS*RAFT_RADIUS &&
		VectorOps::Dot(opponentRaft->velocity - this->velocity, seperationVector) > 0)
	{
		game->gameSounds.playInterRaftCollisionSound = true;

		Vector2f v1 = this->velocity;
		Vector2f v2 = opponentRaft->velocity;
		Vector2f v = opponentRaft->velocity - this->velocity;
		
		Vector2f impulseDir = VectorOps::Normalise(seperationVector);
		Vector2f unAffectedDir = VectorOps::RotateAnticlockwise(impulseDir, PI / 2);

		Vector2f v_dash = (-RAFT_COEFF_RESTITUTION * VectorOps::Dot(v, impulseDir)) * impulseDir + (VectorOps::Dot(v, unAffectedDir))* unAffectedDir;

		this->velocity = (this->velocity + opponentRaft->velocity - v_dash) / 2.0f;
		opponentRaft->velocity = (this->velocity + opponentRaft->velocity + v_dash) / 2.0f;

		float approachVelocity = VectorOps::Dot(v, impulseDir);
		float unAffectedDirPosiCompo = VectorOps::Dot(this->position, unAffectedDir);
		float oldPosiAlongAffectedDir = VectorOps::Dot(previousPosition, -impulseDir);
		position = unAffectedDirPosiCompo * unAffectedDir - oldPosiAlongAffectedDir * impulseDir;

		this->faceDamage((int)approachVelocity / 10);
		opponentRaft->faceDamage((int)approachVelocity / 10);
	}

}

void Raft::catchFish()
{
	for (std::list<Vector2i>::iterator it = game->map.fishLocations.begin(); it != game->map.fishLocations.end(); it++)
	{
		float xDist = it->x - position.x;
		float yDist = it->y - position.y;
		if (xDist * xDist + yDist * yDist <= (RAFT_RADIUS + FISH_PRESENSE_RADIUS) *(RAFT_RADIUS + FISH_PRESENSE_RADIUS))
		{
			//fish caught
			game->map.tryCatchFish(it->x, it->y);
			fishCount++;
			remainingTimeAtWhichLastFishCollected = game->remainingTime;
			game->gameSounds.playFishCollectSound = true;
			break;
		}
	}
}

void Raft::fireCannonBall(Vector2f direction)
{
	CannonBall cb;
	cb.position = position;
	cb.direction = direction;
	cb.ownerRaft = this;
	game->cannonBallsManager.RegisterCannonBall(cb);
	game->gameSounds.playCannonBallFireSound = true;
}

void Raft::validateControls()
{
	if (VectorOps::MagnitudeSquared(controls.thrust) > 1) controls.thrust = VectorOps::Normalise(controls.thrust);
}

Vector2f Raft::getCollisionPoint(int i)
{
	return collisionPoints[i] + position;
}
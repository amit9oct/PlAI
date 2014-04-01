#include "CannonBallsManager.h"
#include "VectorOps.h"
#include "Constants.h"
#include "Map.h"
#include "Raft.h"
#include "Game.h"
#include <stdlib.h>

using namespace sf;
using namespace std;

bool operator ==(const CannonBall& left, const CannonBall& right)
{
	return left.position == right.position && left.direction == right.direction && left.ownerRaft == right.ownerRaft;
}

CannonBallList* CannonBallList::push(CannonBallList* cbl, CannonBall cb)
{
	CannonBallList* cblNew = (CannonBallList*)malloc(sizeof(CannonBallList));
	if (cblNew == NULL) return cbl;
	cblNew->cannonBall = cb;

	if (cbl != NULL) cbl->up = cblNew;
	cblNew->down = cbl;
	cblNew->up = NULL;
	cbl = cblNew;

	return cbl;
}

CannonBallList* CannonBallList::deleteNode(CannonBallList* cbl)
{
	if (cbl == NULL) return NULL;
	if(cbl->up!=NULL) cbl->up->down = cbl->down;
	if (cbl->down != NULL) cbl->down->up = cbl->up;
	CannonBallList* down = cbl->down;
	free(cbl);
	return down;
}

void CannonBallsManager::create(Game* game)
{
	this->game = game;
}

void CannonBallsManager::initialise()
{
	registeredCannonBalls = NULL;
}

void CannonBallsManager::RegisterCannonBall(CannonBall CannonBall)
{
	CannonBall.direction = VectorOps::Normalise(CannonBall.direction);
	registeredCannonBalls = CannonBallList::push(registeredCannonBalls, CannonBall);
}

void CannonBallsManager::update(Time elapsedTime)
{
	CannonBallList* cbl = registeredCannonBalls;
	while (cbl!=NULL)
	{
		
		cbl->cannonBall.position = cbl->cannonBall.position + cbl->cannonBall.direction * (float)CANNON_BALL_SPEED * elapsedTime.asSeconds();

		bool cannonBallDestroyed = false;

		if (cbl->cannonBall.position.x < 0 || cbl->cannonBall.position.x >= game->map.getSize().x || cbl->cannonBall.position.y < 0 || cbl->cannonBall.position.y >= game->map.getSize().y)
		{
			//CannonBall went out of window
			cannonBallDestroyed = true;
		}
		else if (game->map.getTile((int)(cbl->cannonBall.position.x), (int)(cbl->cannonBall.position.y))->type == TileType::Land)
		{
			//The CannonBall has just struck land. It should be removed from the list
			cannonBallDestroyed = true;
		}
		else if (cbl->cannonBall.ownerRaft == &game->raft2 && VectorOps::MagnitudeSquared(cbl->cannonBall.position - game->raft1.getPosition()) <= RAFT_RADIUS * RAFT_RADIUS)
		{
			//The CannonBall has struck raft1.
			cannonBallDestroyed = true;
			game->raft1.faceDamage(CANNONBALL_DAMAGE);
			if (game->raft1.getHealth() == 0) cbl = NULL;
		}
		else if (cbl->cannonBall.ownerRaft == &game->raft1 && VectorOps::MagnitudeSquared(cbl->cannonBall.position - game->raft2.getPosition()) <= RAFT_RADIUS * RAFT_RADIUS)
		{
			//The CannonBall has struck raft2.
			cannonBallDestroyed = true;
			game->raft2.faceDamage(CANNONBALL_DAMAGE);
			if (game->raft2.getHealth() == 0) cbl = NULL;
		}

		if (cannonBallDestroyed)
		{
			game->gameSounds.playCannonBallStrikeSound = true;
			if (registeredCannonBalls == cbl) registeredCannonBalls = cbl = CannonBallList::deleteNode(cbl);
			else cbl = CannonBallList::deleteNode(cbl);
		}
		else
		{
			if (cbl != NULL) cbl = cbl->down;
		}
	}
}
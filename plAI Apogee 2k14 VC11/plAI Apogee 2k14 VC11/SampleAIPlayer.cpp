#include "SampleAIPlayer.h"
#include "VectorOps.h"
#include <SFML\Graphics.hpp>

using namespace sf;

void SampleAIPlayer::initialise(InformationProvider* info)
{

}

RaftControls SampleAIPlayer::controlRaft(InformationProvider* info)
{
	Vector2i fishLocs[50];
	int n = info->getAllVisibleFishPositions(fishLocs);
	bool foundFish = n > 0;

	Vector2f centre = info->getRaftPosition();
	RaftControls ctrl = RaftControls();
	
	//return ctrl; //DeComment this line to make this a dumb bot
	
	if (foundFish)
	{
		Vector2f fishLoc = (Vector2f)fishLocs[0];
		//run towards fish
		ctrl.thrust = 200.0f * VectorOps::Normalise(fishLoc - centre);

		//don't run towards fish if obstacle found
		if (obstacleExists(centre, fishLoc, info))
		{
			ctrl.thrust = VectorOps::RotateAnticlockwise(ctrl.thrust, PI / 2) / 2.0f;
		}
		ctrl.brake = false;

	}
	else
	{
		if (info->getRaftVelocity() != Vector2f(0, 0) && obstacleExists(centre, centre + (float)RAFT_VISIBILITY_RADIUS * VectorOps::Normalise(info->getRaftVelocity()) / 2.0f, info))
		{
			//avoid the obstacle.
			ctrl.thrust = 200.0f * VectorOps::Normalise(VectorOps::RotateAnticlockwise(info->getRaftVelocity(), -PI / 2));
			lastAcc = ctrl.thrust;
			c.restart();
			ctrl.brake = true;
		}
		else
		{
			
			if (c.getElapsedTime().asSeconds() < 1)
			{
				//try roam around aimlessly towards certain direction for 1 second
				ctrl.thrust = lastAcc;
			}
			else
			{
				//change direction after 1 second
				ctrl.thrust = 200.0f * VectorOps::Normalise((Vector2f)Vector2i(rand() % 100 - 50, rand() % 200 - 100));
				lastAcc = ctrl.thrust;
				c.restart();
			}
			ctrl.brake = false;
		}
	}
	
	Vector2f opponent;
	if((opponent = info->getOpponentRaftPosition()).x > 0)
	{
		//fire a cannon in opposite bot's direction
		ctrl.canonDirection = opponent - info->getRaftPosition();

		//go after the enemy bot to attack, as well as add a perpendicular component to save itself from enemy bot.
		//'+=' is used so that the bot largely continues to do whatever it was doing (Coeff of 200 was used to initialy set thrust, now 50 is being used)
		ctrl.thrust += 50.0f*(opponent - info->getRaftPosition()) + 50.0f*VectorOps::RotateAnticlockwise((opponent - info->getRaftPosition()), -PI/2);
	}
	else
	{
		ctrl.canonDirection = Vector2f(0, 0);
	}
	return ctrl;
}

bool SampleAIPlayer::obstacleExists(sf::Vector2f p1, sf::Vector2f p2, InformationProvider* info)
{
	//a simple divide and conquer procedure:

	if (abs(((Vector2i)p1).x - ((Vector2i)p2).x) <= 1 && abs(((Vector2i)p1).y - ((Vector2i)p2).y) <= 1)
	{
		return info->requestMapPoint((Vector2i)p1)=='L' || info->requestMapPoint((Vector2i)p2) == 'L';
	}
	return obstacleExists(p1, (p1 + p2) / 2.0f, info) || obstacleExists(p2, (p1 + p2) / 2.0f, info);
}

void SampleAIPlayer::getTeamName(char teamName[])
{
	strcpy_s(teamName, 256, "Sample AI Bot");
}
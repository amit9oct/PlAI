#include "HumanPlayerWASD.h"
#include "VectorOps.h"

using namespace sf;

void HumanPlayerWASD::initialise(InformationProvider* info)
{

}

RaftControls HumanPlayerWASD::controlRaft(InformationProvider* info)
{
	Vector2f canon;
	Vector2f opp_position;
	opp_position=info->getOpponentRaftPosition();
	if(opp_position.x!=-1 &&opp_position.y!=-1)
	{
		canon.x=opp_position.x-(info->getRaftPosition()).x;
		canon.y=opp_position.y-(info->getRaftPosition()).y;

	}
	else 
	{
		canon.x=rand();
		canon.y=rand();
	}


	Vector2f b;
	bool brake=false;
	Vector2i allFishLocations[10];
	int numnFish=info->getAllVisibleFishPositions(allFishLocations);
	if(numnFish==0)
	{
	RaftControls controls;

	Vector2f a = Vector2f(0,0);
	if (Keyboard::isKeyPressed(Keyboard::W)) a.y = -1;
	if (Keyboard::isKeyPressed(Keyboard::S)) a.y += 1;
	if (Keyboard::isKeyPressed(Keyboard::A)) a.x = -1;
	if (Keyboard::isKeyPressed(Keyboard::D)) a.x += 1;
	if (Keyboard::isKeyPressed(Keyboard::LControl)) controls.brake = true; else
	{
		controls.brake = false;
	}
	controls.thrust = a;

	if(Keyboard::isKeyPressed(Keyboard::Space))
	{
		controls.canonDirection = (Vector2f)Vector2i(rand(), rand());
	}
	else
	{
		controls.canonDirection = canon;
	}
	return controls;
	}
	else
	{
		Vector2f curr_velocity=info->getRaftVelocity();
		brake=true;
		if(curr_velocity.x<=1000 && curr_velocity.y<=1000)
		{
			brake=false;
			b.x=(allFishLocations[0].x-((info->getRaftPosition()).x))*1000.0f;
			b.y=(allFishLocations[0].y-((info->getRaftPosition()).y))*1000.0f;

		}
		else
		{
			b.x=0;
			b.y=0;
		}
		if (obstacleExists(info->getRaftPosition(),(Vector2f) allFishLocations[0], info))
		{
			b = VectorOps::RotateAnticlockwise(b, PI / 2) / 2.0f;
		}
		brake = false;
		return RaftControls(b, brake, Vector2f(0, 0));
	}
}

void HumanPlayerWASD::getTeamName(char teamName[])
{
	strcpy_s(teamName, 256, "Manual Player");
}


bool  HumanPlayerWASD::obstacleExists(sf::Vector2f p1, sf::Vector2f p2, InformationProvider* info)
{
	//a simple divide and conquer procedure:
	if (abs(((Vector2i)p1).x - ((Vector2i)p2).x) <= 1 && abs(((Vector2i)p1).y - ((Vector2i)p2).y) <= 1)
	{
		return info->requestMapPoint((Vector2i)p1)=='L' || info->requestMapPoint((Vector2i)p2) == 'L';
	}
	return obstacleExists(p1, (p1 + p2) / 2.0f, info) || obstacleExists(p2, (p1 + p2) / 2.0f, info);
}
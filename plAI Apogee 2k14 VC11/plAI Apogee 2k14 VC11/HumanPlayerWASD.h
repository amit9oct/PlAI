#pragma once
#include "Player.h"

class HumanPlayerWASD : public Player
{
public:
	void initialise(InformationProvider* info);
	RaftControls controlRaft(InformationProvider* info);
	void getTeamName(char teamName[]);
	bool obstacleExists(sf::Vector2f currentLoc,sf::Vector2f finalLoc,InformationProvider *info);
};


#pragma once
#include "Player.h"

class SampleAIPlayer : public Player
{
public:
	int times;
	sf::Clock c;
	int maxTimes;
	sf::Vector2f lastAcc;
	void initialise(InformationProvider* info);
	bool obstacleExists(sf::Vector2f p1, sf::Vector2f p2, InformationProvider* info);
	RaftControls controlRaft(InformationProvider* info);
	void getTeamName(char teamName[]);
	
};


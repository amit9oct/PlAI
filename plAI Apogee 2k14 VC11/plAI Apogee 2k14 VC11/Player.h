#pragma once
#include "Constants.h"
#include "Raft.h"
#include "InformationProvider.h"

class InformationProvider;

class Player
{
public:
	
	//Use this method to initialise data structures
	virtual void initialise(InformationProvider* informationProvider) = 0;

	//Use this method to control the raft
	virtual RaftControls controlRaft(InformationProvider* informationProvider) = 0;

	//This method should populate the passed argument with the team's name
	virtual void getTeamName(char teamName[]) = 0;
};
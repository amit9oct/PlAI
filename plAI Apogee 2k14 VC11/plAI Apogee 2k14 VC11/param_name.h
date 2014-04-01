#pragma once
#include"Player.h"
#include <math.h>
#include <fstream>
#define FISHLOCATION_MAX_BLACKLIST_TIME 15
#define NUMBER_OF_FISHES 21
#define OBSTACLEMAN_TIME_THRESHOLD 20
#define OBSTACLEMAN_MAX_ANGLE (PI/20.0f)
#define OBSTACLEMAN_COS_ERROR 0.97
#define DEFAULT_LHMCountdown 0
#define NULL_POS Vector2f(-1,-1)
#define ENEMY_PURSUIT_RADIUS (RAFT_RADIUS+RAFT_RADIUS+15)
#define SAFETY_THRESHOLD (RAFT_RADIUS+45)
struct param_name_MotorControls{
	bool brakeApplied;
	sf::Vector2f thrustVector;
};
struct param_name_FishLocation{
	bool caught;
	bool blackListed;
	float blackListTime;
	sf::Vector2i location;
};
class param_name_cannon{
	int timeCheck;
	sf::Vector2f prevVelocity;
	sf::Vector2f prevPosition;
	sf::Vector2f lastSeenPosition;
	sf::Vector2f cannonDirection;
	bool seenOnce;
	bool entered,onTime;
	static int gameCounter;
	int timeDelay;
public:
	sf::Vector2f opponentVelocityVector(sf::Vector2f , InformationProvider *info );
	sf::Vector2f cannonVector(InformationProvider *info );
	std::fstream inputFile;
	param_name_cannon() { timeDelay = (int)(CANNONBALL_FIRE_MIN_LAG*GAME_DESIRED_UPDATE_FPS);
		timeCheck=0; prevVelocity=sf::Vector2f(0,0); onTime=entered=seenOnce=false;}
};
class param_name_obstacleMan{
    static int LHMCountdown;
	static float MIN_PING_DIST;
	static bool hugsLand; // true means Land Hugging on, is equivalent to Mode
	int startTime;//should be initialized before the new postionis fixed
	int direction ;// takes 1,-1 depending on the relative value w.r.t last position
	static float OBSTACLEMAN_DISP_ANGLE;
	sf::Vector2f lastPointChecked;
public:
	void setStartTime(int t);
	sf::Vector2f getObstacleManPosition(sf::Vector2f,InformationProvider *info);
	sf::Vector2f getNextPingPoint(sf::Vector2f v,int n);
	int randDirFixer();
	float randAngleGen();
	sf::Vector2f dispChange(InformationProvider *info);
	void resetMode(InformationProvider *info);
};
class param_name_explorer
{
	sf::Vector2f queue[8];
	int check[8];
public:
	int gameCounter;
	sf::Vector2f explorePoint(InformationProvider *info);
	int chooseLocation(InformationProvider *info);
	void chooseQueueOrder(InformationProvider *info);
	void blacklistExplore(InformationProvider *info, sf::Vector2f);
	std::fstream inputFile;
	param_name_explorer()
	{
		gameCounter=0;
		for(int i=0;i<6;i++) check[i]=0;
	}
};
class param_name : public Player
{
private:
	//Declare your data structures here
	param_name_explorer explore;
	param_name_obstacleMan obstacle;
	param_name_cannon cannonFire;
	param_name_MotorControls movementControls;
	param_name_FishLocation fish[NUMBER_OF_FISHES];
public:
	void initialise(InformationProvider* info);
	RaftControls controlRaft(InformationProvider* info);
	void getTeamName(char teamName[]);
	void motorFunction(sf::Vector2f rFinal,InformationProvider *info, bool needWarpSpeed);
	void updateDatabase(InformationProvider *info);
	int decisionMaker(InformationProvider *info);
	sf::Vector2f catchFish(InformationProvider *info);
	sf::Vector2f hide(InformationProvider *info);
	sf::Vector2f enemyPursuit(InformationProvider *info);
	sf::Vector2f flee(InformationProvider *info);
	bool canFish();
};
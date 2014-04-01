#pragma once
#include "AnimatedSprite.h"
#include "Constants.h"
#include "Map.h"
#include "Raft.h"
#include PLAYER1_HEADER_FILE
#include PLAYER2_HEADER_FILE
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include "CannonBallsManager.h"
#include "GameGraphics.h"
#include "GameSounds.h"
#include "InformationProvider.h"

using namespace sf;
using namespace std;

enum GameState
{
	Welcome = 0, Playing, Paused, GameOver
};

class Game
{
	char mapName[1024];
	char startupPath[1024];

	char player1WinningText[512];
	char player2WinningText[512];
	char versusText[1024];

	void initialise();
	void loadContent();
	void update(sf::Time elTime);
	void draw(sf::Time elapsedTime);
	void playSounds();

	void handleWindowEvents();
public:

	RenderWindow window;
	Map map;
	Raft raft1;
	Raft raft2;
	PLAYER1_CLASS_NAME player1;
	PLAYER2_CLASS_NAME player2;
	InformationProvider infoProvider1;
	InformationProvider infoProvider2;
	CannonBallsManager cannonBallsManager;
	GameGraphics gameGraphics;
	GameSounds gameSounds;

	int gettingFPS;
	float remainingTime;
	GameState gameState;

	Game(char* startupPath ,char* mapName);
	void start();

	void getStartupPath(char buffer[]);
	
};


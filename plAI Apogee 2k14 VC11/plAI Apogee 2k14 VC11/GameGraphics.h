#pragma once
#include <SFML\Graphics.hpp>
#include "Constants.h"
#include "AnimatedSprite.h"

class Game;

class GameGraphics
{
private:

	Game* game;
	sf::Font mainFont;

	char bigStatus[2048];
	char smallStatus[2048];

	//grass:
	sf::Texture grassTexture;
	sf::Sprite grassSprite;
	void loadGrassGraphics();
	void drawGrassGraphics(sf::Time elapsedTime);

	//raft1:
	sf::Texture raft1Texture;
	sf::Sprite raft1Sprite;
	sf::CircleShape raft1VisibilityCircle;
	sf::RectangleShape raft1LifeBar;
	sf::RectangleShape raft1LifeBarOutline;
	void loadRaft1Graphics();
	void drawRaft1Grpahics(sf::Time elapsedTime);

	//raft2:
	sf::Texture raft2Texture;
	sf::Sprite raft2Sprite;
	sf::CircleShape raft2VisibilityCircle;
	sf::RectangleShape raft2LifeBar;
	sf::RectangleShape raft2LifeBarOutline;
	void loadRaft2Graphics();
	void drawRaft2Graphics(sf::Time elapsedTime);

	//fish:
	AnimatedSprite presetFishSprites[NUMBER_OF_PRESET_FISH_SPRITES];
	AnimatedSprite fishSprites[100];
	void loadFishGrpahics();
	void drawFishGraphics(sf::Time elapsedTime);

	//water:
	struct WaterPoint{ float height; float velocity; };
	sf::Image waterImage;
	sf::Texture waterTexture;
	sf::Sprite waterSprite;
	bool waterSourceSelector;
	sf::Vector2i currentRandomWaterDisturbancePoint;
	WaterPoint waterPoints1[RIPPLEMAP_WIDTH * RIPPLEMAP_HEIGHT];
	WaterPoint waterPoints2[RIPPLEMAP_WIDTH * RIPPLEMAP_HEIGHT];
	sf::Clock randomDisturbanceClock;
	void loadWaterGraphics();
	void initialiseWater();
	void updateWaterGraphics(sf::Time elapsedTime);
	void drawWaterGraphics(sf::Time elapsedTime);

	//logo:
	sf::RectangleShape informationBar;
	sf::Texture ieeeLogoTexture;
	sf::Texture bitsLogoTexture;
	sf::Texture apogeeLogoTexture;
	sf::Sprite ieeeLogoSprite;
	sf::Sprite bitsLogoSprite;
	sf::Sprite apogeeLogoSprite;
	void loadLogoGrpahics();
	void drawLogoGraphics(sf::Time elapsedTime);

	//statusDrawing:
	void drawBigStatus(sf::Time elapsedTime);
	void drawSmallStatus(sf::Time elapsedTime);

	//cannonBalls drawing:
	void drawCannonBalls(sf::Time elapsedTime);

	//scores:
	sf::Text remainingTimeText;
	sf::Text player1NameText;
	sf::Text player2NameText;
	sf::Text player1ScoreText;
	sf::Text player2ScoreText;
	sf::Text timeText;
	sf::RectangleShape timePlayerSperatorBar;
	sf::RectangleShape playerScoresSeperatorBar;
	void loadScoresGraphics();
	void drawScoresGraphics(sf::Time elapsedTime);

public:

	void create(Game* game);
	void load();
	void initialise();
	void update(sf::Time elapsedTime);
	void draw(sf::Time elapsedTime);
	void setBigStatus(char* status);
	void setSmallStatus(char* status);
};


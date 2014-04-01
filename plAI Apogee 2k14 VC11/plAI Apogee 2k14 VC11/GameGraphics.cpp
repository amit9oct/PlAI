#include "GameGraphics.h"
#include "Game.h"
#include "Map.h"
#include <math.h>
#include "CannonBallsManager.h"

using namespace sf;

void GameGraphics::loadGrassGraphics()
{
	Image grassImage;
	char grassFileName[1024]; game->getStartupPath(grassFileName); strcat_s(grassFileName, GRASS_TEXTURE_PATH);
	grassImage.loadFromFile(grassFileName);

	for (int y = 0; y < game->map.getSize().y; y++)
	{
		for (int x = 0; x < game->map.getSize().x; x++)
		{
			if (game->map.getTile(x,y)->type != TileType::Land)
			{
				grassImage.setPixel(x, y, Color::Transparent);
			}
		}
	}
	grassTexture.loadFromImage(grassImage, IntRect(0, 0, game->map.getSize().x, game->map.getSize().y));
	grassSprite.setTexture(grassTexture, true);
}

void GameGraphics::drawGrassGraphics(Time elapsedTime)
{
	game->window.draw(grassSprite);
}

void GameGraphics::loadRaft1Graphics()
{
	char raft1FileName[1024]; game->getStartupPath(raft1FileName); strcat_s(raft1FileName, RAFT1_TEXTURE_PATH);
	raft1Texture.loadFromFile(raft1FileName);
	raft1Sprite.setTexture(raft1Texture, true);
	raft1Sprite.setOrigin((float)raft1Texture.getSize().x / 2, (float)raft1Texture.getSize().y / 2);
	raft1Sprite.setScale((float)(2 * RAFT_RADIUS) / (float)raft1Texture.getSize().x, (float)(2 * RAFT_RADIUS) / (float)raft1Texture.getSize().y);
	
	raft1VisibilityCircle.setRadius(RAFT_VISIBILITY_RADIUS);
	raft1VisibilityCircle.setOrigin((float)RAFT_VISIBILITY_RADIUS, (float)RAFT_VISIBILITY_RADIUS);
	raft1VisibilityCircle.setFillColor(COLOR_VISIBILITY_REGION);

	raft1LifeBarOutline.setOutlineColor(Color::Black);
	raft1LifeBarOutline.setOutlineThickness(1);
	raft1LifeBarOutline.setFillColor(Color::Transparent);
	raft1LifeBarOutline.setSize(sf::Vector2f(2 * RAFT_RADIUS + 1, 2));
}

void GameGraphics::drawRaft1Grpahics(Time elapsedTime)
{
	raft1VisibilityCircle.setPosition(game->raft1.getPosition());

	raft1LifeBar.setSize(sf::Vector2f((float)((2 * RAFT_RADIUS + 1) * game->raft1.getHealth()) / 100, 2.0f));
	raft1LifeBar.setPosition(game->raft1.getPosition().x - RAFT_RADIUS, game->raft1.getPosition().y + RAFT_RADIUS + 4);
	raft1LifeBarOutline.setPosition(raft1LifeBar.getPosition());
	int g = 255 * game->raft1.getHealth() / 100;
	int r = 255 * (100 - game->raft1.getHealth()) / 100;
	int b = (int)(255 * sin(PI * game->raft1.getHealth() / 100.0f));
	raft1LifeBar.setFillColor(Color(r, g, b));

	raft1Sprite.setPosition(game->raft1.getPosition());

	game->window.draw(raft1VisibilityCircle);
	game->window.draw(raft1LifeBarOutline);
	game->window.draw(raft1LifeBar);
	game->window.draw(raft1Sprite);
}

void GameGraphics::loadRaft2Graphics()
{
	char raft2FileName[1024]; game->getStartupPath(raft2FileName); strcat_s(raft2FileName, RAFT2_TEXTURE_PATH);
	raft2Texture.loadFromFile(raft2FileName);
	raft2Sprite.setTexture(raft2Texture, true);
	raft2Sprite.setOrigin((float)raft2Texture.getSize().x / 2, (float)raft2Texture.getSize().y / 2);
	raft2Sprite.setScale((float)(2 * RAFT_RADIUS) / (float)raft2Texture.getSize().x, (float)(2 * RAFT_RADIUS) / (float)raft2Texture.getSize().y);

	raft2VisibilityCircle.setRadius(RAFT_VISIBILITY_RADIUS);
	raft2VisibilityCircle.setOrigin((float)RAFT_VISIBILITY_RADIUS, (float)RAFT_VISIBILITY_RADIUS);
	raft2VisibilityCircle.setFillColor(COLOR_VISIBILITY_REGION);

	raft2LifeBarOutline.setOutlineColor(Color::Black);
	raft2LifeBarOutline.setOutlineThickness(1);
	raft2LifeBarOutline.setFillColor(Color::Transparent);
	raft2LifeBarOutline.setSize(sf::Vector2f(2 * RAFT_RADIUS + 1, 2));
}

void GameGraphics::drawRaft2Graphics(Time elapsedTime)
{
	raft2VisibilityCircle.setPosition(game->raft2.getPosition());

	raft2LifeBar.setSize(sf::Vector2f((float)((2 * RAFT_RADIUS + 1) * game->raft2.getHealth()) / 100, 2));
	raft2LifeBar.setPosition(game->raft2.getPosition().x - RAFT_RADIUS, game->raft2.getPosition().y + RAFT_RADIUS + 4);
	raft2LifeBarOutline.setPosition(raft2LifeBar.getPosition());
	int g = 255 * game->raft2.getHealth() / 100;
	int r = 255 * (100 - game->raft2.getHealth()) / 100;
	int b = (int)(255 * sin(PI * game->raft2.getHealth() / 100.0f));
	raft2LifeBar.setFillColor(Color(r, g, b));

	raft2Sprite.setPosition(game->raft2.getPosition());

	game->window.draw(raft2VisibilityCircle);
	game->window.draw(raft2LifeBarOutline);
	game->window.draw(raft2LifeBar);
	game->window.draw(raft2Sprite);
}

void GameGraphics::loadFishGrpahics()
{
	char nameBuffer[1024];
	char startupPath[1024]; game->getStartupPath(startupPath);

	strcpy_s(nameBuffer, startupPath); strcat_s(nameBuffer, "Images\\fish\\bath 2.png");
	presetFishSprites[0].create(nameBuffer, 2, 1, 4);

	strcpy_s(nameBuffer, startupPath); strcat_s(nameBuffer, "Images\\fish\\cap 3.png");
	presetFishSprites[1].create(nameBuffer, 3, 1, 6);

	strcpy_s(nameBuffer, startupPath); strcat_s(nameBuffer, "Images\\fish\\crying 2.png");
	presetFishSprites[2].create(nameBuffer, 2, 1, 4);

	strcpy_s(nameBuffer, startupPath); strcat_s(nameBuffer, "Images\\fish\\dance 10.png");
	presetFishSprites[3].create(nameBuffer, 10, 1, 4);

	strcpy_s(nameBuffer, startupPath); strcat_s(nameBuffer, "Images\\fish\\dude 2.png");
	presetFishSprites[4].create(nameBuffer, 2, 1, 2);

	strcpy_s(nameBuffer, startupPath); strcat_s(nameBuffer, "Images\\fish\\oxygen 4.png");
	presetFishSprites[5].create(nameBuffer, 4, 1, 4);

	strcpy_s(nameBuffer, startupPath); strcat_s(nameBuffer, "Images\\fish\\shark 4.png");
	presetFishSprites[6].create(nameBuffer, 4, 1, 4);

	strcpy_s(nameBuffer, startupPath); strcat_s(nameBuffer, "Images\\fish\\tongue 2.png");
	presetFishSprites[7].create(nameBuffer, 2, 1, 2);

	strcpy_s(nameBuffer, startupPath); strcat_s(nameBuffer, "Images\\fish\\whale 32.png");
	presetFishSprites[8].create(nameBuffer, 32, 1, 5);

	int numOfFish = game->map.getInitialNumberOfFish();
	list<Vector2i>::iterator it = game->map.fishLocations.begin();

	for (int i = 0; i < numOfFish; i++)
	{
		fishSprites[i] = presetFishSprites[rand() % NUMBER_OF_PRESET_FISH_SPRITES];
		Sprite& sprite = fishSprites[i].getCurrentSprite();
		sprite.setOrigin((float)(sprite.getGlobalBounds().width) / 2, (float)(sprite.getGlobalBounds().height) / 2);
		sprite.setScale((float)(2 * FISH_WIDTH) / (float)(sprite.getGlobalBounds().width), (float)(2 * FISH_HEIGHT) / (float)(sprite.getGlobalBounds().height));
		int x = it->x; int y = it->y;
		sprite.setPosition((float)x, (float)y);
		it++;
	}
}

void GameGraphics::drawFishGraphics(Time elapsedTime)
{
	int numOfFish = game->map.getInitialNumberOfFish();
	for (int i = 0; i < numOfFish; i++)
	{
		Sprite sprite = fishSprites[i].getCurrentSprite();
		int x = (int)sprite.getPosition().x;
		int y = (int)sprite.getPosition().y;
		if (game->map.getTile(x, y)->hasFish)
		{
			game->window.draw(sprite);
		}
	}
}

void GameGraphics::loadWaterGraphics()
{
	waterImage.create(RIPPLEMAP_WIDTH, RIPPLEMAP_HEIGHT);
	waterTexture.loadFromImage(waterImage);
	waterSprite.setTexture(waterTexture);
	waterSprite.setScale((float)(game->map.getSize().x) / RIPPLEMAP_WIDTH, (float)(game->map.getSize().y) / RIPPLEMAP_HEIGHT);
}

void GameGraphics::initialiseWater()
{
	for (int y = 0; y < RIPPLEMAP_HEIGHT; y++)
	{
		for (int x = 0; x < RIPPLEMAP_WIDTH; x++)
		{
			int index = y * RIPPLEMAP_WIDTH + x;
			waterPoints1[index].height = waterPoints1[index].velocity = waterPoints2[index].height = waterPoints2[index].velocity = 0;
		}
	}
	randomDisturbanceClock.restart();
	currentRandomWaterDisturbancePoint = Vector2i(rand() % RIPPLEMAP_WIDTH, rand() % RIPPLEMAP_HEIGHT);
}

void GameGraphics::updateWaterGraphics(Time elapsedTime)
{
	WaterPoint* fromState = waterSourceSelector ? waterPoints1 : waterPoints2;
	WaterPoint* toState = waterSourceSelector ? waterPoints2 : waterPoints1;
	waterSourceSelector = !waterSourceSelector;

	if (randomDisturbanceClock.getElapsedTime().asSeconds()>0.05)
	{
		currentRandomWaterDisturbancePoint = Vector2i(rand() % RIPPLEMAP_WIDTH, rand() % RIPPLEMAP_HEIGHT);
		randomDisturbanceClock.restart();
	}

	Vector2i raft1InRippleMap = (Vector2i)Vector2f(game->raft1.getPosition().x*RIPPLEMAP_WIDTH / game->map.getSize().x, game->raft1.getPosition().y*RIPPLEMAP_HEIGHT / game->map.getSize().y);
	Vector2i raft2InRippleMap = (Vector2i)Vector2f(game->raft2.getPosition().x*RIPPLEMAP_WIDTH / game->map.getSize().x, game->raft2.getPosition().y*RIPPLEMAP_HEIGHT / game->map.getSize().y);

	for (int y = 0; y < RIPPLEMAP_HEIGHT; y++)
	{
		for (int x = 0; x < RIPPLEMAP_WIDTH; x++)
		{
			int mapX = x*game->map.getSize().x / RIPPLEMAP_WIDTH; int mapY = y*game->map.getSize().y / RIPPLEMAP_HEIGHT;
			int index = y*RIPPLEMAP_WIDTH + x;

			if (raft1InRippleMap == Vector2i(x, y) || raft2InRippleMap == Vector2i(x, y))
			{
				toState[index].height = -0.4f;
				toState[index].velocity = 0.0;
			}
			else if (game->map.getTile(mapX, mapY)->type == TileType::Land)
			{
				toState[index].height = toState[index].velocity = 0;
			}
			else if(Vector2i(x,y)==currentRandomWaterDisturbancePoint)
			{
				toState[index].height = 0.4f;
				toState[index].velocity = 0.0f;
			}
			else
			{
				float sum = 0;
				int neighbourCount = 0;
				for (int deltaY = -1; deltaY <= 1; deltaY++)
				{
					for (int deltaX = -1; deltaX <= 1; deltaX++)
					{
						int neighbourX = x + deltaX;
						int neighbourY = y + deltaY;
						int neighbour_mapPointX = neighbourX*game->map.getSize().x / RIPPLEMAP_WIDTH;
						int neighbour_mapPointY = neighbourY*game->map.getSize().y / RIPPLEMAP_HEIGHT;
						if (neighbourX < 0 || neighbourX >= RIPPLEMAP_WIDTH || neighbourY < 0 || neighbourY >= RIPPLEMAP_HEIGHT || (neighbourX == x && neighbourY == y)) continue;
						sum += fromState[neighbourY * RIPPLEMAP_WIDTH + neighbourX].height;
						neighbourCount++;
					}
				}

				float average = sum / (float)neighbourCount;
				float force = -150.0f*(fromState[index].height - average) - 0.13f*fromState[index].velocity;

				toState[index].velocity = fromState[index].velocity + force*elapsedTime.asSeconds();
				toState[index].height = fromState[index].height + toState[index].velocity*elapsedTime.asSeconds();
				/*if (toState[index].height > 1) toState[index].height = 1;
				if (toState[index].height<-1) toState[index].height = -1;*/
			}

			int max = 160;
			int val = (int)(max / 2 + toState[index].height*max / 2);
			if (val > max) val = max;
			if (val < 0) val = 0;
			waterImage.setPixel(x, y, Color((max - val) / 2, max - val, 255 - 150 * val / max, 255));
		}
	}
	waterTexture.loadFromImage(waterImage);
	waterSprite.setTexture(waterTexture);
}

void GameGraphics::drawWaterGraphics(sf::Time elapsedTime)
{
	game->window.draw(waterSprite);
}

void GameGraphics::loadLogoGrpahics()
{
	int padding = (INFO_BAR_HEIGHT - LOGO_HEIGHT) / 2;
	informationBar.setSize(Vector2f((float)(game->map.getSize().x), (float)INFO_BAR_HEIGHT));
	informationBar.setPosition(0, 0);
	informationBar.setFillColor(Color(0,0,0, 160));

	char ieeeLogoFileName[1024]; game->getStartupPath(ieeeLogoFileName); strcat_s(ieeeLogoFileName, IEEE_LOGO_PATH);
	ieeeLogoTexture.loadFromFile(ieeeLogoFileName);
	ieeeLogoSprite.setTexture(ieeeLogoTexture);
	ieeeLogoSprite.setScale((float)LOGO_HEIGHT / ieeeLogoTexture.getSize().y, (float)LOGO_HEIGHT / ieeeLogoTexture.getSize().y);
	ieeeLogoSprite.setPosition((float)padding, (float)padding);

	char bitsLogoFileName[1024]; game->getStartupPath(bitsLogoFileName); strcat_s(bitsLogoFileName, BITS_LOGO_PATH);
	bitsLogoTexture.loadFromFile(bitsLogoFileName);
	bitsLogoSprite.setTexture(bitsLogoTexture);
	bitsLogoSprite.setScale((float)LOGO_HEIGHT / bitsLogoTexture.getSize().y, (float)LOGO_HEIGHT / bitsLogoTexture.getSize().y);
	bitsLogoSprite.setPosition((float)(ieeeLogoSprite.getGlobalBounds().left + ieeeLogoSprite.getGlobalBounds().width + 10), (float)padding);

	char apogeeLogoFileName[1024]; game->getStartupPath(apogeeLogoFileName); strcat_s(apogeeLogoFileName, APOGEE_LOGO_PATH);
	apogeeLogoTexture.loadFromFile(apogeeLogoFileName);
	apogeeLogoSprite.setTexture(apogeeLogoTexture);
	apogeeLogoSprite.setScale((float)LOGO_HEIGHT / apogeeLogoTexture.getSize().y, (float)LOGO_HEIGHT / apogeeLogoTexture.getSize().y);
	apogeeLogoSprite.setPosition((float)(bitsLogoSprite.getGlobalBounds().left + bitsLogoSprite.getGlobalBounds().width + 15), (float)padding);
}

void GameGraphics::drawLogoGraphics(Time elapsedTime)
{
	game->window.draw(informationBar);
	game->window.draw(ieeeLogoSprite);
	game->window.draw(bitsLogoSprite);
	game->window.draw(apogeeLogoSprite);
}

void GameGraphics::drawBigStatus(Time elapsedTime)
{
	Text bigText(String(bigStatus), mainFont);
	bigText.setCharacterSize(40);
	bigText.setColor(Color::Black);
	sf::FloatRect localBounds = bigText.getLocalBounds();
	bigText.setPosition(game->map.getSize().x/2 - localBounds.width/2, game->map.getSize().y/2 - localBounds.height/2);
	bigText.setColor(Color::Black);
	game->window.draw(bigText);
}

void GameGraphics::drawSmallStatus(Time elapsedTime)
{
	Text smallText(String(smallStatus), mainFont);
	smallText.setCharacterSize(20);
	smallText.setColor(Color::Black);
	sf::FloatRect localBounds = smallText.getLocalBounds();
	smallText.setPosition(game->map.getSize().x - localBounds.width - 10, game->map.getSize().y - localBounds.height - 10);
	smallText.setColor(Color::Black);
	game->window.draw(smallText);
}

void GameGraphics::drawCannonBalls(Time elapsedTime)
{
	for (CannonBallList* cbl = game->cannonBallsManager.registeredCannonBalls; cbl != NULL; cbl=cbl->down)
	{
		CircleShape circle;
		circle.setRadius(CANNON_BALL_RADIUS);
		circle.setFillColor(Color::Yellow);
		circle.setOrigin(CANNON_BALL_RADIUS, CANNON_BALL_RADIUS);
		circle.setPosition(cbl->cannonBall.position);
		game->window.draw(circle);
	}
}

void GameGraphics::loadScoresGraphics()
{
	int padding = (INFO_BAR_HEIGHT - LOGO_HEIGHT) / 2;

	player2ScoreText.setFont(mainFont);
	player2ScoreText.setString("00");
	player2ScoreText.setCharacterSize(LOGO_HEIGHT);
	player2ScoreText.setColor(Color::White);
	player2ScoreText.setPosition((float)(game->map.getSize().x - player2ScoreText.getLocalBounds().width - padding), (float)padding);

	player2NameText.setFont(mainFont);
	char player2Name[100]; game->player2.getTeamName(player2Name); strcat_s(player2Name, ":");
	player2NameText.setString(player2Name);
	player2NameText.setCharacterSize(LOGO_HEIGHT);
	player2NameText.setColor(Color::White);
	player2NameText.setPosition((float)(player2ScoreText.getGlobalBounds().left - player2NameText.getLocalBounds().width - 10), (float)padding);

	playerScoresSeperatorBar.setSize(Vector2f(2, INFO_BAR_HEIGHT));
	playerScoresSeperatorBar.setPosition(player2NameText.getGlobalBounds().left - 20, 0);
	playerScoresSeperatorBar.setFillColor(Color(255,165,0));

	player1ScoreText.setFont(mainFont);
	player1ScoreText.setString("00");
	player1ScoreText.setCharacterSize(LOGO_HEIGHT);
	player1ScoreText.setColor(Color::White);
	player1ScoreText.setPosition((float)(playerScoresSeperatorBar.getGlobalBounds().left - player1ScoreText.getLocalBounds().width - padding), (float)padding);

	player1NameText.setFont(mainFont);
	char player1Name[100]; game->player1.getTeamName(player1Name); strcat_s(player1Name, ":");
	player1NameText.setString(player1Name);
	player1NameText.setCharacterSize(LOGO_HEIGHT);
	player1NameText.setColor(Color::White);
	player1NameText.setPosition((float)(player1ScoreText.getGlobalBounds().left - player1NameText.getLocalBounds().width - 10), (float)padding);

	timePlayerSperatorBar.setSize(Vector2f(4, INFO_BAR_HEIGHT));
	timePlayerSperatorBar.setPosition(player1NameText.getGlobalBounds().left - 25, 0);
	timePlayerSperatorBar.setFillColor(Color(40,80, 180));

	timeText.setFont(mainFont);
	timeText.setString("3:00");
	timeText.setCharacterSize(LOGO_HEIGHT);
	timeText.setColor(Color::White);
	timeText.setPosition((float)(timePlayerSperatorBar.getGlobalBounds().left - timeText.getLocalBounds().width - padding), (float)padding);

	remainingTimeText.setFont(mainFont);
	remainingTimeText.setString("Remaining Time:");
	remainingTimeText.setCharacterSize(LOGO_HEIGHT);
	remainingTimeText.setColor(Color::White);
	remainingTimeText.setPosition((float)(timeText.getGlobalBounds().left - remainingTimeText.getLocalBounds().width - 10), (float)padding);
}

void GameGraphics::drawScoresGraphics(Time elapsedTime)
{
	char player2Score[3]; sprintf_s(player2Score, "%02d", game->raft2.getNumberOfFish());
	player2ScoreText.setString(player2Score);
	game->window.draw(player2ScoreText);
	game->window.draw(player2NameText);
	game->window.draw(playerScoresSeperatorBar);
	char player1Score[3]; sprintf_s(player1Score, "%02d", game->raft1.getNumberOfFish());
	player1ScoreText.setString(player1Score);
	game->window.draw(player1ScoreText);
	game->window.draw(player1NameText);
	game->window.draw(timePlayerSperatorBar);
	char time[5]; sprintf_s(time, "%01d:%02d",(int)(game->remainingTime) / 60, (int)(game->remainingTime) % 60);
	timeText.setString(time);
	game->window.draw(timeText);
	game->window.draw(remainingTimeText);
}


void GameGraphics::create(Game* game)
{
	this->game = game;
}

void GameGraphics::load()
{
	mainFont.loadFromFile(GAME_FONT);

	loadGrassGraphics();
	loadWaterGraphics();
	loadRaft1Graphics();
	loadRaft2Graphics();
	loadFishGrpahics();
	loadLogoGrpahics();
	loadScoresGraphics();
}

void GameGraphics::initialise()
{
	initialiseWater();
	setBigStatus(NULL);
	setSmallStatus(NULL);
}

void GameGraphics::update(sf::Time elapsedTime)
{
	updateWaterGraphics(elapsedTime);
}

void GameGraphics::draw(sf::Time elapsedTime)
{
	drawWaterGraphics(elapsedTime);
	drawGrassGraphics(elapsedTime);
	drawFishGraphics(elapsedTime);
	if (game->raft1.getHealth() > 0) drawRaft1Grpahics(elapsedTime);
	if (game->raft2.getHealth() > 0) drawRaft2Graphics(elapsedTime);
	drawCannonBalls(elapsedTime);
	drawLogoGraphics(elapsedTime);
	drawScoresGraphics(elapsedTime);
	drawSmallStatus(elapsedTime);
	drawBigStatus(elapsedTime);
}

void GameGraphics::setBigStatus(char* status)
{
	if(status == NULL) strcpy_s(bigStatus, "");
	else strcpy_s(bigStatus, status);
}

void GameGraphics::setSmallStatus(char * status)
{
	if(status == NULL) strcpy_s(smallStatus, "");
	else strcpy_s(smallStatus, status);
}
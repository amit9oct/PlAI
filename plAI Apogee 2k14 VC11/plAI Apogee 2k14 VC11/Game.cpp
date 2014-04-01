#include "Game.h"
#include "VectorOps.h"
#include <math.h>
#include <list>
#include <iostream>
#include <Windows.h>

Game::Game(char* startupPath, char* mapName)
{
	strcpy_s(this->startupPath, startupPath);

	if (mapName != NULL)
	{
		strcpy_s(this->mapName, mapName);
	}
	else
	{
		strcpy_s(this->mapName, startupPath);
		strcat_s(this->mapName, DEFAULT_MAP_PATH);
	}

	raft1.create(this, &raft2);
	raft2.create(this, &raft1);
	cannonBallsManager.create(this);
	infoProvider1.create(this, &raft1);
	infoProvider2.create(this, &raft2);
	gameGraphics.create(this);
	gameSounds.create(this);

	
}

void Game::start()
{
	loadContent();

	initialise();

	sf::Clock clk;
	clk.restart();

	while (window.isOpen())
	{
		Time elapsedTime = clk.getElapsedTime();
		if (clk.getElapsedTime().asMilliseconds()!=0) gettingFPS = 1000 / clk.getElapsedTime().asMilliseconds();

		clk.restart();
		update(elapsedTime);
		draw(elapsedTime);
		playSounds();
	}
}

void Game::loadContent()
{
	map.createFromImage(this->mapName);

	int width = map.getSize().x;
	int height = map.getSize().y;

	UINT32 style;

	if (width >= 1366)
	{
		style = sf::Style::Fullscreen;
		window.setMouseCursorVisible(false);
	}
	else
	{
		style = sf::Style::Close;
	}

	window.create(sf::VideoMode(width, height), "plAI APOGEE 2014", style, sf::ContextSettings(0u, 0u, 0u, 2u, 0u));
	window.setVerticalSyncEnabled(GAME_VERTICAL_SYNC_ENABLED);
	
	gameGraphics.load();
	gameSounds.load();
}

void Game::initialise()
{
	gameState = GameState::Welcome;
	gameSounds.waterMusic.play();
	gameSounds.backgroundMusic.stop();
	gameSounds.welcomeMusic.stop();
	gameSounds.creditsMusic.stop();

	remainingTime = 180.0f;

	raft1.initialise((Vector2f)map.getPlayer1SpawnPoint());
	raft2.initialise((Vector2f)map.getPlayer2SpawnPoint());

	gameGraphics.initialise();
	gameSounds.initialise();
	cannonBallsManager.initialise();

	player1.initialise(&infoProvider1);
	player2.initialise(&infoProvider2);

	player1.getTeamName(player1WinningText); strcat_s(player1WinningText, " Won");
	player2.getTeamName(player2WinningText); strcat_s(player2WinningText, " Won");
	player1.getTeamName(versusText); strcat_s(versusText, " vs " ); player2.getTeamName(&versusText[strlen(versusText)]);
}

void Game::update(sf::Time elapsedTime)
{
	handleWindowEvents();

	switch (gameState)
	{
	case GameState::Welcome:
		{
			gameGraphics.update(elapsedTime);

			gameGraphics.setSmallStatus("Press Enter To Begin PlAIing");
			gameGraphics.setBigStatus(versusText);

			if (Keyboard::isKeyPressed(Keyboard::Return)) 
			{
				gameState = GameState::Playing;
				gameSounds.welcomeMusic.stop();
				gameSounds.backgroundMusic.play();
				gameSounds.waterMusic.play();
				gameSounds.creditsMusic.stop();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

			break;
		}
	case GameState::Playing:
		{
			remainingTime -= elapsedTime.asSeconds();

			if (raft1.getHealth() > 0)
			{
				raft1.controls = player1.controlRaft(&infoProvider1);
				raft1.update(elapsedTime);
			}

			if (map.fishLocations.empty() || remainingTime <= 0 || raft1.getHealth() == 0 || raft2.getHealth() == 0)
			{
				gameState = GameState::GameOver;
				gameSounds.welcomeMusic.stop();
				gameSounds.backgroundMusic.stop();
				gameSounds.waterMusic.stop();
				gameSounds.creditsMusic.play();
			}

			if (raft2.getHealth() > 0)
			{
				raft2.controls = player2.controlRaft(&infoProvider2);
				raft2.update(elapsedTime);
			}

			if (map.fishLocations.empty() || remainingTime <= 0 || raft1.getHealth() == 0 || raft2.getHealth() == 0)
			{
				gameState = GameState::GameOver;
				gameSounds.welcomeMusic.stop();
				gameSounds.backgroundMusic.stop();
				gameSounds.waterMusic.stop();
				gameSounds.creditsMusic.play();
			}

			cannonBallsManager.update(elapsedTime);

			if (map.fishLocations.empty() || remainingTime <= 0 || raft1.getHealth() == 0 || raft2.getHealth() == 0)
			{
				gameState = GameState::GameOver;
				gameSounds.welcomeMusic.stop();
				gameSounds.backgroundMusic.stop();
				gameSounds.waterMusic.stop();
				gameSounds.creditsMusic.play();
			}

			gameGraphics.update(elapsedTime);

			gameGraphics.setSmallStatus(versusText);
			gameGraphics.setBigStatus(NULL);

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				gameState = GameState::Paused;
				gameSounds.welcomeMusic.stop();
				gameSounds.backgroundMusic.pause();
				gameSounds.waterMusic.pause();
				gameSounds.creditsMusic.stop();
			}

			break;
		}
	case GameState::Paused:
		{
			gameGraphics.setBigStatus("Game Paused");
			gameGraphics.setSmallStatus("Press E To Exit. Press Enter To Resume.");
			if (Keyboard::isKeyPressed(Keyboard::E)) window.close();
			if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				gameState = GameState::Playing;
				gameSounds.welcomeMusic.stop();
				gameSounds.backgroundMusic.play();
				gameSounds.waterMusic.play();
				gameSounds.creditsMusic.stop();
			}

			break;
		}
	case GameState::GameOver:
		{
			gameGraphics.update(elapsedTime);

			if (raft1.getHealth() == 0)
			{
				gameGraphics.setBigStatus(player2WinningText);
			}
			else if(raft2.getHealth() == 0)
			{
				gameGraphics.setBigStatus(player1WinningText);
			}
			else
			{
				if (raft1.getNumberOfFish() > raft2.getNumberOfFish())
				{
					gameGraphics.setBigStatus(player1WinningText);
				}
				else if (raft1.getNumberOfFish() < raft2.getNumberOfFish())
				{
					gameGraphics.setBigStatus(player2WinningText);
				}
				else
				{
					if (raft1.remainingTimeAtWhichLastFishCollected < raft2.remainingTimeAtWhichLastFishCollected)
					{
						gameGraphics.setBigStatus(player2WinningText);
					}
					else if (raft2.remainingTimeAtWhichLastFishCollected < raft1.remainingTimeAtWhichLastFishCollected)
					{
						gameGraphics.setBigStatus(player1WinningText);
					}
					else
					{
						gameGraphics.setBigStatus("It's a tie!");
					}
				}
			}
			gameGraphics.setSmallStatus("Press Escape To Exit.");

			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
			//if (Keyboard::isKeyPressed(Keyboard::Return)) initialise();

			break;
		}
	}
	
}

void Game::draw(Time elapsedTime)
{
	window.clear(sf::Color(0, 0, 0, 255));
	
	gameGraphics.draw(elapsedTime);

	window.display();
}

void Game::playSounds()
{	
	gameSounds.play();
}

void Game::handleWindowEvents()
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			break;
		}
	}
}

void Game::getStartupPath(char buffer[])
{
	strcpy_s(buffer, 1024, startupPath);
}
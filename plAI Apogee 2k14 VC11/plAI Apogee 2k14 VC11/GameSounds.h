#pragma once
#include "Constants.h"
#include <SFML\Audio.hpp>

class Game;

class GameSounds
{
	Game* game;

	sf::SoundBuffer fishCollectSoundBuffer;
	sf::Sound fishCollectSound;
	
	sf::SoundBuffer landCollisionSoundBuffer;
	sf::Sound landCollisionSound;

	sf::SoundBuffer interRaftCollisionSoundBuffer;
	sf::Sound interRaftCollisionSound;

	sf::SoundBuffer cannonBallFireSoundBuffer;
	sf::Sound cannonBallFireSound;

	sf::SoundBuffer cannonBallStrikeSoundBuffer;
	sf::Sound cannonBallStrikeSound;

	

public:

	bool playFishCollectSound;
	bool playLandCollisionSound;
	bool playInterRaftCollisionSound;
	bool playCannonBallFireSound;
	bool playCannonBallStrikeSound;

	sf::Music welcomeMusic;
	sf::Music backgroundMusic;
	sf::Music waterMusic;
	sf::Music creditsMusic;

	void create(Game* game);
	void load();
	void initialise();
	void play();
};


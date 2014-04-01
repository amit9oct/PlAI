#include "GameSounds.h"
#include "Game.h"

using namespace sf;

void GameSounds::create(Game* game)
{
	this->game = game;
}

void GameSounds::load()
{
	fishCollectSoundBuffer.loadFromFile(FISH_COLLECT_SOUND_PATH);
	fishCollectSound.setBuffer(fishCollectSoundBuffer);

	landCollisionSoundBuffer.loadFromFile(LAND_COLLISION_SOUND_PATH);
	landCollisionSound.setBuffer(landCollisionSoundBuffer);

	char interRaftSoundFileName[1024]; game->getStartupPath(interRaftSoundFileName); strcat_s(interRaftSoundFileName, INTER_RAFT_COLLISION_SOUND_PATH);
	interRaftCollisionSoundBuffer.loadFromFile(interRaftSoundFileName);
	interRaftCollisionSound.setBuffer(interRaftCollisionSoundBuffer);

	char cannonBallFireSoundFileName[1024]; game->getStartupPath(cannonBallFireSoundFileName); strcat_s(cannonBallFireSoundFileName, CANNON_BALL_FIRE_SOUND_PATH);
	cannonBallFireSoundBuffer.loadFromFile(cannonBallFireSoundFileName);
	cannonBallFireSound.setBuffer(cannonBallFireSoundBuffer);

	char cannonBallStrikeSoundFileName[1024]; game->getStartupPath(cannonBallStrikeSoundFileName); strcat_s(cannonBallStrikeSoundFileName, CANNON_BALL_STRIKE_SOUND_PATH);
	cannonBallStrikeSoundBuffer.loadFromFile(cannonBallStrikeSoundFileName);
	cannonBallStrikeSound.setBuffer(cannonBallStrikeSoundBuffer);

	char welcomeMusicFileName[1024]; game->getStartupPath(welcomeMusicFileName); strcat_s(welcomeMusicFileName, WELCOME_MUSIC_PATH);
	welcomeMusic.openFromFile(welcomeMusicFileName);

	char backgroundMusicFileName[1024]; game->getStartupPath(backgroundMusicFileName); strcat_s(backgroundMusicFileName, BACKGROUND_MUSIC_PATH);
	backgroundMusic.openFromFile(backgroundMusicFileName);

	char waterMusicFileName[1024]; game->getStartupPath(waterMusicFileName); strcat_s(waterMusicFileName, WATER_MUSIC_PATH);
	waterMusic.openFromFile(waterMusicFileName);

	char creditsMusicFileName[1024]; game->getStartupPath(creditsMusicFileName); strcat_s(creditsMusicFileName, CREDITS_MUSIC_PATH);
	creditsMusic.openFromFile(creditsMusicFileName);
}

void GameSounds::initialise()
{
	welcomeMusic.setVolume(80);
	welcomeMusic.setLoop(true);
	backgroundMusic.setVolume(70);
	backgroundMusic.setLoop(true);
	waterMusic.setVolume(30);
	waterMusic.setLoop(true);
	creditsMusic.setVolume(80);
	creditsMusic.setLoop(false);
	playFishCollectSound = false;
	playLandCollisionSound=false;
	playInterRaftCollisionSound=false;
	playCannonBallFireSound=false;
	playCannonBallStrikeSound=false;
}

void GameSounds::play()
{
	if(playFishCollectSound)
	{
		fishCollectSound.play(); playFishCollectSound=false;
	}
	if(playLandCollisionSound)
	{
		landCollisionSound.play(); playLandCollisionSound=false;
	}
	if(playInterRaftCollisionSound)
	{
		interRaftCollisionSound.play(); playInterRaftCollisionSound=false;
	}
	if(playCannonBallFireSound)
	{
		cannonBallFireSound.play(); playCannonBallFireSound=false;
	}
	if(playCannonBallStrikeSound)
	{
		cannonBallStrikeSound.play(); playCannonBallStrikeSound=false;
	}
}

#include "AnimatedSprite.h"


AnimatedSprite::AnimatedSprite()
{
}


AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::create(char* fileName, int numberOfColumns, int numberOfRows, float animationFPS)
{
	texture.loadFromFile(fileName);
	sprite.setTexture(texture);
	this->numberOfColumns = numberOfColumns;
	this->numberOfRows = numberOfRows;
	this->animationFPS = animationFPS;
	clock.restart();
	unitWidth = texture.getSize().x / numberOfColumns;
	unitHeight = texture.getSize().y / numberOfRows;
}

sf::Sprite& AnimatedSprite::getCurrentSprite()
{
	int count = (int)(clock.getElapsedTime().asSeconds()*animationFPS) % (numberOfColumns*numberOfRows);
	int y = count / numberOfColumns;
	int x = count % numberOfColumns;
	sprite.setTextureRect(sf::IntRect(x*unitWidth, y*unitHeight, unitWidth, unitHeight));
	return sprite;
}

sf::Texture& AnimatedSprite::getTexture()
{
	return texture;
}
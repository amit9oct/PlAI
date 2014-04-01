#pragma once
#include <SFML\Graphics.hpp>

class AnimatedSprite
{
	sf::Sprite sprite;
	sf::Texture texture;
	int numberOfColumns;
	int numberOfRows;
	sf::Clock clock;
	int unitWidth, unitHeight;


public:

	float animationFPS;

	AnimatedSprite();
	void create(char* fileName, int numberOfColumns, int numberOfRows, float animationFPS);
	sf::Sprite& getCurrentSprite();
	sf::Texture& getTexture();
	~AnimatedSprite();
};


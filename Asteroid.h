#pragma once

class Asteroid
{
private:
	sf::Sprite sprite;
	bool isDeflected = false;

public:
	// Constructor
	Asteroid(sf::Texture* texture, sf::Vector2u windowSize)
	{

		this->sprite.setTexture(*texture);
		this->sprite.setScale(sf::Vector2f(0.4, 0.4));
		this->sprite.setRotation(180);
		this->sprite.setPosition(sf::Vector2f(rand() % (int)windowSize.x - this->sprite.getGlobalBounds().width, 0));
	}

	// Destructor
	~Asteroid()
	{}

	// Getters
	sf::Sprite getSprite()
	{
		return sprite;
	}

	void movement()
	{
		sprite.rotate(1);
		sprite.move(sf::Vector2f(0, 5));
	}
};
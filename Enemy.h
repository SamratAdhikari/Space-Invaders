#pragma once

class Enemy
{
private:
	// Member variables
	sf::Sprite sprite;
	float direction;

public:
	// Constructor
	Enemy(sf::Texture* texture, sf::Vector2u windowSize)
	{

		this->sprite.setTexture(*texture);
		this->sprite.setRotation(180);
		this->sprite.setScale(sf::Vector2f(0.12, 0.12));
		// this->sprite.setScale(sf::Vector2f(0.15, 0.15));
		this->sprite.setPosition(sf::Vector2f(rand() % windowSize.x, this->sprite.getGlobalBounds().height));

		if (sprite.getPosition().x <= (float)windowSize.x / 2)
			direction = 7;
		else
			direction = -7;
	}

	// Destructor
	~Enemy()
	{}

	// Getters
	sf::Sprite getSprite()
	{
		return sprite;
	}

	void movement()
	{
		sprite.move(sf::Vector2f(direction, 4));
	}
};
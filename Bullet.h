#pragma once

class Bullet
{
private:
	// Member variables
	sf::Sprite sprite;

public:
	// Constructor
	Bullet(sf::Texture* texture, sf::Sprite playerSprite)
	{
		this->sprite.setTexture(*texture);
		this->sprite.setScale(sf::Vector2f(0.04, 0.03));
		// this->sprite.setScale(sf::Vector2f(0.06, 0.06));
		this->sprite.setPosition(playerSprite.getPosition() + sf::Vector2f(55, 0));
		// this->sprite.setPosition(playerSprite.getPosition() + sf::Vector2f(67, 0));
	}

	// Destructor
	~Bullet()
	{}

	// Getters
	sf::Sprite getSprite()
	{
		return this->sprite;
	}

	// Methods
	void movement()
	{
		sprite.move(sf::Vector2f(0, -20));
	}
};
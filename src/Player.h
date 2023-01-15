#pragma once

class Player{
private:
	// Member variables
	sf::Sprite sprite;

public:
		// vector for bullets
		std::vector <Bullet> bullets;

public:
	// Constructor
	Player(sf::Texture *texture){

		this->sprite.setTexture(*texture);
		this->sprite.setScale(sf::Vector2f(0.25, 0.25));
		// this->sprite.setScale(sf::Vector2f(0.3, 0.3));
		this->sprite.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width/2, sf::VideoMode::getDesktopMode().height/1.25));
	}

	// Destructor
	~Player(){}


	// Getters
	sf::Sprite getSprite(){
		return sprite;
	}

	// Methods
	void moveUp(){
		sprite.move(sf::Vector2f(0.0, -9.0));
	}
	void moveDown(){
		sprite.move(sf::Vector2f(0.0, 9.0));
	}
	void moveRight(){
		sprite.move(sf::Vector2f(13.0, 0.0));
	}
	void moveLeft(){
		sprite.move(sf::Vector2f(-13.0, 0.0));
	}

	void resetPosition(){
		sprite.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width/2, sf::VideoMode::getDesktopMode().height/1.25));
	}

};
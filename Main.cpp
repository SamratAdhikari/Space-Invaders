// SPACE INVADER
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#endif

#include "Asteroid.h"
#include "Bullet.h"
#include "Collision.h"
#include "Enemy.h"
#include "Gameover.h"
#include "Player.h"
#include "PCH.hpp"

int main() {
#ifdef _WIN32
    // Hide console window
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    // Hide Mouse Cursor
    ShowCursor(FALSE);
#endif

	// Variable for lives
	int LIVES = 5;
	// Variable for kills
	int KILLS = 0;
	// Variable for highscore
	int HIGHSCORE;

	// seed random
	srand(time(NULL));

	// Variables for the screen dimensions
	float WIDTH = sf::VideoMode::getDesktopMode().width;
	float HEIGHT = sf::VideoMode::getDesktopMode().height;

	// Initialize timers
	int bulletTimer = 20;  // bullet timer
	int enemyTimer = 0;	   // enemy timer
	int asteroidTimer = 0; // asteroid timer

	// Configure Game Window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Space Invaders", sf::Style::Fullscreen);

	// set game fps
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	// Variables for background image
	sf::Texture bgTexture; // texture for background
	bgTexture.loadFromFile("assets/images/background.jpg");
	sf::Vector2u textureSize = bgTexture.getSize(); //Added to store texture size.
	sf::Vector2u windowSize = window.getSize();
	sf::Sprite bgSprite;
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale((float)windowSize.x / textureSize.x, (float)windowSize.y / textureSize.y);

	// Configure Texture for Objects
	sf::Texture playerTexture; // texture for player
	playerTexture.loadFromFile("assets/images/player.png");
	playerTexture.setSmooth(true);

	sf::Texture asteroidTexture; // texture for asteroid
	asteroidTexture.loadFromFile("assets/images/asteroid.png");
	asteroidTexture.setSmooth(true);

	sf::Texture bulletTexture; // texture for bullet
	bulletTexture.loadFromFile("assets/images/bullet.png");
	bulletTexture.setSmooth(true);

	sf::Texture enemyTexture; // texture for enemy
	enemyTexture.loadFromFile("assets/images/enemy.png");
	enemyTexture.setSmooth(true);

	// ICON
	sf::Image icon;
	icon.loadFromFile("assets/images/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// FONTS
	sf::Font font;
	font.loadFromFile("assets/fonts/ComicSansMS.ttf");
	// for lives
	sf::Text livesTxt;
	livesTxt.setFont(font);
	livesTxt.setPosition(sf::Vector2f(50, 20));
	livesTxt.setOutlineColor(sf::Color(46, 139, 87)); // lime green
	livesTxt.setOutlineThickness(2);
	// for kills
	sf::Text killsTxt;
	killsTxt.setFont(font);
	killsTxt.setPosition(sf::Vector2f(WIDTH - 200, 20));
	killsTxt.setOutlineColor(sf::Color(154, 42, 42)); // cadmium red
	killsTxt.setOutlineThickness(2);
	// for gameover screen
	sf::Text gameOverTxt;
	gameOverTxt.setFont(font);
	gameOverTxt.setOutlineThickness(2);

	// SOUNDS
	//shooting sound
	sf::SoundBuffer shootBuffer;
	shootBuffer.loadFromFile("assets/sounds/shoot.wav");
	sf::Sound shootSound;
	shootSound.setBuffer(shootBuffer);
	shootSound.setVolume(50);

	// highscore sound
	sf::SoundBuffer highscoreBuffer;
	highscoreBuffer.loadFromFile("assets/sounds/highscore.wav");
	sf::Sound highscoreSound;
	highscoreSound.setBuffer(highscoreBuffer);

	// bullet and enemy hit sound
	sf::SoundBuffer bulletEnemyBuffer;
	bulletEnemyBuffer.loadFromFile("assets/sounds/bulletEnemy.wav");
	sf::Sound bulletEnemySound;
	bulletEnemySound.setBuffer(bulletEnemyBuffer);
	bulletEnemySound.setVolume(50);

	// collision sound
	sf::SoundBuffer collisionBuffer;
	collisionBuffer.loadFromFile("assets/sounds/collision.wav");
	sf::Sound collisionSound;
	collisionSound.setBuffer(collisionBuffer);

	// bullet and asteroid hit sound
	sf::SoundBuffer bulletAsteroidBuffer;
	bulletAsteroidBuffer.loadFromFile("assets/sounds/bulletAsteroid.wav");
	sf::Sound bulletAsteroidSound;
	bulletAsteroidSound.setBuffer(bulletAsteroidBuffer);
	bulletAsteroidSound.setVolume(25);

	// bullet and asteroid hit sound
	sf::SoundBuffer gameoverBuffer;
	gameoverBuffer.loadFromFile("assets/sounds/gameover.wav");
	sf::Sound gameoverSound;
	gameoverSound.setBuffer(gameoverBuffer);

	// background music
	sf::Music music;
	music.openFromFile("assets/sounds/spacesound.ogg");
	music.setVolume(25);
	music.play();
	music.setLoop(true);

	// Initialize Player Objects
	Player playerObj(&playerTexture); // player object

	// Object to handle highscore
	bool runOnce = true; // to play the highscore sound effect only once per game

	// reading highscore from the file
	std::ifstream readFile;
	readFile.open("assets/Highscore.txt");
	if (readFile.is_open())
	{
		while (!readFile.eof())
			readFile >> HIGHSCORE;
	}
	readFile.close();

	// vector template class for enemy objects
	std::vector<Enemy> enemies;

	// vector template class for asteroid objects
	std::vector<Asteroid> asteroids;

	// infinite loop until the window is closed
	while (window.isOpen())
	{

		// LIVES AND KILLS
		livesTxt.setString("LIVES: " + std::to_string(LIVES));
		killsTxt.setString("KILLS: " + std::to_string(KILLS));

		// Handling highscore
		if (KILLS > HIGHSCORE)
		{

			// to play the highscore sound once per game
			if (runOnce)
			{
				highscoreSound.play();
				runOnce = false;
			}
			HIGHSCORE = KILLS;
		}

		// Event Listening
		sf::Event ev;

		// GAME OVER
		if (LIVES <= 0)
		{
			// GAME OVER
			gameoverSound.play();
			Gameover gameOverObj;
			// RenderWindow and Text classes are non-copyable
			// and we dont want two seperate windows to generate
			gameOverObj.printString(&window, &gameOverTxt, HIGHSCORE);

			// display eveything on the screen
			window.display();

			// wait until ENTER key is pressed
			while (window.waitEvent(ev))
			{
				// listen for key presses
				if (ev.type == sf::Event::KeyPressed)
				{
					// close the window when ENTER key is pressed
					if (ev.key.code == sf::Keyboard::Return)
						window.close();
				}
			}
		}

		// Listen for other events
		while (window.pollEvent(ev))
		{
			// handle keyboard shortcuts to close the window
			if (ev.type == sf::Event::Closed)
				window.close();

			// listen for key presses
			if (ev.type == sf::Event::KeyPressed)
			{
				// close the window when Esc key is pressed
				if (ev.key.code == sf::Keyboard::Escape)
					window.close();
			}
		}

		// Player Motion
		// move up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			// top side of the player's ship should be less than the top of the screen
			if (playerObj.getSprite().getPosition().y > 0)
				playerObj.moveUp();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // move down
			// bottom side of the player's ship should be greater than the bottom of the screen
			if (playerObj.getSprite().getPosition().y + playerObj.getSprite().getGlobalBounds().width < window.getSize().y)
				playerObj.moveDown();
		// move right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			// right side of the player's ship should be less than the right of the screen
			if (playerObj.getSprite().getPosition().x + playerObj.getSprite().getGlobalBounds().width < window.getSize().x)
				playerObj.moveRight();
		// move left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			// left side of the player's ship should be greater than the left of the screen
			if (playerObj.getSprite().getPosition().x > 0)
				playerObj.moveLeft();

		// BULLETS
		if (bulletTimer < 20) // to generate one bullet per 20 complete game loops
			bulletTimer++;

		// Trigger bullets
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && bulletTimer >= 20)
		{
			// appends the bullet obj to the end of the bullets vector
			playerObj.bullets.push_back(Bullet(&bulletTexture, playerObj.getSprite())); //nameless object
			shootSound.play();
			bulletTimer = 0;
		}

		// Handling Bullets
		for (uint i = 0; i < playerObj.bullets.size(); i++)
		{
			// move bullets
			playerObj.bullets[i].movement();

			// Out of bounds
			if (playerObj.bullets[i].getSprite().getPosition().y + playerObj.bullets[i].getSprite().getGlobalBounds().height <= 0)
			{
				// deletes the ith object from the beginning(0th index) of the vector
				playerObj.bullets.erase(playerObj.bullets.begin() + i);
				break;
			}

			// BULLET & ENEMY COLLISION
			for (uint j = 0; j < enemies.size(); j++)
			{
				// checks for pixel to pixel collision between two objects (sprites)
				if (Collision::PixelPerfectTest(playerObj.bullets[i].getSprite(), enemies[j].getSprite()))
				{
					bulletEnemySound.play();
					enemies.erase(enemies.begin() + j);
					playerObj.bullets.erase(playerObj.bullets.begin() + i);
					KILLS++; // increase kill point
					break;
				}
			}

			// Bullets and Asteriods Collision
			for (uint j = 0; j < asteroids.size(); j++) // uint - because vector objects are unsigned
			{
				if (Collision::PixelPerfectTest(playerObj.bullets[i].getSprite(), asteroids[j].getSprite()))
				{
					playerObj.bullets.erase(playerObj.bullets.begin() + i);
					bulletAsteroidSound.play();
					break;
				}
			}
		}

		// Player and Enemies Collision
		for (uint i = 0; i < enemies.size(); i++)
		{
			if (Collision::PixelPerfectTest(playerObj.getSprite(), enemies[i].getSprite()))
			{
				collisionSound.setVolume(25);
				collisionSound.play();
				enemies.erase(enemies.begin() + i);
				LIVES--;
				KILLS++;
				break;
			}
		}

		// Player and Asteroids Collision
		for (uint i = 0; i < asteroids.size(); i++)
		{
			if (Collision::PixelPerfectTest(playerObj.getSprite(), asteroids[i].getSprite()))
			{
				LIVES--;
				collisionSound.setVolume(100);
				collisionSound.play();
				asteroids.erase(asteroids.begin() + i);
				playerObj.resetPosition();
				break;
			}
		}

		// Enemies and Asteroids Collision
		for (uint i = 0; i < asteroids.size(); i++)
		{
			for (uint j = 0; j < enemies.size(); j++)
			{
				if (Collision::PixelPerfectTest(enemies[j].getSprite(), asteroids[i].getSprite()))
				{
					collisionSound.setVolume(25);
					collisionSound.play();
					enemies.erase(enemies.begin() + j);
					break;
				}
			}
		}

		// ENEMIES
		if (enemyTimer < 100) // to generate one enemy per 100 game loops
			enemyTimer++;

		if (enemyTimer >= 100)
		{
			enemies.push_back(Enemy(&enemyTexture, window.getSize()));
			enemyTimer = 0;
		}

		// ASTEROIDS
		if (asteroidTimer < 150) // to generate one asteroid per 150 game loops
			asteroidTimer++;

		if (asteroidTimer >= 150)
		{
			asteroids.push_back(Asteroid(&asteroidTexture, window.getSize()));
			asteroidTimer = 0;
		}

		// Enemies Out of bounds
		for (uint i = 0; i < enemies.size(); i++)
		{
			// RIGHT
			if (enemies[i].getSprite().getPosition().x > window.getSize().x)
			{
				enemies.erase(enemies.begin() + i);
				LIVES--;
				break;
			}

			// LEFT
			if (enemies[i].getSprite().getPosition().x < 0)
			{
				enemies.erase(enemies.begin() + i);
				LIVES--;
				break;
			}
		}

		// Asteroids out of bounds
		for (uint i = 0; i < asteroids.size(); i++)
		{
			// Bottom
			if (asteroids[i].getSprite().getPosition().y - asteroids[i].getSprite().getGlobalBounds().height > window.getSize().y)
			{
				asteroids.erase(asteroids.begin() + i);
				break;
			}

			// Right
			if (asteroids[i].getSprite().getPosition().x > window.getSize().x)
			{
				asteroids.erase(asteroids.begin() + i);
				break;
			}

			// Left
			if (asteroids[i].getSprite().getPosition().x < 0)
			{
				asteroids.erase(asteroids.begin() + i);
				break;
			}
		}

		// clear/ update the window
		window.clear();

		// draw background image
		window.draw(bgSprite);

		// draw player
		window.draw(playerObj.getSprite());

		// draw asteroid
		for (uint i = 0; i < asteroids.size(); i++)
		{
			window.draw(asteroids[i].getSprite());
			asteroids[i].movement();
		}

		// draw enemies
		for (uint i = 0; i < enemies.size(); i++)
		{
			window.draw(enemies[i].getSprite());
			enemies[i].movement();
		}

		// draw bullets
		for (uint i = 0; i < playerObj.bullets.size(); i++)
			window.draw(playerObj.bullets[i].getSprite());

		// draw the texts
		window.draw(livesTxt);
		window.draw(killsTxt);

		// display all the elements on the window
		window.display();
	}

	return 0;
}